//
// Created by jwc on 3/26/19.
//

extern "C"
{
    #include <PixelGfx/JWC_PixelGfx.h>
}

#include <QtGui/QPainter>
#include <math.h>
#include "genbuttons.h"

#include "Image/PathAdapter.h"

QApplication *app;

int main(int argc, char **argv)
{
    Init_JWC_PixelGfx();
    app = new QApplication(argc, argv);

    int Threads = 8;
    GfxInitThreadWorkers(Threads);


    QMainWindow *W = new QMainWindow();
    Wij *w = new Wij(W);

    W->setCentralWidget(w);

    W->show();
    w->show();

    app->exec();

    GfxTerminate();

}

unsigned char clamp(int i)
{
    if (i<0) return 0;
    if (i>255) return 255;
    return i;
}

ARGB Normalize(ARGB in)
{
    double r = in.r;
    double g = in.g;
    double b = in.b;

    double d = sqrt(r*r+g*g+b*b);
    double d2 = sqrt(255*255*3);

    r /= d;
    g /= d;
    b /= d;

    return {in.a, clamp(r*d2), clamp(g*d2), clamp(b*d2)};

}

ARGB bg = Normalize( ARGB {0xFF, 0x20, 0x20, 0x20});
ARGB color = Normalize( ARGB {0xFF, 0x30, 0x5, 0x30});

bool line(int index, double v, ARGB &p, float &z, void *arg)
{
    if (abs(v)<=2/48.0) {
        p = color;
        z = 0;
        return true;
    }

    return false;
}

Image *image_Divide;
Image *image_Move;
Image *image_Plus;
Image *image_Connect;

void BuildDivide()
{
    image_Divide = new Image(48,48);
    image_Divide->FillRect(0,0,48,48, PixOp_SRC,bg, ZOp_SRC, 0);

    PathAdapter a;

    a.inputMatrix = dMatrix2D::Translate({-.9,0}) * dMatrix2D::Rotate(-M_PI/5.0) * dMatrix2D::Translate({.9,0});
    a.inputMatrix *= dMatrix2D::Translate({0,.2});

    a.outputMatrix = dMatrix2D::Scale({(double) image_Divide->Width, (double) image_Divide->Height});

    a.Line({.9,.2}, {.9,.8});

    a.Line({.4,.5}, {.75,.5});

    a.Line({.75,.5-.1}, {.75, .5+.1});
    a.Line({.75,.5-.1}, {.9, .5});
    a.Line({.75, .5+.1}, {.9, .5});


    a.Apply(image_Divide);

    image_Divide->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / image_Divide->Width, &line, nullptr);
}

bool finger(int index, double v, ARGB &p, float &z, void *arg)
{
    if (abs(v)<=4/48.0) {
        p = color;
        z = 0;
        return true;
    }

    return false;
}

bool hand(int index, double v, ARGB &p, float &z, void *arg)
{
    if (v>=-4/48.0) {
        p = color;
        z = 0;
        return true;
    }

    return false;
}


void BuildMove()
{
    image_Move = new Image(48,48);
    image_Move->FillRect(0,0,48,48, PixOp_SRC, bg, ZOp_SRC, 0);

    PathAdapter a;

    a.inputMatrix *= dMatrix2D::Scale({1.0/8,1.0/10}) * dMatrix2D::Translate({1.0/8,1.0/10});;
    a.outputMatrix = dMatrix2D::Scale({(double) image_Move->Width, (double) image_Move->Height});

    a.Line({1,2}, {1,4});
    a.Line({2,1}, {2,4});
    a.Line({3,.5}, {3,4});
    a.Line({4,1.5}, {4,6});
    a.Line({4,6}, {6,4});

    a.Apply(image_Move);

    image_Move->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / image_Divide->Width, &finger, nullptr);

    image_Move->ClearPath();
    a.ClearPath();

    a.Line({1,4},{4,4});
    a.LineTo({4,6});
    a.LineTo({3,8});
    a.LineTo({1.5,8});
    a.LineTo({1,4});

    a.Apply(image_Move);

    image_Move->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / image_Divide->Width, &hand, nullptr);

}

void BuildPlus()
{
    image_Plus = new Image(48,48);
    image_Plus->FillRect(0,0,48,48, PixOp_SRC, bg, ZOp_SRC, 0);

    PathAdapter a;

    a.outputMatrix = dMatrix2D::Scale({(double) image_Plus->Width, (double) image_Plus->Height});

    a.Line({.25,.5}, {.75,.5});

    a.Line({.5,.25}, {.5,.75});

    a.Apply(image_Plus);

    image_Plus->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / image_Plus->Width, &line, nullptr);
}

void BuildConnect() {
    image_Connect = new Image(48, 48);
    image_Connect->FillRect(0, 0, 48, 48, PixOp_SRC, bg, ZOp_SRC, 0);

    PathAdapter a;

    a.outputMatrix = dMatrix2D::Scale({(double) image_Connect->Width, (double) image_Connect->Height});

    double d = 1.0/16;
    a.inputMatrix *= dMatrix2D::Scale({1.0/(1.0+d*8),1.0/(1.0+d*8)});

    a.inputMatrix *= dMatrix2D::Translate({-.5,-.5}) * dMatrix2D::Rotate(-M_PI*2.0/4) * dMatrix2D::Translate({.5,.5});

    //a.inputMatrix *= dMatrix2D::Translate({-1.0,-.5}) * dMatrix2D::Rotate(-M_PI*2.0/8) * dMatrix2D::Translate({1,.5});

    //a.Line({1.0, .5 +d*2},{1.0, .5-d*2});
   // a.LineTo({1.0+d*2,.5});
    //a.LineTo({1.0,.5+d*2});

    //a.inputMatrix *= dMatrix2D::Translate({-1.0,-.5}) * dMatrix2D::Rotate(M_PI*2.0/8) * dMatrix2D::Translate({1.0,.5});

    dPnt2D c = a.inputMatrix * dPnt2D {1.0,.5};

    a.inputMatrix *= dMatrix2D::Translate({-c.x,-c.y}) * dMatrix2D::Rotate(M_PI*2.0/8) * dMatrix2D::Translate({c.x,c.y});

    a.Line({1.0+d*2,.5},{1.0-d*2,.5});
    a.LineTo({1.0,.5+d*2});
    a.LineTo({1.0+d*2,.5});

    a.inputMatrix *= dMatrix2D::Translate({-c.x,-c.y}) * dMatrix2D::Rotate(-M_PI*2.0/8) * dMatrix2D::Translate({c.x,c.y});

    a.MoveTo({1.0,.5});

    for (double th = 0.0; th < M_PI * 2 * 3 / 4; th+=M_PI*2/16)
    {
        a.inputMatrix *= dMatrix2D::Translate({-.5,-.5}) * dMatrix2D::Rotate(M_PI*2.0/16) * dMatrix2D::Translate({.5,.5});

        a.LineTo({1.0,.5});
    }

    a.Apply(image_Connect);

    image_Connect->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / image_Connect->Width, &line, nullptr);
}




Wij::Wij(QWidget *parent) : QWidget(parent)
{
    BuildDivide();
    BuildMove();
    BuildPlus();
    BuildConnect();

}

void Wij::paintEvent(QPaintEvent *evt)
{
    QPainter *P = new QPainter(this);

    int w = image_Divide->Width;
    int h = image_Divide->Height;

    QImage I(w,h, QImage::Format_RGBA8888);

    GfxBlt(PixType_ARGB, image_Divide->imageMemory,0, 0, w,h, w,
            PixType_RGBA, I.bits(), 0,0,w,h,w);

    P->drawImage(0,2, I);

    GfxBlt(PixType_ARGB, image_Move->imageMemory,0, 0, w,h, w,
           PixType_RGBA, I.bits(), 0,0,w,h,w);

    P->drawImage(52,2, I);

    GfxBlt(PixType_ARGB, image_Plus->imageMemory,0, 0, w,h, w,
           PixType_RGBA, I.bits(), 0,0,w,h,w);

    P->drawImage(52*2,2, I);

    GfxBlt(PixType_ARGB, image_Connect->imageMemory,0, 0, w,h, w,
           PixType_RGBA, I.bits(), 0,0,w,h,w);

    P->drawImage(52*3,2, I);

    P->end();
    delete P;
}