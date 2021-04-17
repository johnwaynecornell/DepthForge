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

void connect_press(void *_This, Button*element, bool pressed, void *arg);
void clear_press(void *_This, Button*element, bool pressed, void *arg);

int _w = 48;
int _h = 48;

void ancillary_press(void *_This, Button*element, bool pressed, void *arg);
void ancillary_update(void *_This, Button_Image *E, void *arg);

Mode_Path::Mode_Path(MainUI *mainUI) : Mode(mainUI)
{
    BuildDivide();
    BuildMove();
    BuildPlus();
    BuildConnect();
    BuildSelect();
    BuildClear();

    BuildShapeToggle();
    BuildShapeCurveToggle();

    curSubModeButton = nullptr;
    subMode = SubMode_None;

    tabCtl = new DepthForgeTabCtl(mainUI->tabs, QApplication::tr("Path"));

    tabCtl->width.setResp(Resp_Child);
    tabCtl->height.setResp(Resp_Parent);
    tabCtl->xPos.setResp(Resp_Self);
    tabCtl->yPos.setResp(Resp_Self);

    tabCtl->xPos.set(0);
    tabCtl->yPos.set(0);

    tabCtl->tabPosition.set(mainUI->tabs->_tabPosition);
    mainUI->tabs->_tabPosition += 64 + 9;

    tabCtl->myMode = this;

    pathToolsFixed = new Fixed(tabCtl);

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
    
    pathButtonsFrame = new Frame(pathToolsFixed);

    pathButtonsFrame->width.setResp(Resp_Child);
    pathButtonsFrame->height.setResp(Resp_Child);
    pathButtonsFrame->xPos.setResp(Resp_Self);
    pathButtonsFrame->yPos.setResp(Resp_Self);

    pathButtonsFrame->xPos.set(0);
    pathButtonsFrame->yPos.set(0);

    ancillaryFrame = new Frame(pathToolsFixed);

    ancillaryFrame->width.setResp(Resp_Child);
    ancillaryFrame->height.setResp(Resp_Child);

    ancillaryFrame->backgroundResp = Resp_Child;


    ancillaryView = new Button_Image(ancillaryFrame);

    ancillaryView->width.setResp(Resp_Self);
    ancillaryView->height.setResp(Resp_Self);
    ancillaryView->xPos.setResp(Resp_Self);
    ancillaryView->yPos.setResp(Resp_Parent);

    //ancillaryView->height.set((lenssz+ border)*2);
    //ancillaryView->width.set((lenssz+ border)*2);
    ancillaryView->xPos.set(0);
    ancillaryView->yPos.set(0);

    ancillaryImage = new Image(1, 1);
    ancillaryView->setSource(ancillaryImage, false);

    ancillaryView->onPress = {this,ancillaryView, &ancillary_press, nullptr};
    ancillaryView->onUpdateSrc = { this, ancillaryView, &ancillary_update, nullptr};

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
    pathTools->height.setResp(Resp_Child);
    pathTools->xPos.setResp(Resp_Self);
    pathTools->yPos.setResp(Resp_Self);

    pathTools->xPos.set(0);
    pathTools->yPos.set(0);
    
    pathTools->width.set(_w*3+6);
    pathTools->height.set(256);

    pathButtons = new Fixed(pathButtonsFrame);
    pathButtons->width.setResp(Resp_Child);
    pathButtons->height.setResp(Resp_Child);
    pathButtons->xPos.setResp(Resp_Self);
    pathButtons->yPos.setResp(Resp_Parent);

    pathButtons->xPos.set(0);
    pathButtons->yPos.set(0);

    pathButtons->width.set(_w*3+6);
    pathButtons->height.set(256);

    pathOps = new Fixed(pathOpsFrame);
    pathOps->width.setResp(Resp_Child);
    pathOps->height.setResp(Resp_Self);
    pathOps->xPos.setResp(Resp_Self);
    pathOps->yPos.setResp(Resp_Self);

    pathOps->xPos.set(0);
    pathOps->yPos.set(0);


    pathOps->width.set(_w*3+6);
    pathOps->height.set(256);

    //pathTools->width.set(256+12);

    button_Divide = addButton(pathTools, 0, 0, image_Divide, image_Divide_t);
    button_Move = addButton(pathTools, _w+6, 0, image_Move, image_Move_t);
    button_Select = addButton(pathTools, (_w+6)*2, 0, image_Select, image_Select_t);
    button_Plus = addButton(pathTools, 0, _h+6, image_Plus, image_Plus_t);

    button_Connect = addButton2(pathButtons, _w+6, 0, image_Connect, image_Connect_t);
    button_Clear = addButton2(pathButtons, 0, 0, image_Clear, image_Clear_t);

    button_ShapeToggle = addButton(pathOps, 0, 0, image_ShapeToggle, image_ShapeToggle_t);
    button_ShapeCurveToggle = addButton(pathOps, 0, _h+6, image_ShapeCurveToggle, image_ShapeCurveToggle_t);

    slide_Offset = new Slider(pathOps, "Offset", true, false);
    slide_Offset->width.setResp(Resp_Self);
    slide_Offset->height.setResp(Resp_Self);
    slide_Offset->xPos.setResp(Resp_Self);
    slide_Offset->yPos.setResp(Resp_Self);

    slide_Offset->height.set(256 - 3 * 2);
    slide_Offset->width.set(32);
    slide_Offset->xPos.set(pathOps->width.get() - (slide_Offset->width.get())*2-3);
    slide_Offset->yPos.set(0);

    slide_Intensity = new Slider(pathOps, "Intensity", true, false);
    slide_Intensity->width.setResp(Resp_Self);
    slide_Intensity->height.setResp(Resp_Self);
    slide_Intensity->xPos.setResp(Resp_Self);
    slide_Intensity->yPos.setResp(Resp_Self);

    slide_Intensity->height.set(256 - 3 * 2);
    slide_Intensity->width.set(32);
    slide_Intensity->xPos.set(pathOps->width.get() - slide_Intensity->width.get());
    slide_Intensity->yPos.set(0);

    button_Divide->tag = (void *) SubMode_Divide;
    button_ShapeToggle->tag = (void *) SubMode_Shape_Linear;
    button_ShapeCurveToggle->tag = (void *) SubMode_Shape_Curve;
    button_Move->tag = (void *) SubMode_Move;
    button_Plus->tag = (void *) SubMode_Plus;

    button_Connect->tag = (void *) SubMode_None;
    button_Clear->tag = (void *) SubMode_None;

    button_Select->tag = (void *) SubMode_Select;

    button_Connect->onPress = {this, button_Connect, &connect_press, nullptr};
    button_Clear->onPress = {this, button_Clear, &clear_press, nullptr};

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

Mode_Path::~Mode_Path()
{
    if (shapeDrawZbuf != nullptr) delete shapeDrawZbuf;
}

void Mode_Path::changeSubMode(SubMode mode)
{
    subMode = mode;

    if (mode != SubMode_Shape_Curve && mode != SubMode_Shape_Linear) doShapeDraw = false;
}

void connect_press(void *_This, Button*element, bool pressed, void *arg) {
    Mode_Path *T = (Mode_Path *) _This;
    element->toggle();

    if (pressed) {
        T->points.push_back(*T->points.begin());
        T->refreshPth();
    }
}

void clear_press(void *_This, Button*element, bool pressed, void *arg) {
    Mode_Path *T = (Mode_Path *) _This;
    element->toggle();

    if (pressed) {
        T->points.clear();
        T->refreshPth();
    }
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
            T->changeSubMode((Mode_Path::SubMode) (long) (size_t) element->tag);
        }
        else {

            T->curSubModeButton = nullptr;
            T->changeSubMode(Mode_Path::SubMode_None);
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

    f->xPos.setResp(Resp_Self);
    f->yPos.setResp(Resp_Self);

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

void textOutMatchWidth(Image *I, int width, char *txt, ARGB color)
{
    QImage *i = new QImage(I->Width, I->Height,QImage::Format_ARGB32);

    GfxBlt(PixType_ARGB, I->imageMemory, 0, 0, I->Width, I->Height, I->stride,
           PixType_BGRA, i->bits(), 0, 0, i->width(), i->height(), i->width());

    QPainter *p = new QPainter(i);

    double osz = 1;
    double sz;

    int w;

    do {
        sz = osz;

        QFont f;
        f = p->font();

        f.setPointSizeF(osz);

        p->setFont(f);

        w = p->fontMetrics().boundingRect(txt).width();

        osz += .1;
    } while (w < (width - 1));

    QFont f;
    f = p->font();

    f.setPointSizeF(sz);

    p->setFont(f);

    QRect rect = p->fontMetrics().boundingRect(txt);
    int __w = rect.width();
    int __h = rect.height();

    p->setPen(QColor::fromRgb(color.r,color.g,color.b, color.a));
    p->drawText((I->Width-__w) / 2,  (I->Height+__h/2)/2, QApplication::tr(txt));

    GfxBlt(PixType_BGRA, i->bits(), 0, 0, i->width(), i->height(), i->width(),
           PixType_ARGB, I->imageMemory, 0, 0, I->Width, I->Height, I->stride);

    p->end();
    delete p;
    delete i;

}

void Mode_Path::BuildClear() {

    colors_toggled(false);
    image_Clear = new Image(_w, _h);
    image_Clear->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);

    textOutMatchWidth(image_Clear, image_Clear->Width-3, "Clear", color);

    colors_toggled(true);
    image_Clear_t = new Image(_w, _h);
    image_Clear_t->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);

    textOutMatchWidth(image_Clear_t, image_Clear_t->Width-3, "Clear", color);
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
    int mode;
};

bool highlight(int I, double X, ARGB &P, float &Z, void *arg)
{
    HighlightParams *params = (HighlightParams *)arg;

    if (X>=0)
    {
        double v = X / params->max;

        if (params->mode==1) v = sin(v * M_PI / 2.0);

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
    HighlightParams *params = (HighlightParams *)arg;

    if (X>=0)
    {
        double v = 1.0-(X / params->max);

        unsigned char z = (unsigned char) ((v)* 0xFF);

        P = color;//{z,0xFF,0xFF,0xFF};
        P.a = z;
        Z = (- v) * .25;

        return true;
    }

    return false;
}


void Mode_Path::BuildShapeToggle()
{
    PathAdapter a;

    colors_toggled(false);

    image_ShapeToggle = new Image(_w, _h);
    image_ShapeToggle_t = new Image(_w, _h);

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

    params.mode = 0;
    colors_toggled(false);

    image_ShapeToggle->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);
    image_ShapeToggle->DrawPath(PixOp_SRC_ALPHA, ZOp_SRC, 1.0,
            &params.min, &params.max, highlight, &params);


    a.Apply(image_ShapeToggle_t);

    colors_toggled(true);
    image_ShapeToggle_t->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);
    image_ShapeToggle_t->DrawPath(PixOp_SRC_ALPHA, ZOp_SRC, 1.0,
                                &params.min, &params.max, highlight, &params);

}

void Mode_Path::BuildShapeCurveToggle()
{
    PathAdapter a;

    colors_toggled(false);

    image_ShapeCurveToggle = new Image(_w, _h);
    image_ShapeCurveToggle_t = new Image(_w, _h);

    dPnt2D L = dPnt2D::sinCos(0);

    a.MoveTo(L);

    for (double th = M_PI * 2/8; th < M_PI*2; th += M_PI * 2/8)
    {
        dPnt2D c = dPnt2D::sinCos(th);
        a.LineTo(c);
    }

    a.LineTo(L);

    dPnt2D A,B;

    a.BoundingBox(A,B);

    A = A - dPnt2D {.05,.05};
    B = B + dPnt2D {.05,.05};

    a.outputMatrix = dMatrix2D::Translate(A.negate()) *dMatrix2D::Scale(dPnt2D {(double) _w, (double) _h}
                                                                        / dPnt2D {B-A});


    a._preservePath++;

    a.Apply(image_ShapeCurveToggle);

    HighlightParams params;
    params.mode = 1;

    colors_toggled(false);

    image_ShapeCurveToggle->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);
    image_ShapeCurveToggle->DrawPath(PixOp_SRC_ALPHA, ZOp_SRC, 1.0,
                                &params.min, &params.max, highlight, &params);


    a.Apply(image_ShapeCurveToggle_t);

    colors_toggled(true);
    image_ShapeCurveToggle_t->FillRect(0, 0, _w, _h, PixOp_SRC, bg, ZOp_SRC, 0);
    image_ShapeCurveToggle_t->DrawPath(PixOp_SRC_ALPHA, ZOp_SRC, 1.0,
                                  &params.min, &params.max, highlight, &params);

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

void Mode_Path::updateSrc(Forge *forge)
{
    if (doShapeDraw)
    {
        for (int y=0; y < forge->src->Height; y++)
        {
            for (int x = 0; x < forge->src->Width; x++)
            {
                long i = y*forge->src->Width+x;
                float z = shapeDrawZbuf[i];

                if (shapeDrawPositive)
                {
                    if (pathData[i].mv >=0)
                    {
                        double v = pathData[i].mv / shapeDrawMaxMv;
                        if (subMode == SubMode_Shape_Curve) v = sin(acos(1.0-v));
                        z += slide_Offset->v + slide_Intensity->v * v;
                    }
                } else
                {
                    if (pathData[i].mv <=0)
                    {
                        double v = pathData[i].mv / shapeDrawMinMv;
                        if (subMode == SubMode_Shape_Curve) v = sin(acos(1.0-v));
                        z += slide_Offset->v +  slide_Intensity->v * v;
                    }
                }

                forge->src->zMemory[i] = z;
            }
        }
    }
}

void Mode_Path::drawForge(Forge *forge, Image *target, QImage *qImage) {
    //pth.outputMatrix = dMatrix2D::Scale({(double) forge->_w, (double) forge->_h}) *
    //                   dMatrix2D::Translate({(double) forge->_x, (double) forge->_y});

    pth.outputMatrix =
            dMatrix2D::Scale({(double) forge->src->Width, (double) forge->src->Height}) *
            dMatrix2D::Translate( {(double) -forge->_srcX , (double) -forge->_srcY} ) *
            dMatrix2D::Scale({(double) forge->_w / forge->_srcW,
                              (double) forge->_h  / forge->_srcH}) *
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

            _pth.outputMatrix =
                    dMatrix2D::Scale({(double) forge->src->Width, (double) forge->src->Height}) *
                    dMatrix2D::Translate( {(double) -forge->_srcX , (double) -forge->_srcY} ) *
                    dMatrix2D::Scale({(double) forge->_w / forge->_srcW,
                                      (double) forge->_h  / forge->_srcH}) *
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
    if (subMode == SubMode_Divide)
    {
        pth.Nearest({forge->mouseX, forge->mouseY}, nearestIndex, nearestX);

    } else if (subMode == SubMode_Move)
    {
        if (mouseDown) {
            int deltaX = x - mouseX;
            int deltaY = y - mouseY;

            int i = 0;
            std::list<dPnt2D>::iterator p = points.begin();
            while (i < selectedPnt) {
                p++;
                i++;
            }

            dPnt2D q = *p;

            q.x += deltaX / (double) forge->_w * forge->_srcW / (double) forge->src->Width;// * forge->src->Width;
            q.y += deltaY / (double) forge->_h * forge->_srcH / (double) forge->src->Height;// * forge->src->Height;

            if (q.x<0) q.x=0; else if (q.x > 1.0) q.x = 1.0;
            if (q.y<0) q.y=0; else if (q.y > 1.0) q.y = 1.0;

            *p = q;

            refreshPth();
        }
    }

    mouseX = x;
    mouseY = y;

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

    pointsDirty = true;
}

void Mode_Path::applyShape(SubMode shape, int x, int y)
{
    Image *target = this->mainUI->forgeContainer->forge->src;

    if (pointsDirty)
    {
        if (pathData != nullptr) delete pathData;

        pth.outputMatrix = dMatrix2D::Scale({(double) target->Width, (double) target->Height});

        pth._preservePath++;

        pth.Apply(target);

        pathData = target->ComputePath();

        pointsDirty = false;

        shapeDrawMinMv = INFINITY;
        shapeDrawMaxMv = -INFINITY;

        for (int y=0; y<target->Height; y++)
        {
            for (int x=0; x<target->Width; x++)
            {
                double mv = pathData[y*target->Width+x].mv;
                if (mv<shapeDrawMinMv) shapeDrawMinMv = mv;
                if (mv>shapeDrawMaxMv) shapeDrawMaxMv = mv;
            }
        }
    }

    if (shapeDrawZbuf != nullptr) delete shapeDrawZbuf;

    shapeDrawZbuf = new float[target->Width*target->Height];

    for (int y=0; y<target->Height; y++) {
        for (int x = 0; x < target->Width; x++) {
            int i = y * target->Width + x;
            shapeDrawZbuf[i] = target->zMemory[i];
        }
    }

    //target->pix[y][x] = {0xFF,0xFF,0xFF,0xFF};

    shapeDrawPositive = pathData != nullptr && pathData[y*target->Width+x].mv>=0;
    doShapeDraw = true;
}

bool Mode_Path::mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    if (button == Qt::MouseButton::LeftButton) {
        mouseDown = true;
    }

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

//        pointsCurrent = points.size()-1;
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
                //pointsCurrent = points.size()-1;
            }
        }
    }else if (subMode == SubMode_Select)
    {
        if (button == Qt::MouseButton::LeftButton)
        {
            selectedPnt = nearest({forge->mouseX,forge->mouseY});

        }
    } else if (subMode == SubMode_Shape_Linear)
    {
        applyShape(SubMode_Shape_Linear, (int) (forge->mouseX*forge->src->Width), (int) (forge->mouseY*forge->src->Height));
    }
    else if (subMode == SubMode_Shape_Curve)
    {
        applyShape(SubMode_Shape_Curve, (int) (forge->mouseX*forge->src->Width), (int) (forge->mouseY*forge->src->Height));
    }

    return true;
}

bool Mode_Path::mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    if (button == Qt::MouseButton::LeftButton) {
        mouseDown = false;
    }

    return true;
}

void Mode_Path::selfLayout()
{
    tabCtl->height.set(mainUI->height.get());
    resizeAncillary(pathTools->width.get());
}

void Mode_Path::doLayout()
{
    pathOpsFrame->xPos.set(0);
    pathOpsFrame->yPos.set(pathToolsFixed->height.get()-pathOpsFrame->height.get()-1);

    pathOpsFrame->width.set(pathOps->width.get()+6);

    pathToolsFrame->xPos.set(0);
    pathToolsFrame->yPos.set(0);

    pathToolsFrame->width.set(pathTools->width.get()+6);

    pathButtonsFrame->xPos.set(0);
    pathButtonsFrame->yPos.set(pathToolsFrame->height.get());

    pathButtonsFrame->width.set(pathTools->width.get()+6);

    ancillaryFrame->xPos.set(0);
    ancillaryFrame->yPos.set(pathButtonsFrame->yPos.get() + pathButtonsFrame->height.get());
}
