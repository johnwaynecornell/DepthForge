//
// Created by jwc on 2/19/19.
//

#include "Slider.h"

Slider::Slider(UI *parent) : UI(parent)
{
    v = 0;
    element = new Element(this);

    element->xPos.setResp(Resp_Self);
    element->yPos.setResp(Resp_Self);

    element->width.setResp(Resp_Self);
    element->height.setResp(Resp_Self);

    element->xPos.set(16);
    element->yPos.set(0);
    element->width.set(16);
    element->height.set(16);
}

void Slider::drawBackground(UI *member, Image *target, QImage *qImage)
{
    UI::drawBackground(member, target, qImage);
}

void Slider::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);
}

bool Slider::selfLayout()
{
    bool rc = selfLayout();

    return rc;
}

bool Slider::doLayout()
{
    bool rc = doLayout();

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
}

Slider::~Slider()
{

}

Slider::Element::Element(Slider *slider) : UI(slider)
{

}

void Slider::Element::drawBackground(UI *member, Image *target, QImage *qImage)
{
    UI::drawBackground(member,target,qImage);
}

void Slider::Element::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);
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
    bool rc = mouseMove(x, y);

    return rc;
}

bool Slider::Element::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    bool rc = mouseButtonPress(x,y,button);
    return rc;
}

bool Slider::Element::mouseButtonRelease(int x, int y, Qt::MouseButton button)
{
    bool rc = UI::mouseButtonRelease(x,y,button);
    return rc;
}

Slider::Element::~Element()
{

}
