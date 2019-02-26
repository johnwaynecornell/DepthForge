//
// Created by jwc on 1/28/19.
//

#include "DepthForgeWin.h"

#include <QtGui/QPainter>
#include <QtCore/QAbstractEventDispatcher>
#include <QtWidgets/QMenuBar>

#include <QMouseEvent>

#include <math.h>
#include <UI/TestUI.h>

extern "C"
{
    #include "PixelGfx/JWC_PixelGfx.h"
}

#include "UI/UI.h"

DepthForgeWin::DepthForgeWin(QMainWindow *parent)
{
    hasMouse = false;
    dispatcher = QAbstractEventDispatcher::instance();
    connect(dispatcher, SIGNAL(aboutToBlock()), SLOT(aboutToBlock()));

    UI_Image = UI_ImageAnaglyph  = UI_ImageLeft = UI_ImageRight = nullptr;
    rend = nullptr;

    this->parent = parent;

    //ui = new TestUI(this);

    ui = new MainUI(this);
    mouseCapture = nullptr;

    /*
    ui = new Fixed(nullptr);

    ui->width.setResp(Resp_Self);
    ui->height.setResp(Resp_Self);
    ui->xPos.setResp(Resp_Self);
    ui->yPos.setResp(Resp_Self);

    Frame *f = new Frame(ui);
    ui->children.push_back(f);

    f->xPos.set(0);
    f->yPos.set(0);

    f->width.setResp(Resp_Child);
    f->height.setResp(Resp_Child);

    f->backgroundResp = Resp_Child;

    Button_Image *t = new Button_Image(f);
    f->children.push_back(t);

    t->width.setResp(Resp_Self);
    t->height.setResp(Resp_Self);

    t->xPos.set(0);
    t->yPos.set(0);

    t->z = -0;

    t->backColor = {0xFF, 0x40,0x00,0x80, .25};

    t->backgroundResp = Resp_Self;

//    Image *bg = new Image(128,128);
//    Image *_bg = new Image(128,128);

    QImage A;
    A.load(tr("/home/jwc/Pictures/Danielle.jpg"));

    if (!A.hasAlphaChannel() && A.format() == QImage::Format_RGB32)
    {
        QImage B = QImage(A.width(), A.height(), QImage::Format_ARGB32);

        GfxBlt(PixType_BGRA, A.bits(), 0,0,A.width(),A.height(), A.width(),
               PixType_ARGB, B.bits(), 0, 0, B.width(), B.height(), B.width());

        A = B;
    }

    UI_Image = UI_ImageAnaglyph  = UI_ImageLeft = UI_ImageRight = nullptr;
    rend = nullptr;

    Image *Q = new Image(128,128);

    int xc = Q->Height/2;
    int yc = Q->Width/2;

    for (int y=0; y<Q->Height; y++)
    {
        for (int x=0; x<Q->Width; x++)
        {
            unsigned char v;

  //          v = (unsigned char) (rand()%80);

  //          _bg->pix[y][x]={0xFF,
  //                         (unsigned char) (v+rand()%0x80), (unsigned char)(v+rand()%0x80),0};

            int xx = x-xc;
            int yy = y-yc;

            float d = 1 - sqrtf(xx*xx+yy*yy)/xc;
            if (d<0) d = 0;

            d = sin(d*M_PI/2);
//d=0;
            unsigned char r;
            unsigned char b;

            if (x%0x10 == 0 || y%0x10 == 0)
            {
                b=0x80;
                r=0x80;
            } else {
                b=0xFF;
                r=0xFF;
            }

            v = (unsigned char) (d*0xFF);
            Q->pix[y][x] = {v,r,b,b};
            Q->z[y][x] = -d * .25;

        }
    }
/*
    for (int y=0; y<Q->Height; y++) {
        for (int x = 0; x < Q->Width; x++) {
            int r=0;
            int g=0;
            int b=0;
            int a=0;
            int d=0;

            const int gr=2;

            for (int yy=y-gr;yy<=y+gr; yy++)
            {
                for (int xx=x-gr;xx<x+gr; xx++)
                {
                    if (xx>=0&&xx<bg->Width&&yy>=0&&yy<bg->Height)
                    {
                        ARGB p = _bg->pix[yy][xx];
                        r+=p.r;
                        g+=p.g;
                        b+=p.b;
                        a+=p.a;

                        d++;

                    }
                }
            }

            bg->pix[y][x] = {(unsigned char)(a/d),(unsigned char)(r/d),
                             (unsigned char)(g/d),(unsigned char)(b/d)};

        }
    }


            t->src = Q;
*/
    setMouseTracking(true);

    //Q->CalcZ();

    /*
    ARGB C1 = {0,0,0,0};
    ARGB C2 = C1;
    float z1 = -.05;
    float z2 = z1;

    for (int i=0; i<24; i++)
    {
        int x1 = i; int y1=i;
        int x2 = 127-i; int y2 = 127-i;

        Q->FillRect(x1, y1, x2-1, y1, PixOp_SRC_ALPHA, C1, ZOp_SRC_ADD, z1);
    }*/

}

void DepthForgeWin::aboutToBlock()
{

    OnIdle();
}

void DepthForgeWin::resizeGL(int w,int h)
{
    QGLWidget::resizeGL(w,h);
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
    grabMouse();
    hasMouse = true;
    ui->mouseEnter();
}

bool DepthForgeWin::checkRelinquishMouse(int x, int y)
{
    if (!hasMouse) return false;
    if (x<0||y<0||x>width()||y>height() && mouseCapture == nullptr)
    {
        releaseMouse();
        hasMouse = false;

        ui->mouseLeave();

        return true;
    }

    return false;
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
    UI_ImageAnaglyph->AnaglyphFrom(UI_ImageLeft, UI_ImageRight);


    GfxBlt(PixType_ARGB, UI_ImageAnaglyph->imageMemory, 0,0,Width,Height, Width, PixType_ABGR, obuf, 0, 0, Width, -Height, Width);
    //GfxBlt(PixType_ARGB, UI_Image->imageMemory, 0,0,Width,Height, Width, RenderBufferType, obuf, 0, 0, Width, -Height, Width);
    //GfxBlt(PixType_ARGB, UI_ImageLeft->imageMemory, 0,0,Width,Height, Width, RenderBufferType, obuf, 0, 0, Width, -Height, Width);

    glDrawBuffer(GL_BACK_LEFT);

    if (glGetError() != GL_NO_ERROR)
    {
        int q = 1;
        q+=2;
    }

    glDrawPixels(Width,Height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, obuf);

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