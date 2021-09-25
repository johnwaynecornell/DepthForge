//
// Created by jwc on 1/28/19.
//

#include <QtGui/QPainter>
#include <QtCore/QAbstractEventDispatcher>
#include <QtWidgets/QMenuBar>

#include <QMouseEvent>

#include <QStandardPaths>
#include <QFileDialog>

#include <math.h>

#include "DepthForgeWin.h"
#include <UI/TestUI.h>

extern "C"
{
    #include "PixelGfx/JWC_PixelGfx.h"
}

#include "UI/UI.h"
#include "MainWnd.h"

DepthForgeWin::DepthForgeWin(QMainWindow *appWindow, QWindow *parent) : QOpenGLWindow(NoPartialUpdate, parent)
{
    glEnable(GL_STEREO);

    hasMouse = false;
    showFPS = false;

    dispatcher = QAbstractEventDispatcher::instance();
    //connect(dispatcher, SIGNAL(aboutToBlock()), SLOT(aboutToBlock()));

    UI_Image = UI_ImageMono  = UI_ImageLeft = UI_ImageRight = nullptr;
    rend = nullptr;

    this->parent = appWindow;

    mouseCapture = nullptr;
    obuf = nullptr;

    void *tmp;

    MainWnd *w = (MainWnd *) appWindow;

    get_member_pointer(void (DepthForgeWin::*a)(UI *, void *), &DepthForgeWin::take_picture_jps, tmp);
    w->export_jps_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};

    get_member_pointer(void (DepthForgeWin::*a)(UI *, void *), &DepthForgeWin::take_picture_ana, tmp);
    w->export_anaglyph_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};

    //ui = new TestUI(this);

    ui = new MainUI(this);
    forceAnaglyph = false;
    SBSHalf = false;

    idleTimer.setInterval(0);
    connect(&idleTimer, SIGNAL(timeout()), this, SLOT(idleCallback()));
    idleTimer.start();
}

void DepthForgeWin::idleCallback()
{
    requestUpdate();
}

void DepthForgeWin::aboutToBlock()
{
    //OnIdle();
}

void DepthForgeWin::resizeGL(int w,int h)
{
    QOpenGLWindow::resizeGL(w,h);
    checkResize();
}

void DepthForgeWin::checkResize()
{
    Width = width();
    Height = height();

    if (Width != oldWidth || Height != oldHeight) {
        oldWidth = Width;
        oldHeight = Height;


        int w = Width;
        int h = Height;

        if (UI_Image != nullptr) delete UI_Image;
        if (UI_ImageMono != nullptr) delete UI_ImageMono;
        if (UI_ImageLeft != nullptr) delete UI_ImageLeft;
        if (UI_ImageRight != nullptr) delete UI_ImageRight;
        if (rend != nullptr) delete rend;

        UI_Image = new Image(w, h);
        UI_ImageMono = new Image(w, h);
        UI_ImageLeft = new Image(w, h);
        UI_ImageRight = new Image(w, h);

        rend = new QImage((uchar *) UI_Image->imageMemory, w, h, QImage::Format_ARGB32);

        ui->xReal = 0;
        ui->yReal = 0;
        ui->yPos.set(0);
        ui->yPos.set(0);

        ui->width.set(w);
        ui->height.set(h);

        if (obuf != nullptr) delete[] obuf;
        obuf = new BGRA[Width * Height];

        ui->finalLayout();
    }
}

void DepthForgeWin::closeEvent(QCloseEvent *event)
{

    if (UI_Image != nullptr) delete UI_Image;
    if (UI_ImageMono != nullptr) delete UI_ImageMono;
    if (UI_ImageLeft != nullptr) delete UI_ImageLeft;
    if (UI_ImageRight != nullptr) delete UI_ImageRight;
    if (rend != nullptr) delete rend;

    delete ui;

    disconnect(dispatcher, SIGNAL(aboutToBlock()));

}

void DepthForgeWin::mouseMoveEvent(QMouseEvent *eventMove)
{
    if (!hasMouse) takeMouse();

    int x = eventMove->x();
    int y = eventMove->y();

    lastMouseX = x;
    lastMouseY = y;

    showMouse = (x>=0)&&(x<width())&&(y>=0)&&(y<height());

    if (mouseCapture != nullptr)
    {
        ui->mouseCoordNotify(x,y);
        x -= mouseCapture->xReal;
        y -= mouseCapture->yReal;

        mouseCapture->mouseMove(x, y);

    } else if (!checkRelinquishMouse(x,y)) ui->mouseMove(x, y);
}
void DepthForgeWin::mousePressEvent(QMouseEvent *eventPress)
{
    //eventPress->
    if (!hasMouse) takeMouse();

    int x = eventPress->x();
    int y = eventPress->y();

    lastMouseX = x;
    lastMouseY = y;

    if (mouseCapture != nullptr)
    {
        x -= mouseCapture->xReal;
        y -= mouseCapture->yReal;

        mouseCapture->mouseButtonPress(x, y,
                                       eventPress->button());

    } else if (!checkRelinquishMouse(x,y)) ui->mouseButtonPress(x, y,
            eventPress->button());
}
void DepthForgeWin::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    if (!hasMouse) takeMouse();

    int x = releaseEvent->x();
    int y = releaseEvent->y();

    lastMouseX = x;
    lastMouseY = y;

    if (mouseCapture != nullptr)
    {
        x -= mouseCapture->xReal;
        y -= mouseCapture->yReal;

        mouseCapture->mouseButtonRelease(x, y,
                                         releaseEvent->button());

    } else if (!checkRelinquishMouse(x,y)) ui->mouseButtonRelease(x, y,
            releaseEvent->button());
}

void DepthForgeWin::giveMouse(UI *element)
{
    mouseCapture = element;
}

void DepthForgeWin::freeMouse(UI *element)
{
    mouseCapture = nullptr;

    checkRelinquishMouse(lastMouseX, lastMouseY);
}


void DepthForgeWin::takeMouse()
{
    setMouseGrabEnabled(true);
    hasMouse = true;
    ui->mouseEnter();
}

bool DepthForgeWin::checkRelinquishMouse(int x, int y)
{
    if (!hasMouse) return false;
    if (x<0||y<0||x>width()||y>height() && mouseCapture == nullptr || parent->isActiveWindow() == false)
    {
        setMouseGrabEnabled(false);
        hasMouse = false;

        ui->mouseLeave();

        return true;
    }

    return false;
}

void DepthForgeWin::initializeGL()
{

    QOpenGLWindow::initializeGL();

    int majorversion = format().majorVersion();
    int minorversion = format().minorVersion();

    glDrawBuffer(GL_BACK_RIGHT);
    real_stereo = format().stereo() && (glGetError() == GL_NO_ERROR);
    anaglyph = !real_stereo;
}

void DepthForgeWin::paintGL()
{
    checkResize();

    RGBA DrawColor = { (uchar) rand(),(uchar) rand(),(uchar) rand(),0xFF};

    UI_Image->FillRect(0,0,Width,Height, PixOp_SRC, {0xFF,0x00,0x00,0x00}, ZOp_SRC, 0.0f);

    ui->finalLayout();
    ui->doDraw(UI_Image,rend);

    if (showFPS)
    {
        fps.mark(ui->getTimeInSeconds());

        char disp[1024];

        sprintf(disp, "%lf fps", fps.fps());

        QPainter *p = new QPainter(rend);

        QFont f = p->font();
        f.setPointSizeF(10);
        p->setFont(f);
        p->setPen(QColor(0xFF,0xFF,0xFF,0xFF));

        QFontMetrics m = p->fontMetrics();

        //QRect r = m.boundingRect(tr(disp));

        QSize s = m.size(0, tr(disp));

        QRect r = QRect(10,10,s.width(), s.height());

        UI_Image->FillRect(r.x(), r.y(), r.width(), r.height(), PixOp_SRC, {0xFF,0x00,0x00,0x00}, ZOp_SRC, 0);

        p->drawText(r.x(), r.y()+m.ascent(), QApplication::tr(disp));

        p->end();
        delete  p;

    }

    bool MONO = false;

    UI_Image->Artif3d(UI_Image->Width/30, UI_ImageLeft, UI_ImageRight);
    if ((anaglyph&&!SBSHalf) || forceAnaglyph) {
        UI_ImageMono->AnaglyphFrom(UI_ImageLeft, UI_ImageRight);
        MONO = true;
    } else if (SBSHalf)
    {
        GfxBlt(PixType_ARGB, UI_ImageLeft->imageMemory,0, 0, Width, Height, Width,
               PixType_ARGB, UI_ImageMono->imageMemory,
               0, 0, Width / 2, Height, Width);

        GfxBlt(PixType_ARGB, UI_ImageRight->imageMemory,0, 0, Width, Height, Width,
               PixType_ARGB, UI_ImageMono->imageMemory,
               Width / 2, 0, Width / 2, Height, Width);

        MONO = true;
    }

    if (real_stereo)
    {
        glDrawBuffer(GL_BACK_LEFT);

        GfxBlt(PixType_ARGB, (MONO) ?
                             UI_ImageMono->imageMemory : UI_ImageLeft->imageMemory,
               0, 0, Width, Height, Width, PixType_ABGR, obuf,
               0, 0, Width, -Height, Width);

        glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, obuf);
        glFinish();

        glDrawBuffer(GL_BACK_RIGHT);

        GfxBlt(PixType_ARGB, (MONO)
                             ? UI_ImageMono->imageMemory : UI_ImageRight->imageMemory,
               0, 0, Width, Height, Width, PixType_ABGR, obuf,
               0, 0, Width, -Height, Width);

        glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, obuf);
        glFinish();

    } else {

        glDrawBuffer(GL_BACK);

        GfxBlt(PixType_ARGB, UI_ImageMono->imageMemory, 0, 0, Width, Height, Width, PixType_ABGR, obuf, 0, 0, Width,
               -Height, Width);
        glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, obuf);
    }
}


void DepthForgeWin::MouseButtonDown()
{
}

void DepthForgeWin::OnIdle(void) {
    //this->update();
}

void DepthForgeWin::setShowFPS(bool state)
{
    showFPS = state;
}

void DepthForgeWin::take_picture_ana(UI *sender, void *arg) {
    Image *ImageLeft;
    Image *ImageRight;
    Image *src = UI_Image;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);

    QString path = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
                                          QStandardPaths::LocateOption::LocateDirectory);

    QString fileName = QFileDialog::getSaveFileName(
            parent, ("Save Image File"),
            path,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        save_ana(fileName, ImageLeft, ImageRight);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;

}

void DepthForgeWin::take_picture_jps(UI *sender, void *arg)
{
    Image *ImageLeft;
    Image *ImageRight;
    Image *src = UI_Image;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);

    const bool SideBySide = true;

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);

    QString path = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
                                          QStandardPaths::LocateOption::LocateDirectory);

    QString fileName = QFileDialog::getSaveFileName(
            parent, ("Save Image File"),
            path,
            ("Images (*.jps)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        save_jps(fileName, ImageLeft, ImageRight);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;
}