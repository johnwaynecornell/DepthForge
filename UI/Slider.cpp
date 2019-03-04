//
// Created by jwc on 2/19/19.
//

#include "Slider.h"

Slider::Slider(UI *parent, const char *label) : UI(parent)
{
    v = 0;
    this->label = label;
    element = new Element(this, 16, 24);

    element->xPos.setResp(Resp_Self);
    element->yPos.setResp(Resp_Self);

    element->width.setResp(Resp_Parent);
    element->height.setResp(Resp_Parent);

    src = nullptr;

    vCallback = {0,0,0};
}


Slider::~Slider()
{
    if (src != nullptr) delete src;
}

void Slider::setV(double val)
{
    if (val<0) val=0;
    if (val>1) val=1;

    bool c = v != val;

    v = val;

    updateElementPosition();

    if (c && vCallback.function != nullptr)
    {
        vCallback.function(vCallback.element, v, vCallback.argument);
    }
}

void Slider::setVCallvack(void (*proc)(void *, double, void *), void *elem, void *arg)
{
    vCallback = { elem, proc, arg };
}

bool sliderPixFunc(int index, double y, ARGB &p, float &z, void *arg)
{
    int xc = *((int *)arg);
    xc >>= 1;

    double q = abs(y);

    q = abs(q - (xc - 3));

    z = .06125 + sin(abs(y) / xc * M_PI / 2.0)*.125;

    z = -.125;

    if (q>=0 && q<=3)
    {
        q = 1.0 - q / 3;

        unsigned char _y = (unsigned char)((q)*0xFF);

        p = {_y,_y,_y, _y};


        //z = - y * .125;
        //z = 0;

        return true;
    }

    if (abs(y)<xc)
    {
        p = {0xFF,0x60,0x60,0x60};
        //z = 0;

        return true;
    }

    return false;
}


void Slider::makeSrc()
{
    int _w = width.get();
    int _h = height.get();

    if (src != nullptr && _w == src->Width && _h == src->Height) return;

    if (src != nullptr) delete src;

    src = new Image(_w,_h);

    int xc = _w / 2;

    src->Line(xc+(xc>>1), 6, xc+(xc>>1), _h-6);

    src->DrawPath(PixOp_SRC_ALPHA,ZOp_SRC_ADD, 1, sliderPixFunc, &xc);

    QImage *i = new QImage((unsigned char *) src->imageMemory, src->Width, src->Height,
            QImage::Format_ARGB32);

    QPainter *p = new QPainter(i);

    double osz = 1;
    double sz;

    int w;

    do
    {
        sz = osz;

        QFont f;
        f = p->font();

        f.setPointSizeF(osz);

        p->setFont(f);

        w = p->fontMetrics().boundingRect(label).height();

        osz+=.1;
    } while(w < (xc-1));

    QFont f;
    f = p->font();

    f.setPointSizeF(sz);

    p->setFont(f);

    int __w = p->fontMetrics().boundingRect(label).width();

    p->translate(_w/2-3,_h);
    p->rotate(-90);

    p->setPen(QColor(0xFF,0xFF,0xFF,0xFF));
    p->drawText((_h-__w)/2,0, QApplication::tr(label));

    p->end();
    delete  p;
    delete i;

}

void Slider::drawBackground(UI *member, Image *target, QImage *qImage)
{
    UI::drawBackground(member, target, qImage);
}

void Slider::draw(Image *target, QImage *qImage)
{
    makeSrc();
    target->DrawImage(xReal,yReal, width.get(), height.get(),
                      PixOp_SRC_ALPHA, ZOp_SRC_ADD, src, 0,0,src->Width, src->Height);

    UI::draw(target, qImage);
}

void Slider::updateElementPosition()
{
    int y = (int) ((1.0-v) * (height.get()-element->height.get()-1));

    element->xPos.set(16);
    element->yPos.set(y);

    element->xReal = xReal + element->xPos.get();
    element->yReal = yReal + element->yPos.get();
}

bool Slider::selfLayout()
{
    bool rc = UI::selfLayout();

    return rc;
}

bool Slider::doLayout()
{
    bool rc = UI::doLayout();

    updateElementPosition();

    return rc;
}

void Slider::mouseEnter()
{
    UI::mouseEnter();
}

void Slider::mouseLeave()
{
    UI::mouseLeave();
}

bool Slider::mouseMove(int x, int y)
{
    bool rc = UI::mouseMove(x,y);

    return rc;
}

bool Slider::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    bool rc = UI::mouseButtonPress(x,y,button);

    return rc;
}

bool Slider::mouseButtonRelease(int x, int y, Qt::MouseButton button)
{
    bool rc = UI::mouseButtonRelease(x,y,button);

    return rc;
}

bool Slider::moveElement(int xd, int yd)
{
    int _y, y;

    _y = y = element->yPos.get();

    int h = height.get() - element->height.get() - 1;

    y = y + yd;

    if (y<0) y=0;
    if (y>h) y=h;

    setV(1.0-(y / (double) h));

    return _y != y;
}

bool elementPixFunc(int index, double y, ARGB &p, float &z, void *arg)
{

    y = abs(y);

    if (y>=0.0 && y<=1.0)
    {
        y =  1.0 - y;//abs((y - .5))*2;
        unsigned char _y = (unsigned char)((y)*0xFF);

        int a = y * 2 * 0xFF;
        if (a > 0xFF) a = 0xFF;

        p = {(unsigned  char) a, valValAlpha(0, _y, a),0, valValAlpha(0, _y, a)};


        z = - y * .125;
        z = 0;

        return true;

    }

    p = {0x00,0x00,0x00,0x00 };
    z = 0;

    return true;
}

Slider::Element::Element(Slider *slider, int width, int height) : UI(slider)
{
    this->width.set(width);
    this->height.set(height);

    src = new Image(width, height);

    int xc = width>>1;
    int yc = height>>1;

    int w = 3;

    src->MoveTo(xc, height-w);
    src->LineTo(width-w, yc);
    src->LineTo(xc, w);
    src->LineTo(w, yc);
    src->LineTo(xc, height-w);

    src->DrawPath(PixOp_SRC_ALPHA, ZOp_SRC_ADD, 1.0 / w, elementPixFunc, nullptr);

    mouseDown = false;
}

Slider::Element::~Element()
{
    delete src;
}

void Slider::Element::drawBackground(UI *member, Image *target, QImage *qImage)
{
    UI::drawBackground(member,target,qImage);
}

void Slider::Element::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);

    target->DrawImage(xReal,yReal, width.get(), height.get(),
            PixOp_SRC_ALPHA, ZOp_SRC_ADD, src, 0,0,src->Width, src->Height);
}

bool Slider::Element::selfLayout()
{
    bool rc = UI::selfLayout();

    return rc;
}

bool Slider::Element::doLayout()
{
    bool rc = UI::doLayout();
    return rc;
}

void Slider::Element::mouseEnter()
{
    UI::mouseEnter();
}

void Slider::Element::mouseLeave()
{
    UI::mouseLeave();
}

bool Slider::Element::mouseMove(int x, int y)
{
    bool rc = UI::mouseMove(x, y);

    if (mouseDown)
    {
        x += xReal;
        y += yReal;

        int xd = x - mouseX;
        int yd = y - mouseY;


        if (((Slider *)parent)->moveElement(xd,yd))
        {
            mouseX = x;
            mouseY = y;
        }

    }

    return rc;
}

bool Slider::Element::mouseButtonPress(int x, int y, Qt::MouseButton button) {
    bool rc = UI::mouseButtonPress(x, y, button);

    if (button == Qt::MouseButton::LeftButton)
    {
        mouseDown = true;
        mouseX = x + xReal;
        mouseY = y + yReal;

        grabMouse();
    }

    return rc;
}

bool Slider::Element::mouseButtonRelease(int x, int y, Qt::MouseButton button)
{
    bool rc = UI::mouseButtonRelease(x,y,button);

    //printf("mouseButtonRelease\n");

    if (button == Qt::MouseButton::LeftButton)
    {
        //printf("mouseButtonRelease left\n");
        mouseDown = false;

        releaseMouse();
    }

    return rc;
}