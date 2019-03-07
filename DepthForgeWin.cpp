//
// Created by jwc on 1/28/19.
//

#include "DepthForgeWin.h"

#include <QtGui/QPainter>
#include <QtCore/QAbstractEventDispatcher>
#include <QtWidgets/QMenuBar>

#include <QMouseEvent>

#include <QStandardPaths>
#include <QFileDialog>

#include <math.h>
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



    Image *A = new Image(1024,768);
    Image *B = new Image(200,200);

    A->DrawImage(0,100,1024,768, 0, 0, 200,200, PixOp_SRC, ZOp_SRC,
            B,0,0,200,200);

    A->DrawImage(0,0,1024,768, 0, 0, 200,200, PixOp_SRC, ZOp_SRC,
                 B,0,100,200,100);


    hasMouse = false;
    dispatcher = QAbstractEventDispatcher::instance();
    connect(dispatcher, SIGNAL(aboutToBlock()), SLOT(aboutToBlock()));

    UI_Image = UI_ImageAnaglyph  = UI_ImageLeft = UI_ImageRight = nullptr;
    rend = nullptr;

    this->parent = appWindow;

    mouseCapture = nullptr;

    void *tmp;

    MainWnd *w = (MainWnd *) appWindow;

    get_member_pointer(void (DepthForgeWin::*a)(void *), &DepthForgeWin::take_picture_jps, tmp);
    w->export_jps_proc = {this, (void (*)(void *,void *))tmp, nullptr};

    get_member_pointer(void (DepthForgeWin::*a)(void *), &DepthForgeWin::take_picture_ana, tmp);
    w->export_anaglyph_proc = {this, (void (*)(void *,void *))tmp, nullptr};

    //ui = new TestUI(this);

    ui = new MainUI(this);
    forceAnaglyph = false;

}

void DepthForgeWin::aboutToBlock()
{

    OnIdle();
}

void DepthForgeWin::resizeGL(int w,int h)
{
    QOpenGLWindow::resizeGL(w,h);
}

void DepthForgeWin::checkResize()
{
    Width = width();
    Height = height();

    if (Width != oldWidth || Height != oldHeight)
    {
        oldWidth = Width;
        oldHeight = Height;
    }

    int w = Width;
    int h = Height;

    if (UI_Image != nullptr) delete UI_Image;
    if (UI_ImageAnaglyph  != nullptr) delete UI_ImageAnaglyph;
    if (UI_ImageLeft != nullptr) delete UI_ImageLeft;
    if (UI_ImageRight != nullptr) delete UI_ImageRight;
    if (rend != nullptr) delete rend;

    UI_Image = new Image(w,h);
    UI_ImageAnaglyph  = new Image(w,h);
    UI_ImageLeft = new Image(w,h);
    UI_ImageRight = new Image(w,h);

    rend = new QImage((uchar *)UI_Image->imageMemory, w, h, QImage::Format_ARGB32);

    ui->xReal = 0; ui->yReal = 0;
    ui->yPos.set(0);
    ui->yPos.set(0);

    ui->width.set(w);
    ui->height.set(h);

    ui->finalLayout();

    this->Width = w;
    this->Height = h;
}

void DepthForgeWin::closeEvent(QCloseEvent *event)
{

    if (UI_Image != nullptr) delete UI_Image;
    if (UI_ImageAnaglyph  != nullptr) delete UI_ImageAnaglyph;
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

    if (mouseCapture != nullptr)
    {
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
    anaglyph = !format().stereo();
}

void DepthForgeWin::paintGL()
{


    checkResize();

    BGRA *obuf = new BGRA[Width*Height];

    RGBA DrawColor = { (uchar) rand(),(uchar) rand(),(uchar) rand(),0xFF};

    UI_Image->FillRect(0,0,Width-1,Height-1, PixOp_SRC, {0xFF,0x00,0x00,0x00}, ZOp_SRC, 0.0f);

    ui->draw(UI_Image,rend);


    /*
    QImage A;
    A.load(tr("/home/jwc/Pictures/Danielle.jpg"));
    QImage::Format  f = A.format();

    if (!A.hasAlphaChannel() && A.format() == QImage::Format_RGB32)
    {
        QImage B = QImage(A.width(), A.height(), QImage::Format_ARGB32);

        GfxBlt(PixType_BGRA, A.bits(), 0,0,A.width(),A.height(), A.width(),
                PixType_ARGB, B.bits(), 0, 0, B.width(), B.height(), B.width());

        A = B;
    }

    Image Q(128,128);
    QImage _Q((uchar *)Q.imageMemory, 128,128, QImage::Format_ARGB32);

    QPainter P(&_Q);
    P.setCompositionMode(QPainter::CompositionMode_Source);
    P.drawImage(QRect(0,0, Q.Width, Q.Height),
            A, QRect(0,0, A.width(),A.height()));
    P.end();

    for (int y=0; y <128; y++)
    {
        for (int x=0; x < 128; x++)
        {
            Q.pix[y][x].a = 0x80;
        }

    }

    Q.CalcZ();

    UI_Image->FillRect(250,200,300,250, PixOp_SRC_ALPHA, {0x80,0x80,0x00,0x80}, ZOp_SRC_ADD, -.25);

    UI_Image->DrawImage(200,200,100,100, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
            &Q,0,0,128,128);

    UI_Image->DrawImage(250,250,100,100, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                        &Q,0,0,128,128);
*/

/*
    QPainter P;

    P.begin(rend);

    P.fillRect(0,0,Width,Height, QColor(0x00,0x00,0xFF,0xFF));

    P.end();

    for (int y=0;y<100;y++)
    {
        for (int x=0; x<100; x++)
        {
            ARGB b = {0xFF, (unsigned char) (x+y),(unsigned char) (x*y),0};
            UI_Image->imageMemory[y*Width+x] = b;
        }
    }


    P.begin(rend);

    QPen pen = P.pen();

    pen.setColor(QColor(DrawColor.r, DrawColor.g, DrawColor.b));

    P.setPen(pen);

    P.drawLine(0,0,Width, Height);
    //SDL_SetRenderDrawColor(rend, DrawColor.r, 0, DrawColor.b, DrawColor.a);
    //SDL_RenderDrawLine(rend,0,0,Width,Height);

    P.end();
*/
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

        UI_Image->FillRect(r.x(), r.y(), r.x()+r.width(), r.y()+r.height(), PixOp_SRC, {0xFF,0x00,0x00,0x00}, ZOp_SRC, 0);

        p->drawText(r.x(), r.y()+m.ascent(), QApplication::tr(disp));

        p->end();
        delete  p;

    }


    UI_Image->Artif3d(UI_Image->Width/30, UI_ImageLeft, UI_ImageRight);
    if (anaglyph || forceAnaglyph)
        UI_ImageAnaglyph->AnaglyphFrom(UI_ImageLeft, UI_ImageRight);

    if (format().stereo())
    {
        glDrawBuffer(GL_BACK_LEFT);

        Q_ASSERT(glGetError() == GL_NO_ERROR);

        GfxBlt(PixType_ARGB, (anaglyph || forceAnaglyph) ?
        UI_ImageAnaglyph->imageMemory : UI_ImageLeft->imageMemory,
                0, 0, Width, Height, Width, PixType_ABGR, obuf,
                0, 0, Width, -Height, Width);

        glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, obuf);

        glDrawBuffer(GL_BACK_RIGHT);
        Q_ASSERT(glGetError() == GL_NO_ERROR);
        glFinish();

        GfxBlt(PixType_ARGB, (anaglyph || forceAnaglyph)
        ? UI_ImageAnaglyph->imageMemory : UI_ImageRight->imageMemory,
               0, 0, Width, Height, Width, PixType_ABGR, obuf,
               0, 0, Width, -Height, Width);

        glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, obuf);
        glFinish();

    } else {

        glDrawBuffer(GL_BACK);

        GfxBlt(PixType_ARGB, UI_ImageAnaglyph->imageMemory, 0, 0, Width, Height, Width, PixType_ABGR, obuf, 0, 0, Width,
               -Height, Width);
        //GfxBlt(PixType_ARGB, UI_Image->imageMemory, 0,0,Width,Height, Width, RenderBufferType, obuf, 0, 0, Width, -Height, Width);
        //GfxBlt(PixType_ARGB, UI_ImageLeft->imageMemory, 0,0,Width,Height, Width, RenderBufferType, obuf, 0, 0, Width, -Height, Width);

        glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, obuf);

    }

    delete []obuf;

//    SDL_RenderPresent(renderer);
}

void DepthForgeWin::MouseButtonDown()
{
}

void DepthForgeWin::OnIdle(void)
{
    this->update();
}

void DepthForgeWin::setShowFPS(bool state)
{
    showFPS = state;
}

void DepthForgeWin::take_picture_ana(void *arg) {
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

void DepthForgeWin::take_picture_jps(void *arg)
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