//
// Created by jwc on 4/2/19.
//

#include "Mode_Path.h"

extern "C"
{
#include <PixelGfx/JWC_PixelGfx.h>
}

#include <QtGui/QPainter>
#include <math.h>

#include "Image/PathAdapter.h"

#include "MainUI.h"

#include "Forge.h"

#include "MainWnd.h"

int _w = 48;
int _h = 48;

Mode_Path::Mode_Path(MainUI *mainUI) : Mode(mainUI)
{
    BuildDivide();
    BuildMove();
    BuildPlus();
    BuildConnect();
    BuildSelect();
    BuildShapeToggle();

    curSubModeButton = nullptr;
    subMode = SubMode_None;

    pathToolsCtl = new DepthForgeTabCtl(mainUI->tabs, QApplication::tr("Path"));

    pathToolsCtl->width.setResp(Resp_Child);
    pathToolsCtl->height.setResp(Resp_Parent);
    pathToolsCtl->xPos.setResp(Resp_Self);
    pathToolsCtl->yPos.setResp(Resp_Self);

    pathToolsCtl->xPos.set(0);
    pathToolsCtl->yPos.set(0);

    pathToolsCtl->tabPosition.set(mainUI->tabs->_tabPosition);
    mainUI->tabs->_tabPosition += 64 + 9;

    pathToolsCtl->myMode = this;

    pathToolsFixed = new Fixed(pathToolsCtl);

    pathToolsFixed->width.setResp(Resp_Child);
    pathToolsFixed->height.setResp(Resp_Parent);
    pathToolsFixed->xPos.setResp(Resp_Self);
    pathToolsFixed->yPos.setResp(Resp_Self);

    pathToolsFixed->xPos.set(0);
    pathToolsFixed->yPos.set(0);

    pathToolsFrame = new Frame(pathToolsFixed);

    pathToolsFrame->width.setResp(Resp_Child);
    pathToolsFrame->height.setResp(Resp_Child);
    pathToolsFrame->xPos.setResp(Resp_Self);
    pathToolsFrame->yPos.setResp(Resp_Self);

    pathToolsFrame->xPos.set(0);
    pathToolsFrame->yPos.set(0);

    pathOpsFrame = new Frame(pathToolsFixed);

    pathOpsFrame->width.setResp(Resp_Self);
    pathOpsFrame->height.setResp(Resp_Self);
    pathOpsFrame->xPos.setResp(Resp_Self);
    pathOpsFrame->yPos.setResp(Resp_Self);

    pathOpsFrame->width.set(10);
    pathOpsFrame->height.set(256);

    pathOpsFrame->xPos.set(0);
    pathOpsFrame->yPos.set(0);

    pathTools = new Fixed(pathToolsFrame);
    pathTools->width.setResp(Resp_Child);
    pathTools->height.setResp(Resp_Self);
    pathTools->xPos.setResp(Resp_Self);
    pathTools->yPos.setResp(Resp_Self);

    pathTools->xPos.set(0);
    pathTools->yPos.set(0);


    pathTools->width.set(_w*2+6);
    pathTools->height.set(256);

    pathOps = new Fixed(pathOpsFrame);
    pathOps->width.setResp(Resp_Child);
    pathOps->height.setResp(Resp_Self);
    pathOps->xPos.setResp(Resp_Self);
    pathOps->yPos.setResp(Resp_Self);

    pathOps->xPos.set(0);
    pathOps->yPos.set(0);


    pathOps->width.set(_w*2+6);
    pathOps->height.set(256);

    //pathTools->width.set(256+12);

    button_Divide = addButton(pathTools, 0, 0, image_Divide, image_Divide_t);
    button_Move = addButton(pathTools, _w+6, 0, image_Move, image_Move_t);
    button_Plus = addButton(pathTools, 0, _h+6, image_Plus, image_Plus_t);
    button_Select = addButton(pathTools, 0, (_h+6)*2, image_Select, image_Select_t);

    button_Connect = addButton2(pathTools, _w+6, _h+6, image_Connect, image_Connect_t);
    button_ShapeToggle = addButton2(pathOps, 0, 0, image_ShapeToggle, image_ShapeToggle_t);

    button_Divide->tag = (void *) SubMode_Divide;
    button_Move->tag = (void *) SubMode_Move;
    button_Plus->tag = (void *) SubMode_Plus;
    button_Connect->tag = (void *) SubMode_Connect;
    button_Select->tag = (void *) SubMode_Select;

    ARGB _1 = {0xFF,0xFF,0xFF,0x00};
    ARGB _2 = {0xFF,0x00,0xFF,0xFF};
    ARGB _3 = {0xFF,0xFF,0x00,0xFF};

    for (int i=0; i<5; i++)
    {
        double q = i/5.0;

        pathPixles[i] = _1.interpolate(_2, q);
        pathPixles[i+5] = _2.interpolate(_3, q);
        pathPixles[i+10] = _3.interpolate(_1, q);
    }

    pathPixles[15] = pathPixles[0];
}

void button_press(void *_This, Button*element, bool pressed, void *arg)
{
    Mode_Path *T = (Mode_Path *)_This;

    if (pressed)
    {
        if (T->curSubModeButton != nullptr && T->curSubModeButton != element)
            T->curSubModeButton->setToggled(false);

        element->toggle();

        if (element->isToggled())
        {
            T->curSubModeButton = (Button_Image *) element;
            T->subMode = (Mode_Path::SubMode) (long) (size_t) element->tag;
        }
        else {

            T->curSubModeButton = nullptr;
            T->subMode = Mode_Path::SubMode_None;
        }
    }
}

Button_Image *Mode_Path::addButton(UI *parent, int x, int y, Image *img, Image *img_t)
{
    Frame *f = new Frame(parent);

    Button_Image *r = new Button_Image(f);

    r->onPress = {this, r, &button_press, nullptr};

    r->setSource(img, false);
    r->setSource(img_t, true);

    r->xPos.setResp(Resp_Self);
    r->yPos.setResp(Resp_Self);

    r->width.setResp(Resp_Self);
    r->height.setResp(Resp_Self);

    r->xPos.set(0);
    r->yPos.set(0);

    r->z = -0;
    r->backColor = {0xFF, 0x40,0x00,0x80, .25};

    r->backgroundResp = Resp_Self;

    f->xPos.set(x);
    f->yPos.set(y);

    f->width.setResp(Resp_Child);
    f->height.setResp(Resp_Child);

    f->backgroundResp = Resp_Child;

    return r;
}

Button_Image *Mode_Path::addButton2(UI *parent, int x, int y, Image *img, Image *img_t)
{
    Frame *f = new Frame(parent);

    Button_Image *r = new Button_Image(f);

    //r->onPress = {this, r, &button_press, nullptr};

    r->setSource(img, false);
    r->setSource(img_t, true);

    r->xPos.setResp(Resp_Self);
    r->yPos.setResp(Resp_Self);

    r->width.setResp(Resp_Self);
    r->height.setResp(Resp_Self);

    r->xPos.set(0);
    r->yPos.set(0);

    r->z = -0;
    r->backColor = {0xFF, 0x40,0x00,0x80, .25};

    r->backgroundResp = Resp_Self;

    f->xPos.set(x);
    f->yPos.set(y);

    f->width.setResp(Resp_Child);
    f->height.setResp(Resp_Child);

    f->backgroundResp = Resp_Child;

    return r;
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

ARGB bg;
ARGB color;

void colors_toggled(bool toggled)
{
    if (!toggled) {
        bg = ARGB{0xFF, 0xA0, 0xA0, 0xA0};
        color = Normalize( ARGB {0xFF, 0x30, 0x5, 0x30});
    } else {
        bg = ARGB{0xFF, 0x20, 0x20, 0x20};
        color = Normalize( ARGB {0xFF, 0x30, 0x30, 0x5});
    }
}

bool line(int index, double v, ARGB &p, float &z, void *arg)
{
    if (abs(v)<=2/48.0) {
        p = color;
        z = 0;
        return true;
    }

    return false;
}

void Mode_Path::BuildDivide()
{
    PathAdapter a;

    a.inputMatrix = dMatrix2D::Translate({-.9,0}) * dMatrix2D::Rotate(-M_PI/5.0) * dMatrix2D::Translate({.9,0});
    a.inputMatrix *= dMatrix2D::Translate({0,.2});

    a.outputMatrix = dMatrix2D::Scale({(double) _w, (double) _h});

    a.Line({.9,.2}, {.9,.8});

    a.Line({.4,.5}, {.75,.5});

    a.Line({.75,.5-.1}, {.75, .5+.1});
    a.Line({.75,.5-.1}, {.9, .5});
    a.Line({.75, .5+.1}, {.9, .5});

    a._preservePath++;

    colors_toggled(false);

    image_Divide = new Image(_w,_h);
    image_Divide->FillRect(0,0,_w,_h, PixOp_SRC,bg, ZOp_SRC, 0);

    a.Apply(image_Divide);
    image_Divide->DrawPath(PixOp_SRC, ZOp_SRC_ADD,
            2.0 / _w, &line, nullptr);

    colors_toggled(true);

    image_Divide_t = new Image(_w,_h);
    image_Divide_t->FillRect(0,0,_w,_h, PixOp_SRC,bg, ZOp_SRC, 0);

    a.Apply(image_Divide_t);
    image_Divide_t->DrawPath(PixOp_SRC, ZOp_SRC_ADD,
            2.0 / _w, &line, nullptr);
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


void Mode_Path::BuildMove()
{
    PathAdapter a;

    a.inputMatrix *= dMatrix2D::Scale({1.0/8,1.0/10}) * dMatrix2D::Translate({1.0/8,1.0/10});;
    a.outputMatrix = dMatrix2D::Scale({(double) _w, (double) _h});

    a.Line({1,2}, {1,4});
    a.Line({2,1}, {2,4});
    a.Line({3,.5}, {3,4});
    a.Line({4,1.5}, {4,6});
    a.Line({4,6}, {6,4});

    a._preservePath++;
    colors_toggled(false);

    image_Move = new Image(_w,_h);
    image_Move->FillRect(0,0,_w,_h, PixOp_SRC, bg, ZOp_SRC, 0);

    a.Apply(image_Move);

    image_Move->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / _w, &finger, nullptr);

    colors_toggled(true);
    image_Move_t = new Image(_w,_h);
    image_Move_t->FillRect(0,0,_w,_h, PixOp_SRC, bg, ZOp_SRC, 0);

    a.Apply(image_Move_t);

    image_Move_t->DrawPath(PixOp_SRC, ZOp_SRC_ADD,
            2.0 / _w, &finger, nullptr);



    a.ClearPath();

    a.Line({1,4},{4,4});
    a.LineTo({4,6});
    a.LineTo({3,8});
    a.LineTo({1.5,8});
    a.LineTo({1,4});

    a._preservePath++;

    colors_toggled(false);
    a.Apply(image_Move);
    image_Move->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / _w, &hand, nullptr);

    colors_toggled(true);
    a.Apply(image_Move_t);
    image_Move_t->DrawPath(PixOp_SRC, ZOp_SRC_ADD,
            2.0 / _w, &hand, nullptr);

}

void Mode_Path::BuildPlus()
{
    PathAdapter a;

    a.outputMatrix = dMatrix2D::Scale({(double) _w, (double) _h});

    a.Line({.25,.5}, {.75,.5});

    a.Line({.5,.25}, {.5,.75});

    a._preservePath++;

    colors_toggled(false);

    image_Plus = new Image(_w,_h);
    image_Plus->FillRect(0,0,_w,_h, PixOp_SRC, bg, ZOp_SRC, 0);
    a.Apply(image_Plus);

    image_Plus->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / _w, &line, nullptr);

    colors_toggled(true);

    image_Plus_t = new Image(_w,_h);
    image_Plus_t->FillRect(0,0,_w,_h, PixOp_SRC, bg, ZOp_SRC, 0);
    a.Apply(image_Plus_t);

    image_Plus_t->DrawPath(PixOp_SRC, ZOp_SRC_ADD,
            2.0 / _w, &line, nullptr);
}

void Mode_Path::BuildConnect() {
    PathAdapter a;

    a.outputMatrix = dMatrix2D::Scale({(double) _w, (double) _h});

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

    a._preservePath++;

    colors_toggled(false);
    image_Connect = new Image(_w, _h);
    image_Connect->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);

    a.Apply(image_Connect);

    image_Connect->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / _w, &line, nullptr);

    colors_toggled(true);
    image_Connect_t = new Image(_w, _h);
    image_Connect_t->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);

    a.Apply(image_Connect_t);

    image_Connect_t->DrawPath(PixOp_SRC, ZOp_SRC_ADD,
            2.0 / _w, &line, nullptr);
}

void Mode_Path::BuildSelect() {
    PathAdapter a;

    a.outputMatrix = dMatrix2D::Scale({(double) _w, (double) _h});

    a.inputMatrix = dMatrix2D::Translate({.5,0});

    a.Line({.025,.9}, {-.025,.9});
    a.LineTo({-.025,.5});
    a.LineTo({-.3,.5});
    a.LineTo({0,.1});

    a.LineTo({.3,.5});
    a.LineTo({.025,.5});
    a.LineTo({.025,.9});

    a._preservePath++;

    colors_toggled(false);
    image_Select = new Image(_w, _h);
    image_Select->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);

    a.Apply(image_Select);
    image_Select->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / _w, &hand, nullptr);

    colors_toggled(true);
    image_Select_t = new Image(_w, _h);
    image_Select_t->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);

    a.Apply(image_Select_t);
    image_Select_t->DrawPath(PixOp_SRC, ZOp_SRC_ADD, 2.0 / _w, &hand, nullptr);

}

void Swap(dPnt2D &A, dPnt2D &B)
{
    dPnt2D a = A;
    A = B;
    B = a;
}

struct HighlightParams
{
    double min;
    double max;
};

bool highlight(int I, double X, ARGB &P, float &Z, void *arg)
{
    HighlightParams *params = (HighlightParams *)arg;

    if (X>=0)
    {
        double v = X / params->max;

        unsigned char z = (unsigned char) ((v)* 0xFF);


        P = color;//{z,0xFF,0xFF,0xFF};
        P.a = z;
        Z = (- v) * .25;

        return true;
    }

    return false;
}

bool highlight2(int I, double X, ARGB &P, float &Z, void *arg)
{
    if (X>=0)
    {
        P = color;//{0xFF,0xFF,0xFF,0xFF};
        Z = .25;

        return true;
    }

    return true;
}


void Mode_Path::BuildShapeToggle()
{
    PathAdapter a;

    colors_toggled(false);

    image_ShapeToggle = new Image(_w, _h);
    image_ShapeToggle_t = new Image(_w, _h);

    image_ShapeToggle->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);
    image_ShapeToggle_t->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);

    dPnt2D pnt = {1,-.05};
    dPnt2D pnt2;
    dPnt2D pnt3;

    dPnt2D A = pnt;
    dPnt2D B;

    a.MoveTo(pnt);

    //printf("{%lf,%lf}\n", pnt.x,pnt.y);

    pnt2 = pnt + dPnt2D::sinCos(M_PI / 2.0 + M_PI / 50.0)*.4;

    a.LineTo(pnt2);

    //printf("{%lf,%lf}\n", pnt2.x,pnt2.y);

    pnt3 = pnt2 + dPnt2D::sinCos((pnt2-pnt).atan2() + M_PI / 2.0 - M_PI / 20.0)*.3;

    a.LineTo(pnt3);

    //printf("{%lf,%lf}\n", pnt3.x,pnt3.y);

    pnt = pnt2;
    pnt2 = pnt3;

    pnt3 = pnt2 + dPnt2D::sinCos((pnt2-pnt).atan2() + M_PI / 2.0 - M_PI / 20.0)*.7;

    a.LineTo(pnt3);

    //printf("{%lf,%lf}\n", pnt3.x,pnt3.y);

    pnt = pnt2;
    pnt2 = pnt3;

    pnt3 = pnt2 + dPnt2D::sinCos((pnt2-pnt).atan2() + M_PI / 2.0 + M_PI / 15.0)*.3;

    a.LineTo(pnt3);

    //printf("{%lf,%lf}\n", pnt3.x,pnt3.y);

    pnt = pnt2;
    pnt2 = pnt3;

    B = pnt2;

    pnt = (B-A)/2;

    double r = pnt.len();

    //pnt = pnt + A;

    pnt = A + pnt- dPnt2D::sinCos(pnt.atan2()-M_PI/2.0)* r / 2.0;

    r = (pnt-A).len();


    double th1 = (B-pnt).atan2();
    double th2 = (A-pnt).atan2();

    if (th2>th1) th2 -= M_PI * 2.0;

    for (double th = th1; th >= th2; th-=(th1-th2)/8.0)
    {
        a.LineTo(pnt+dPnt2D::sinCos(th)*r);
    }

    a.BoundingBox(A,B);

    A = A - dPnt2D {.05,.05};
    B = B + dPnt2D {.05,.05};

    a.outputMatrix = dMatrix2D::Translate(A.negate()) *dMatrix2D::Scale(dPnt2D {(double) _w, (double) _h}
                                                                         / dPnt2D {B-A});


    a._preservePath++;

    a.Apply(image_ShapeToggle);

    HighlightParams params;

    image_ShapeToggle->DrawPath(PixOp_SRC_ALPHA, ZOp_SRC, 1.0,
            &params.min, &params.max, highlight, &params);


    a.Apply(image_ShapeToggle_t);

    image_ShapeToggle_t->DrawPath(PixOp_SRC_ALPHA, ZOp_SRC, 1.0,
                                highlight2, nullptr);






}


struct outLineFuncArgs
{
    int o;
    Mode_Path *m;
};

bool outLineFunc(int I, double X, int x, int xD, ARGB &P, float &Z, void *arg)
{
    outLineFuncArgs *a = (outLineFuncArgs *)arg;

    int o = a->o;
    int xx = (int) X + x + o;

    /*
    bool c = ((xx>>3)%2) == 1;

    if (c) P = {0xFF,0xFF,0xFF,0xFF}; else P = {0xFF,0x00,0x00,0x00};
*/
    P = a->m->pathPixles[xx%16];
    
    Z = 0;

    return true;
}

int Mode_Path::nearest(dPnt2D c)
{
    double x = INFINITY;
    int _i = -1;

    int i =0;

    for (std::list<dPnt2D>::iterator it = points.begin(); it != points.end(); it++)
    {
        dPnt2D Q = (*it)-c;

        if (!isinf(Q.x)) {
            double _x = Q.len();

            if (_x < x) {
                x = _x;
                _i = i;
            }
        }

        i++;
    }

    return _i;
}

void Mode_Path::drawForge(Forge *forge, Image *target, QImage *qImage) {
    pth.outputMatrix = dMatrix2D::Scale({(double) forge->_w, (double) forge->_h}) *
                       dMatrix2D::Translate({(double) forge->_x, (double) forge->_y});

    pth._preservePath++;

    pth.Apply(target);

    double time = forge->getTimeInSeconds();

    int t = (int)(time * 32);
    t %= 32;
    t = 31 - t;

    outLineFuncArgs args;
    args.o = t;
    args.m = this;

    target->DrawPathOutline(PixOp_SRC, ZOp_SRC_ADD, outLineFunc, &args);

    PathAdapter pa1,pa2,pa3;
    pa1.outputMatrix = pa2.outputMatrix = pa3.outputMatrix= pth.outputMatrix;

    int i;

    i = 0;
    for (std::list<dPnt2D>::iterator q = points.begin(); q != points.end(); q++)
    {
        dPnt2D &c = *q;

        if (!isinf(c.x))
        {
            if (i == selectedPnt)
            {
                pa2.Line({c.x - .01, c.y - .01}, {c.x + .01, c.y + .01});
                pa2.Line({c.x + .01, c.y - .01}, {c.x - .01, c.y + .01});

            } else {
                pa1.Line({c.x - .01, c.y - .01}, {c.x + .01, c.y + .01});
                pa1.Line({c.x + .01, c.y - .01}, {c.x - .01, c.y + .01});
            }
        }

        i++;
    }

    time = abs((time - trunc(time)-.5)*2);

    unsigned char alpha = (unsigned char)(0xFF*time);

    pa1.Apply(target);
    target->DrawPath(PixOp_SRC_ALPHA, {alpha,0xFF,0xFF,0xFF}, ZOp_SRC, 0);

    pa2.Apply(target);
    target->DrawPath(PixOp_SRC_ALPHA, {alpha,0xFF,0xFF,0x00}, ZOp_SRC, 0);

    if (subMode == SubMode_Select)
    {
        int n = nearest({forge->mouseX,forge->mouseY});

        if (n != -1) {

            std::list<dPnt2D>::iterator it = points.begin();

            for (int i = 0; i < n; i++) it++;

            pa3.inputMatrix = dMatrix2D::Translate(*it);

            double th = 0.0;

            pa3.MoveTo({sin(th) * .015, cos(th) * .015});

            double thd = M_PI / 4.0;

            for (th = thd; th <= M_PI * 2.0; th += thd) pa3.LineTo({sin(th) * .015, cos(th) * .015});

            pa3.Apply(target);
            target->DrawPath(PixOp_SRC_ALPHA, {alpha, 0xFF, 0xFF, 0x00}, ZOp_SRC, 0);
        }
    }


    if (subMode == SubMode_Divide && nearestIndex != -1) {
        dPathEntry *pe = pth.path + nearestIndex;

        if (pe->point == false) {
            dPnt2D d = pe->B-pe->A;

            double th = atan2(d.y,d.x);

            PathAdapter _pth;

            _pth.outputMatrix = dMatrix2D::Scale({(double) forge->_w, (double) forge->_h}) *
                               dMatrix2D::Translate({(double) forge->_x, (double) forge->_y});


            _pth.inputMatrix = dMatrix2D::Rotate(-th) * dMatrix2D::Translate(pe->A);

            _pth.Line({nearestX, -.1}, {nearestX, 0});
            _pth.Line({nearestX, -0}, {nearestX-.01, -.01});
            _pth.Line({nearestX, -0}, {nearestX+.01, -.01});

            _pth.Apply(target);

            target->DrawPath(PixOp_SRC, {0xFF, 0xFF, 0xFF, 0x00}, ZOp_SRC_ADD, 0.0f);
        }
    }
}


bool Mode_Path::mouseMoveForge(Forge *forge, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if (subMode == SubMode_Divide)
    {
        pth.Nearest({forge->mouseX, forge->mouseY}, nearestIndex, nearestX);

    }
    return true;
}

void Mode_Path::refreshPth()
{
    pth.ClearPath();

    bool New = true;

    int p = -1;

    for (std::list<dPnt2D>::iterator i = points.begin(); i != points.end(); i++)
    {
        if (isinf((*i).x)) New = true;
        else
        {
            if (New) pth.MoveTo(*i); else
            {
                pth.LineTo(*i);
                pth.path[pth.pathIndex-1].data = (void *) p;
            }

            New = false;
        }

        p++;
    }
}

bool Mode_Path::mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    if (subMode == SubMode_Plus)
    {
        dPnt2D c = {forge->mouseX, forge->mouseY};

        if (button == Qt::MouseButton::LeftButton) {

            std::list<dPnt2D>::iterator it = points.begin();

            int i;
            for (i=0; i<selectedPnt; i++) it++;

            selectedPnt = i;

            points.insert(it, c);
            refreshPth();

        } else if (button == Qt::MouseButton::RightButton)
        {
            pth.MoveTo(c);

            points.push_back({INFINITY,INFINITY});

            selectedPnt = points.size();

            points.push_back(c);


        }

        pointsCurrent = points.size()-1;
    } else if (subMode == SubMode_Divide)
    {
        if (button == Qt::MouseButton::LeftButton) {
            pth.Nearest({forge->mouseX, forge->mouseY}, nearestIndex, nearestX);

            if (nearestIndex != -1) {
                dPathEntry &pe = pth.path[nearestIndex];

                int p = (int) (size_t) pe.data;

                dPnt2D _c = {nearestX, 0};

                dPnt2D d = pe.B-pe.A;

                double th = atan2(d.y,d.x);

                dMatrix2D Matrix = dMatrix2D::Rotate(-th) * dMatrix2D::Translate(pe.A);
                _c = Matrix * _c;

                std::list<dPnt2D> points2 = points;

                points.clear();

                int i = 0;

                for (std::list<dPnt2D>::iterator c = points2.begin(); c != points2.end(); c++) {
                    points.push_back(*c);
                    if (i == p) points.push_back(_c);
                    i++;
                }

                refreshPth();
                pointsCurrent = points.size()-1;
            }
        }
    }else if (subMode == SubMode_Select) {
        if (button == Qt::MouseButton::LeftButton)
        {
            selectedPnt = nearest({forge->mouseX,forge->mouseY});

        }
    }

    return true;
}

bool Mode_Path::mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    return true;
}

void Mode_Path::selfLayout()
{
    pathToolsCtl->height.set(mainUI->height.get());
}

void Mode_Path::doLayout()
{
    pathOpsFrame->xPos.set(0);
    pathOpsFrame->yPos.set(pathToolsFixed->height.get()-pathOpsFrame->height.get()-1);

    pathOpsFrame->width.set(pathToolsFrame->width.get());
}
