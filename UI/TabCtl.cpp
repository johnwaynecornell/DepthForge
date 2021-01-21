//
// Created by jwc on borderSize/7/19.
//

#include "TabCtl.h"
#include "MainUI.h"

TabCtl::TabCtl(UI *parent, QString Lable) : Frame(parent)
{
    tabSize.set(16<<1);
    borderSize.set(6);
    tabPosition.set(borderSize.get()<<1);
    tabLength.set(64);

    animation = nullptr;
    qAnimation = nullptr;

    myState = State_collapsed;

    this->Lable = Lable;
}

TabCtl::~TabCtl()
{
    
}

ARGB tabInner = {0xFF,0xFF,0xFF,0xFF};
ARGB tabOuter = {0xFF,0xFF,0x00,0xFF};

bool tabDraw(int Index, double y, ARGB &Pix, float &z, void *arg)
{
    y = abs(y);
    if (y>1)
    {
        z = 0;
        Pix = {0,0,0,0};
    } else {

        z = y * .125;

        unsigned char Q = (unsigned char) (y * 0xFF);

        Pix = tabInner.interpolate(tabOuter.interpolate({0x00, 0x00, 0x00, 0x00}, Q), Q);
    }
    return true;
}

void TabCtl::drawFrameSrc()
{
    int bs = borderSize.get();

    int w = bs*6;
    int h = w;

    if (frameSrc == nullptr || frameSrc->Width != w || frameSrc->Height != h)
    {
        if (frameSrc != nullptr) delete frameSrc;

        frameSrc = new Image(w,h);

        int x1,y1,x2,y2;

        x1 = y1 = bs;
        x2 = x1 + bs*4; y2 = y1 + bs*4;

        frameSrc->Line(x1,y1, x2, y1);
        frameSrc->LineTo(x2,y2);
        frameSrc->LineTo(x1,y2);
        frameSrc->LineTo(x1,y1);

        frameSrc->DrawPath(PixOp_SRC, ZOp_SRC, 1.0/bs, &tabDraw, nullptr);
    }
}

void TabCtl::draw(Image *target, QImage *qImage) {
    UI::draw(target, qImage);

    drawFrameSrc();

    int sz = borderSize.get() << 1;

    int x1 = xReal;
    int y1 = yReal;

    int x2 = xReal + width.get() - 1 - sz;
    int y2 = yReal + height.get() - 1 - sz;

    int ix = x1 + tabSize.get();

    int iyt = y1 + tabPosition.get();
    int iyb = iyt + tabLength.get();

    int xx;
    int yy;
    int w;
    int h;

    QPainter *p = new QPainter(qImage);

    //p->fontMetrics().height()

    QPen pen = p->pen();

    pen.setColor(QColor{0xFF,0xFF,0xFF});
    pen.setWidth(30);

    p->setPen(pen);

    QFont f = p->font();

    f.setPointSize(14);

    p->setFont(f);

    QRect r = p->fontMetrics().boundingRect(Lable);

    int _w = r.width();

    p->translate((x1+ix+r.height()) / 2, iyb);
    p->rotate(-90);

    p->drawText((tabLength.get()-sz-_w) / 2,0, Lable);


    p->end();
    delete p;

    if (myState != State_collapsed) {
        xx = ix + sz;
        yy = y1;

        w = (x2 - xx);
        h = sz;

        target->Tile(xx, yy, w, h, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                     frameSrc, 0, 0, sz, 0, sz, sz);

        target->Tile(xx, y2, w, h, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                     frameSrc, 0, 0, sz, 0, sz, sz);

        target->DrawImage(xx - sz, yy, sz, sz, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                          frameSrc, 0, 0, sz, sz);
        target->DrawImage(xx + w, yy, sz, sz, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                          frameSrc, sz << 1, 0, sz, sz);

        target->DrawImage(xx - sz, y2, sz, sz, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                          frameSrc, 0, sz << 1, sz, sz);
        target->DrawImage(xx + w, y2, sz, sz, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                          frameSrc, sz << 1, sz << 1, sz, sz);
    }

    //tab top+bottom
    xx = x1+sz;
    yy = iyt;

    w = (ix-xx);
    h = sz;

    target->Tile(xx, yy, w, h, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                 frameSrc, 0, 0, sz, 0, sz,sz);

    target->Tile(xx, iyb, w, h, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                 frameSrc, 0, 0, sz, 0, sz,sz);

    target->DrawImage(xx-sz, yy, sz,sz, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                      frameSrc, 0, 0, sz,sz);

    if (myState != State_collapsed)
        target->DrawImage(xx+w, yy, sz,sz, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                      frameSrc, sz<<1, sz<<1, sz,sz);

    target->DrawImage(xx-sz, iyb, sz,sz, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                      frameSrc, 0, sz<<1, sz,sz);
    if (myState != State_collapsed)
        target->DrawImage(xx+w, iyb, sz,sz, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                      frameSrc, sz<<1, 0, sz,sz);

    // tab left
    xx = x1;
    yy = iyt+sz;

    w = sz;
    h = (iyb)-yy+1;

    target->Tile(xx, yy, w, h, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                 frameSrc, 0, 0, 0, sz, sz,sz);


    if (myState != State_collapsed) {

        xx = x2;
        yy = y1 + sz;

        w = sz;
        h = (y2) - yy + 1;

        target->Tile(xx, yy, w, h, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                     frameSrc, 0, 0, 0, sz, sz, sz);

        xx = ix;
        yy = y1 + sz;

        w = sz;
        h = (iyt) - yy + 1;

        target->Tile(xx, yy, w, h, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                     frameSrc, 0, 0, 0, sz, sz, sz);


        xx = ix;
        yy = iyb + sz;

        w = sz;
        h = (y2) - yy + 1;

        target->Tile(xx, yy, w, h, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                     frameSrc, 0, 0, 0, sz, sz, sz);
    }
}

void TabCtl::drawChildern(Image *target, QImage *qImage)
{
    UI *child = children.front();

    if (myState != State_collapsed && myState != State_closed)
    {
        if (q != 1.0)
        {
            int oldxReal = child->xReal;
            int oldyReal = child->yReal;

            child->xReal = 0;
            child->yReal = 0;

            child->updateReals();

            int w = child->width.get();
            int h = child->height.get();

            if (animation == nullptr || animation->Width < w || animation->Height < h)
            {
                if (animation != nullptr)
                {
                    delete animation;
                    delete qAnimation;
                }

                animation = new Image(w,h);

                qAnimation = new QImage((uchar *) animation->imageMemory, w, h, QImage::Format_RGBA8888);
            }

            animation->FillRect(0,0,w,h,PixOp_SRC, {0,0,0,0}, ZOp_SRC, 0);
            UI::drawChildern(animation, qAnimation);

            target->DrawImage(xReal+childOriginX.get(), yReal+childOriginY.get(),
                              (int) (width.val - (borderSize.get()<<1) - childOriginX.get()),
                              height.get()-(borderSize.get()<<2),
                    PixOp_SRC_ALPHA, ZOp_SRC, animation, 0, 0, w, h);


            child->xReal = oldxReal;
            child->yReal = oldyReal;

            child->updateReals();
        } else UI::drawChildern(target,qImage);
    }
}

bool TabCtl::selfLayout()
{
    UI::selfLayout();

    childOriginX.set(tabSize.get()+(borderSize.get()<<1));
    childOriginY.set((borderSize.get()<<1));

    UI *child = *children.begin();

    State state = myState;

    if (myState == State_opening)
    {
        q = getTimeInSeconds()-animTime;
        if (q>=1)
        {
            q = 1;
            myState = State_open;

        }
    } else if (myState == State_closing)
    {
        q = 1.0 - (getTimeInSeconds()-animTime);
        if (q*child->width.get()<=0)
        {
            q = 0;
            myState = State_closed;


        }
    }

    if (width.resp == Resp_Child)
    {
        Q_ASSERT(child != nullptr && child->width.resp != Resp_Parent);
        int w = tabSize.get();

        if (myState != State_collapsed)
        {
            w += borderSize.get()*4;
        }

        if (myState != State_closed && myState != State_collapsed)
        {
            w += (int) (child->width.val * q);
        }

        width.set(w);
        width.dirty = false;
    }

    if (height.resp == Resp_Child)
    {
        Q_ASSERT(child != nullptr && child->height.resp != Resp_Parent);

        height.set(child->height.val + (borderSize.get()<<2));
        height.dirty = false;
    }

    if (state != myState) invokeStateChangeCallback(myState);

    return true;
}

bool TabCtl::doLayout() {

    UI *child = *children.begin();

    if (child != nullptr) {
        if (child->width.resp == Resp_Parent) {
            Q_ASSERT(width.resp != Resp_Child-tabSize.get());
            Q_ASSERT(false);
            child->width.set(width.val - (borderSize.get()<<2));
            width.dirty = false;
        }

        if (child->height.resp == Resp_Parent) {
            Q_ASSERT(height.resp != Resp_Child);

            child->height.set(height.val - (borderSize.get()<<2));
            height.dirty = false;
        }
    }

    UI::doLayout();

    return false;
}

bool TabCtl::contains(int x, int y)
{
    if (x<0||x>=width.get() || y<0 || y>height.get()) return false;

    int ix = tabSize.get();

    int iyt = tabPosition.get();
    int iyb = iyt + tabLength.get();

    return (x>ix)||(y>=iyt && y<iyb);
}

bool TabCtl::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    if (!UI::mouseButtonPress(x,y,button))
    {
        if (x<tabSize.get()) {
            return mouseButtonPress_Tab(x,y,button);
        }

        return false;
    }

    return true;
}

bool TabCtl::mouseButtonPress_Tab(int x, int y, Qt::MouseButton button)
{
    return ((TabFolder *)parent)->tabPress(this, x, y, button);
}

UI *TabCtl::childAt(int &x, int &y)
{
    if (myState == State_open) return UI::childAt(x,y);
    return nullptr;

}

void TabCtl::invokeStateChangeCallback(State state)
{
    if (stateChangeCallback.function != nullptr)
        stateChangeCallback.function(stateChangeCallback._This,
                (TabCtl *)stateChangeCallback.element,state,
                stateChangeCallback.argument);
}

void TabCtl::setStateChangeCallback(void *_This,
                                    void (*callback)(void *_This, TabCtl *ctl, State state, void *arg),
                                    void *arg)
{
    stateChangeCallback = { _This, this, callback, arg };
}


void TabCtl::open()
{
    myState = State_opening;
    animTime = getTimeInSeconds();
    invokeStateChangeCallback(myState);
}

void TabCtl::close()
{
    myState = State_closing;
    animTime = getTimeInSeconds();
    invokeStateChangeCallback(myState);
}

DepthForgeTabCtl::DepthForgeTabCtl(UI *parent, QString Lable) : TabCtl(parent, Lable)
{
}

DepthForgeTabCtl::~DepthForgeTabCtl()
{

}

void DepthForgeTabCtl::open()
{
    TabCtl::open();

    ((MainUI *)rootElement())->mode_Current = myMode;
}


TabFolder::TabFolder(UI *parent) : UI(parent)
{
}

TabFolder::~TabFolder()
{
}

void TabFolder::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);
}

bool TabFolder::selfLayout()
{
    UI::selfLayout();

    int hx=0;
    int hy=0;

    for (auto i = children.begin(); i != children.end(); i++)
    {
        int _x = (*i)->width.get();
        int _y = (*i)->height.get();

        if (_x>hx) hx = _x;
        if (_y>hy) hy = _y;

    }

    //UI *child = *children.begin();

    if (width.resp == Resp_Child)
    {
        //Q_ASSERT(child != nullptr && child->width.resp != Resp_Parent);
        width.set(hx);
        width.dirty = false;
    }

    if (height.resp == Resp_Child)
    {
        height.set(hy);
        height.dirty = false;
    }

    return true;
}

bool TabFolder::doLayout() {

    for (std::list<UI*>::iterator i = children.begin(); i != children.end(); i++)
    {
        UI *child = *i;

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
    }

    UI::doLayout();

    return false;
}

void stateChange(void *_This, TabCtl *ctl, TabCtl::State state, void *arg)
{
    TabFolder *This = (TabFolder *)_This;
    TabCtl *New = (TabCtl *) arg;

    if (state == TabCtl::State_closed)
    {
        ctl->myState = TabCtl::State_collapsed;
        ctl->setStateChangeCallback(nullptr, nullptr, nullptr);

        New->open();
    }
}

bool TabFolder::tabPress(TabCtl *ctl, int x, int y, Qt::MouseButton button)
{
    if (ctl->myState == TabCtl::State_open) ctl->close();
    else if (ctl->myState == TabCtl::State_closed) ctl->open();
    else if (ctl->myState == TabCtl::State_collapsed)
    {
        TabCtl *a = activeCtl();

        if (a == nullptr) ctl->open();
        else if (a->myState == TabCtl::State_closed)
        {
            ctl->open();
            a->myState = TabCtl::State_collapsed;
        } else if (a->myState == TabCtl::State_open)
        {
            a->setStateChangeCallback(this, stateChange, ctl);
            a->close();
        }
    }

    return true;
}

TabCtl *TabFolder::activeCtl()
{
    for (std::list<UI *>::iterator i = children.begin(); i != children.end(); i++)
    {
        if (((TabCtl *)*i)->myState != TabCtl::State_collapsed)
            return(TabCtl *)*i;
    }

    return nullptr;
}