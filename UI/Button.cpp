//
// Created by jwc on 2/15/19.
//

#include "UI.h"
#include <math.h>

Button::Button(UI *parent) : UI(parent)
{
    z = 0.0f;

    zAct = 0.0f;
    zTarg = 0.0f;
    zSpeed = .5f;

    lastDrawTime = INFINITY;
}

Button::~Button()
{

}

void Button::drawBackground(UI *member, Image *target, QImage *qImage)
{
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    drawTime = ts.tv_sec + ts.tv_nsec / 1000000000.0;
    if (qIsInf(lastDrawTime))
    {
        zTarg = z;
        lastDrawTime = drawTime;
    }

    double e = drawTime - lastDrawTime;

    lastDrawTime = drawTime;

    double d = zAct-zTarg;

    zAct += zSpeed * e * ((d > 0) ? -1 : 1);

    if (abs(zAct-zTarg) > abs(d)) zAct = zTarg;

    backColor.z = zAct;
    UI::drawBackground(member, target, qImage);
}

void Button::mouseEnter()
{
    zTarg = z + .25;

    UI::mouseEnter();
}

void Button::mouseLeave()
{
    zTarg = z;
    UI::mouseLeave();
}


bool Button::mouseMove(int x, int y)
{
    if (UI::mouseMove(x,y)) return true;

    return true;
}

bool Button::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    if (UI::mouseButtonPress(x,y, button)) return true;

    return true;
}

bool Button::mouseButtonRelease(int x, int y, Qt::MouseButton button)
{
    if (UI::mouseButtonRelease(x,y, button)) return true;

    return true;
}


Button_Image::Button_Image(UI *parent) : Button(parent)
{
}

void Button_Image::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);

    target->DrawImage(xReal, yReal, width.get(), height.get(),
            PixOp_SRC_ALPHA, ZOp_SRC_ADD, src, 0,0, src->Width, src->Height);

}

bool Button_Image::selfLayout()
{
    UI *child = *children.begin();

    if (width.resp = Resp_Self)
    {
        width.set(src->Width);
        width.dirty = false;
    }

    if (height.resp = Resp_Self)
    {
        height.set(src->Height);
        height.dirty = false;
    }

    UI::selfLayout();
}


bool Button_Image::doLayout()
{
    bool rc = UI::doLayout();
    if (rc) return true;

    return false;
}

Button_Image::~Button_Image()
{
}
