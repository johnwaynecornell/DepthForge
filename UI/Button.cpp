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

    toggled = false;
}

Button::~Button()
{

}

bool Button::isToggled()
{
    return toggled;
}
void Button::setToggled(bool state)
{
    toggled = state;
}

void Button::toggle()
{
    setToggled(!isToggled());
}


void Button::drawBackground(UI *member, Image *target, QImage *qImage)
{
    drawTime = getTimeInSeconds();

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

    grabMouse();

    if (onPress.function != nullptr) onPress.function(onPress._This, this, true, onPress.argument);

    return true;
}

bool Button::mouseButtonRelease(int x, int y, Qt::MouseButton button)
{
    if (UI::mouseButtonRelease(x,y, button)) return true;

    releaseMouse();

    if (onPress.function != nullptr) onPress.function(onPress._This, this, false, onPress.argument);

    return true;
}


Button_Image::Button_Image(UI *parent) : Button(parent)
{
    src_noToggle = src_Toggle = nullptr;
}

Button_Image::~Button_Image()
{
    if (src_noToggle != nullptr) delete src_noToggle;
    if (src_Toggle != nullptr) delete src_Toggle;
}

void Button_Image::setSource(Image *src, bool forToggle)
{
    if (forToggle) src_Toggle = src; else src_noToggle = src;
}

Image *Button_Image::getSource()
{
    if (isToggled() && src_Toggle != nullptr) return src_Toggle;

    return src_noToggle;
}


void Button_Image::draw(Image *target, QImage *qImage)
{
    if (onUpdateSrc.function != nullptr) onUpdateSrc.function(onUpdateSrc._This, this, onUpdateSrc.argument);

    UI::draw(target, qImage);

    target->DrawImage(xReal, yReal, width.get(), height.get(),
            PixOp_SRC_ALPHA, ZOp_SRC_ADD, getSource(),
            0,0, getSource()->Width, getSource()->Height);

}

bool Button_Image::selfLayout()
{
    UI *child = *children.begin();

    if (width.resp = Resp_Self)
    {
        width.set(getSource()->Width);
        width.dirty = false;
    }

    if (height.resp = Resp_Self)
    {
        height.set(getSource()->Height);
        height.dirty = false;
    }

    UI::selfLayout();

    return true;
}


bool Button_Image::doLayout()
{
    bool rc = UI::doLayout();
    if (rc) return true;

    return false;
}
