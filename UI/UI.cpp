//
// Created by jwc on 2/7/19.
//

#include <cstdlib>
#include "UI.h"

UI::UI(UI *parent)
{
    this->parent = parent;
    this->tag = nullptr;
    this->layoutProc = nullptr;

    childOriginX.val = 0;
    childOriginY.val = 0;

    backgroundResp = Resp_None;

    backOp.zOp = ZOp_SRC_ADD;
    backOp.pixOp = PixOp_SRC_ALPHA;

    backColor = ARGBz(0,0,0,0,0.0f);
    backImage = nullptr;

    mouseIn = nullptr;
    
    mouseEnterProc = mouseLeaveProc = {0,0,0} ;

    if (parent != nullptr) parent->children.push_back(this);
}

UI::~UI()
{
    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++)
    {
        delete (*i);
    }
}

UI * UI::rootElement()
{
    UI *i = this;
    while (i->parent != nullptr) i = i->parent;

    return i;
}

void UI::finalLayout()
{
    selfLayout();
    doLayout();

    //Q_ASSERT(doLayout());

    std::list<UI *> l;

    l.insert(l.begin(), this);

    while (l.begin() != l.end()) {

        UI *cur = l.front();
        l.pop_front();

        int _x = cur->xReal + cur->childOriginX.get();
        int _y = cur->yReal + cur->childOriginY.get();

        for (std::list<UI *>::iterator i = cur->children.begin();
                i != cur->children.end(); i++)
        {
            UI *e = *i;
            e->xReal = _x+e->xPos.get();
            e->yReal = _y+e->yPos.get();

            l.push_back(e);
        }
    }
}


bool UI::selfLayout()
{
    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++)
    {
        (*i)->selfLayout();
    }

    return false;
}

bool UI::doLayout()
{
    if (layoutProc != nullptr) return layoutProc(this);

    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++)
    {
        (*i)->doLayout();
    }

    return false;
}

void UI::mouseEnter()
{
    if (mouseEnterProc.function != nullptr) 
        mouseEnterProc.function(mouseEnterProc.element, mouseEnterProc.argument);
}
void UI::mouseLeave()
{
    if (mouseIn != nullptr)
    {
        mouseIn->mouseLeave();
        mouseIn = nullptr;
    }

    if (mouseLeaveProc.function != nullptr)
        mouseLeaveProc.function(mouseLeaveProc.element, mouseLeaveProc.argument);
}

void UI::setMouseEnterProc(void (*proc)(UI *elem, void *arg), UI *elem, void *arg)
{
    mouseEnterProc = {elem, proc, arg};
}
void UI::setMouseLeaveProc(void (*proc)(UI *elem, void *arg), UI *elem, void *arg)
{
    mouseLeaveProc = {elem, proc, arg};
}

bool UI::mouseMove(int x, int y)
{
    UI *ch = childAt(x,y);

    if (ch != mouseIn)
    {
        if (mouseIn != nullptr) mouseIn->mouseLeave();

        mouseIn = ch;
        if (mouseIn != nullptr) mouseIn->mouseEnter();
    }

    if (ch != nullptr)
    {
        return ch->mouseMove(x,y);
    }

    return false;
}

bool UI::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    UI *ch = childAt(x,y);
    if (ch != mouseIn)
    {
        if (mouseIn != nullptr) mouseIn->mouseLeave();

        mouseIn = ch;
        if (mouseIn != nullptr) mouseIn->mouseEnter();
    }

    if (ch != nullptr)
    {
        return ch->mouseButtonPress(x,y, button);
    }

    return false;

}

bool UI::mouseButtonRelease(int x, int y, Qt::MouseButton button)
{
    UI *ch = childAt(x,y);
    if (ch != mouseIn)
    {
        if (mouseIn != nullptr) mouseIn->mouseLeave();

        mouseIn = ch;
        if (mouseIn != nullptr) mouseIn->mouseEnter();
    }

    if (ch != nullptr)
    {
        return ch->mouseButtonRelease(x,y, button);
    }

    return false;
}

void UI::grabMouse()
{
    giveMouse(this);
}

void UI::releaseMouse()
{
    freeMouse(this);
}

void UI::giveMouse(UI *element)
{
    UI *p = parent;

    while (p->parent != nullptr) p = p->parent;

    p->giveMouse(element);
}

void UI::freeMouse(UI *element)
{
    UI *p = parent;

    while (p->parent != nullptr) p = p->parent;

    p->freeMouse(element);
}


UI *UI::childAt(int &x, int &y)
{
    x += childOriginX.get();
    y += childOriginY.get();

    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++)
    {
        UI *el = *i;
        int _x = x - el->xPos.get();
        int _y = y - el->yPos.get();

        if (_x>=0 && _x < el->width.get() && _y >=0 && _y<el->height.get())
        {
            x = _x;
            y = _y;

            return el;
        }

    }

    return nullptr;

}

void UI::drawBackground(UI *member, Image *target, QImage *qImage)
{
    if (backgroundResp == Resp_Child) children.front()->drawBackground(member, target, qImage);
    if (parent != nullptr &&
        parent->backgroundResp == Resp_Child || backgroundResp != Resp_None)
    {
        if (backImage != nullptr)
            target->DrawImage(member->xReal, member->yReal,
                          member->xReal + member->width.get(), member->yReal + member->height.get(),
                          PixOp_SRC_ALPHA, ZOp_SRC_ADD, backImage,
                          0, 0, backImage->Width, backImage->Height);

        target->FillRect(member->xReal, member->yReal,
                member->xReal + member->width.get(), member->yReal + member->height.get(),
                backOp.pixOp, backColor, backOp.zOp, backColor.z);
    }
}

void UI::draw(Image *target, QImage *qImage)
{
    drawBackground(this, target, qImage);

    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++)
    {
        (*i)->draw(target, qImage);
    }
}

Frame::Frame(UI *parent) : UI(parent)
{
    childOriginX.set(3);
    childOriginY.set(3);
}

void Frame::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);

    int x1 = xReal;
    int y1 = yReal;

    int x2 = x1 + width.val-1;
    int y2 = y1 + height.val-1;

    ARGB C1, C2;
    float z1,z2;

    C1 = {0xFF,0x80,0x00,0x80};
    C2 = C1;

    z1 = -.05;z2 = z1;

    target->Line(x1, y1, x2-1, y1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x2, y1, x2, y2-1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x2, y2, x1+1, y2, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x1, y2, x1, y1+1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);

    C1 = {0xFF,0xFF,0xFF,0xFF};
    C2 = C1;

    x1++;y1++;x2--;y2--;
    z1=-.1; z2 = z1;

    target->Line(x1, y1, x2-1, y1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x2, y1, x2, y2-1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x2, y2, x1+1, y2, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x1, y2, x1, y1+1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);

    C1 = {0xFF,0x80,0x00,0x80};
    C2 = C1;

    x1++;y1++;x2--;y2--;
    z1=-.05; z2 = z1;

    target->Line(x1, y1, x2-1, y1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x2, y1, x2, y2-1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x2, y2, x1+1, y2, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
    target->Line(x1, y2, x1, y1+1, PixOp_SRC, C1, C2, ZOp_SRC_ADD, z1, z2);
}

bool Frame::selfLayout()
{
    UI::selfLayout();

    UI *child = *children.begin();

    if (width.resp == Resp_Child)
    {
        Q_ASSERT(child != nullptr && child->width.resp != Resp_Parent);
        width.set(child->width.val + 6);
        width.dirty = false;
    }

    if (height.resp == Resp_Child)
    {
        Q_ASSERT(child != nullptr && child->height.resp != Resp_Parent);

        height.set(child->height.val + 6);
        height.dirty = false;
    }

    return true;
}

bool Frame::doLayout() {

    UI *child = *children.begin();

    if (child != nullptr) {
        if (child->width.resp == Resp_Parent) {
            Q_ASSERT(width.resp != Resp_Child);
            child->width.set(width.val - 6);
            width.dirty = false;
        }

        if (child->height.resp == Resp_Parent) {
            Q_ASSERT(height.resp != Resp_Child);

            child->height.set(height.val - 6);
            height.dirty = false;
        }
    }

    UI::doLayout();

    return false;
}

Frame::~Frame()
{
}

Fixed::Fixed(UI *parent) : UI(parent)
{

}

Fixed::~Fixed()
{

}
/*
void Fixed::draw(Image *target, QImage *qImage)
{
}*/

bool Fixed::doLayout()
{
    bool rc = UI::doLayout();
    if (rc) return true;

    return false;
}

