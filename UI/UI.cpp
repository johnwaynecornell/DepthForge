//
// Created by jwc on 2/7/19.
//

#include <cstdlib>
#include "UI.h"
#include <QBuffer>
#include <QFile>

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
    
    mouseEnterProc = mouseLeaveProc = {0,0,0,0} ;

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

void UI::drawBackground(UI *member, Image *target, QImage *qImage)
{
    if (backgroundResp == Resp_Child) children.front()->drawBackground(member, target, qImage);
    if (parent != nullptr &&
            (parent->backgroundResp == Resp_Child || backgroundResp != Resp_None))
    {
        if (backImage != nullptr)
            target->DrawImage(member->xReal, member->yReal,
                              member->xReal + member->width.get(), member->yReal + member->height.get(),
                              PixOp_SRC_ALPHA, ZOp_SRC_ADD, backImage,
                              0, 0, backImage->Width, backImage->Height);

        target->FillRect(member->xReal, member->yReal,
                         member->width.get(), member->height.get(),
                         backOp.pixOp, backColor, backOp.zOp, backColor.z);
    }
}

void UI::doDraw(Image *target, QImage *qImage)
{
    draw(target, qImage);
    drawChildern(target, qImage);
    drawOverlay(target, qImage);
}

void UI::draw(Image *target, QImage *qImage)
{
    drawBackground(this, target, qImage);
}

void UI::drawChildern(Image *target, QImage *qImage)
{
    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++)
    {
        (*i)->doDraw(target, qImage);
    }
}

void UI::drawOverlay(Image *target, QImage *qImage)
{

}

void UI::finalLayout()
{
    selfLayout();
    doLayout();

    updateReals();
    //Q_ASSERT(doLayout());
}

void UI::updateReals()
{
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

void UI::setMouseEnterProc(void (*proc)(void *_This, UI * elem, void *arg),
        void *_This, void *arg)
{
    mouseEnterProc = {_This, this, proc, arg};
}
void UI::setMouseLeaveProc(void (*proc)(void *_This, UI *elem, void *arg),
    void *_This, void *arg)
{
    mouseLeaveProc = {_This, this, proc, arg};
}

bool UI::contains(int x, int y)
{
    return (x>=0 && x<width.get()) && (y>=0 && y<height.get());
}

void UI::mouseEnter()
{
    if (mouseEnterProc.function != nullptr) 
        mouseEnterProc.function(mouseEnterProc._This,
                mouseEnterProc.element, mouseEnterProc.argument);
}
void UI::mouseLeave()
{
    if (mouseIn != nullptr)
    {
        mouseIn->mouseLeave();
        mouseIn = nullptr;
    }

    if (mouseLeaveProc.function != nullptr)
        mouseLeaveProc.function(mouseEnterProc._This,
                                mouseLeaveProc.element, mouseLeaveProc.argument);
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
    x -= childOriginX.get();
    y -= childOriginY.get();

    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++)
    {
        UI *el = *i;
        int _x = x - el->xPos.get();
        int _y = y - el->yPos.get();

        if (el->contains(_x,_y))
        {
            x = _x;
            y = _y;

            return el;
        }

    }

    return nullptr;

}

double UI::getTimeInSeconds()
{
    UI *p = this->parent;
    while (p->parent != nullptr) p = p->parent;

    if (p == nullptr)
    {
        fprintf(stderr, "ERROR root UI must override getTimeInSeconds");
        QApplication::exit(-1);
    }

    return p->getTimeInSeconds();
}

Frame::Frame(UI *parent) : UI(parent)
{
    childOriginX.set(3);
    childOriginY.set(3);
}

Frame::~Frame()
{
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

Fixed::Fixed(UI *parent) : UI(parent)
{

}

Fixed::~Fixed()
{

}

bool Fixed::selfLayout()
{
    UI::selfLayout();

    UI *child = *children.begin();

    if (width.resp == Resp_Child)
    {
        int w = 0;
        for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++) {
            UI *child = (*i);

            Q_ASSERT(child != nullptr && child->width.resp != Resp_Parent);
            int ww =child->xPos.get() + child->width.get();
            if (ww > w) w = ww;

        }

        width.set(w);
        width.dirty = false;
    }

    if (height.resp == Resp_Child)
    {
        Q_ASSERT(child != nullptr && child->height.resp != Resp_Parent);

        int h = 0;
        for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++) {
            UI *child = (*i);

            Q_ASSERT(child != nullptr && child->width.resp != Resp_Parent);
            int hh =child->yPos.get() + child->height.get();
            if (hh > h) h = hh;

        }

        height.set(h);
        height.dirty = false;
    }

    return true;
}

bool Fixed::doLayout() {

    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++) {
        UI *child = (*i);

        if (child != nullptr) {
            if (child->width.resp == Resp_Parent) {
                Q_ASSERT(width.resp != Resp_Child);
                child->width.set(width.get());
            }

            if (child->height.resp == Resp_Parent) {
                Q_ASSERT(height.resp != Resp_Child);
                child->height.set(height.get());
            }
        }
    }

    UI::doLayout();

    return false;
}






/* Media Types */
#define SD_MTYPE_STEREOSCOPIC_IMAGE 0x01

/* layout Options */
#define SD_LAYOUT_INTERLEAVED 0x01
#define SD_LAYOUT_SIDEBYSIDE 0x02
#define SD_LAYOUT_OVERUNDER 0x03
#define SD_LAYOUT_ANAGLYPH 0x04

/* Misc Flags Bits */
#define SD_HALF_HEIGHT 0x01
#define SD_HALF_WIDTH 0x02
#define SD_LEFT_FIELD_FIRST 0x04

struct StereoDescriptor
{
    unsigned char ID[4];

    unsigned char sizeHigh;
    unsigned char sizeLow;

    unsigned char dummy;
    unsigned char flags;
    unsigned char layout;
    unsigned char type;
};

struct SDApp3
{
    unsigned char FF;
    unsigned char APP3;
    unsigned char sizeHigh;
    unsigned char sizeLow;
    unsigned char ID[4];

    StereoDescriptor desc;
};


void save_jps(QString fileName, Image *ImageLeft, Image *ImageRight)
{
    Image *ImageOut;

    int w = ImageLeft->Width;
    int h = ImageLeft->Height;

    const bool SideBySide = true;

    QImage *tmp;

    if (SideBySide) {

        ImageOut = new Image(w << 1, h);

        GfxBlt(PixType_ARGB, ImageLeft->imageMemory, 0, 0, w, h, w,
               PixType_RGBA, ImageOut->imageMemory, w, 0, w, h, w << 1);
        GfxBlt(PixType_ARGB, ImageRight->imageMemory, 0, 0, w, h, w,
               PixType_RGBA, ImageOut->imageMemory, 0, 0, w, h, w << 1);

        tmp = new QImage((uchar *)
                                 ImageOut->imageMemory, w << 1, h, QImage::Format_RGBA8888);

    } else
    {

        ImageOut = new Image(w, h << 1);

        GfxBlt(PixType_ARGB, ImageLeft->imageMemory, 0, 0, w, h, w,
               PixType_RGBA, ImageOut->imageMemory, 0, h, w, h, w);
        GfxBlt(PixType_ARGB, ImageRight->imageMemory, 0, 0, w, h, w,
               PixType_RGBA, ImageOut->imageMemory, 0, 0, w, h, w);

        tmp = new QImage((uchar *)
                                 ImageOut->imageMemory, w, h << 1, QImage::Format_RGBA8888);

    }

    {
        QBuffer *b = new QBuffer();
        b->open(QBuffer::ReadWrite);

        tmp->save(b, "JPG");

        const unsigned char * m = (const unsigned char *) b->data().data();
        int l = b->data().length();

        //printf("jpeg length = %d\n", l);

        int p = 0;

        int x = -1;

        int size;

        while (p<l)
        {
            Q_ASSERT(m[p] == 0xFF);

            unsigned char code = m[p+1];

            if (code == 0xD8 || code == 0xD9 || code == 0xDA) size = 0;
            else size = (m[p+2]<<8)+m[p+3];

            printf("\tCode %02X len=%d\n", code, size);

            p+=size+2;

            if (code == 0xE0) { x = p; break; }

        }

        Q_ASSERT(x != -1);

        unsigned char head[] = {0xFF, 0xE3, 0x00,0x00};

        QFile *f = new QFile(fileName);
        f->open(QFile::WriteOnly);

        f->write((const char *) m, x);

        SDApp3 desc;

        desc.FF = 0xFF;
        desc.APP3 = 0xE3;

        desc.sizeHigh = (unsigned char) ((sizeof(desc)-2) >> 8);
        desc.sizeLow = (unsigned char) ((sizeof(desc)-2));

        desc.ID[0] = '_'; desc.ID[1] = 'J'; desc.ID[2] = 'P'; desc.ID[3] = 'S';

        desc.desc.ID[0] = 'J'; desc.desc.ID[1] = 'P'; desc.desc.ID[2] = 'S'; desc.desc.ID[3]='_';

        desc.desc.sizeHigh = (unsigned char) ((sizeof(desc.desc)-4) >> 8);
        desc.desc.sizeLow = (unsigned char) ((sizeof(desc.desc))-4);

        desc.desc.dummy = 0;
        desc.desc.type = SD_MTYPE_STEREOSCOPIC_IMAGE;

        if (SideBySide)
        {
            desc.desc.layout = SD_LAYOUT_SIDEBYSIDE;
            desc.desc.flags = SD_HALF_WIDTH;

        } else
        {
            desc.desc.layout = SD_LAYOUT_OVERUNDER;
            desc.desc.flags = SD_HALF_HEIGHT;
        }

        f->write((const char *) &desc,sizeof(desc));
        f->write((const char *)(m+x), l-x);

        f->close();
        delete  f;
        delete b;
    }

    cleanup:
    delete ImageOut;
    delete tmp;
}

void save_ana(QString fileName, Image *ImageLeft, Image *ImageRight)
{
    //save_sample(fileName, ImageLeft, ImageRight);
    //return;

    Image *ImageOut;

    int w = ImageLeft->Width;
    int h = ImageRight->Height;

    ImageOut = new Image(w, h);

    ImageOut->AnaglyphFrom(ImageLeft, ImageRight);


    QImage *tmp = new QImage(w,h, QImage::Format_RGBA8888);

    GfxBlt(PixType_ARGB, ImageOut->imageMemory, 0, 0, w, h, w,
           PixType_RGBA, tmp->bits(), 0, 0, w, h, w);

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        tmp->save(fileName);
    }

    cleanup:
    delete ImageOut;
    delete tmp;

}

void save_sample(QString fileName, Image *ImageLeft, Image *ImageRight)
{
    Image *ana;

    int w = ImageLeft->Width;
    int h = ImageRight->Height;

    ana = new Image(w, h);

    ana->AnaglyphFrom(ImageLeft, ImageRight);


    QImage *tmp = new QImage(800,1200, QImage::Format_RGBA8888);
    tmp->fill(QColor(0xFF,0xFF,0xFF,0xFF));

    GfxBlt(PixType_ARGB, ana->imageMemory, 0, 0, w, h, w,
           PixType_RGBA, tmp->bits(), 2, 2, 800-2, 600-2, 800);

    GfxBlt(PixType_ARGB, ImageLeft->imageMemory, 0, 0, w, h, w,
           PixType_RGBA, tmp->bits(), 2, 600+2, 400-4, 300-4, 800);

    GfxBlt(PixType_ARGB, ImageRight->imageMemory, 0, 0, w, h, w,
           PixType_RGBA, tmp->bits(), 400+2, 600+2, 400-4, 300-4, 800);

    GfxBlt(PixType_ARGB, ImageRight->imageMemory, 0, 0, w, h, w,
           PixType_RGBA, tmp->bits(), 2, 900+2, 400-4, 300-4, 800);

    GfxBlt(PixType_ARGB, ImageLeft->imageMemory, 0, 0, w, h, w,
           PixType_RGBA, tmp->bits(), 400+2, 900+2, 400-4, 300-4, 800);


    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        tmp->save(fileName);
    }

    cleanup:
    delete ana;
    delete tmp;

}