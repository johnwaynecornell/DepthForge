//
// Created by jwc on 2/7/19.
//

#ifndef DEPTHFORGE_UI_H
#define DEPTHFORGE_UI_H

#include "../Image/Image.h"
#include <list>

#include <QImage>
#include <QApplication>
#include <QPainter>

#include <math.h>

class UI;

typedef bool (*LayoutProc)(UI *elem);

enum Resp
{
    Resp_Parent,
    Resp_Child,
    Resp_Self,
    Resp_None
};


template <class T> class UIProp
{
public:
    bool dirty = true;
    T val = 0;
    Resp resp = Resp_Self;

    void set(T val)
    {
        dirty = true;
        this->val = val;
    }

    T get()
    {
        return val;
    }

    void setResp(Resp resp)
    {
        this->resp = resp;
    }

};

class UI;

template <class f> struct UICallback
{
    void *_This;
    UI *element;
    f function;
    void *argument;
};

class UI {
public:
    UI *parent;
    std::list<UI *> children;

    UIProp<int> xPos;
    UIProp<int> yPos;

    UIProp<int> width;
    UIProp<int> height;

    UIProp<int> childOriginX;
    UIProp<int> childOriginY;

    Resp backgroundResp;

    void *tag;
    int xReal;
    int yReal;

    //LayoutProc selfLayoutProc;
    LayoutProc layoutProc = nullptr;

    ImgOp backOp;
    Image *backImage;
    ARGBz backColor;

    UI *mouseIn;

private:
    UICallback<void (*)(void*, UI *, void *)> mouseEnterProc;
    UICallback<void (*)(void*, UI *, void *)> mouseLeaveProc;

public:

    UI(UI *parent);
    virtual ~UI();

    UI * rootElement();


    void doDraw(Image *target, QImage *qImage);
    virtual void drawBackground(UI *member, Image *target, QImage *qImage);
    virtual void draw(Image *target, QImage *qImage);
    virtual void drawChildern(Image *target, QImage *qImage);
    virtual void drawOverlay(Image *target, QImage *qImage);

    void finalLayout();
    void updateReals();

    virtual bool selfLayout();
    virtual bool doLayout();

    void setMouseEnterProc(void (*proc)(void *_This, UI *elem, void *arg), void *elem, void *arg);
    void setMouseLeaveProc(void (*proc)(void *_This, UI *elem, void *arg), void *elem, void *arg);

    virtual bool contains(int x, int y);

    virtual void mouseEnter();
    virtual void mouseLeave();

    virtual bool mouseCoordNotify(int x, int y);

    virtual bool mouseMove(int x, int y);
    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);

    virtual void grabMouse();
    virtual void releaseMouse();

private:
    virtual void giveMouse(UI *element);
    virtual void freeMouse(UI *element);
public:
    virtual UI *childAt(int &x, int &y);
    virtual double getTimeInSeconds();
};

class Frame : public UI
{
public:

    Frame(UI *parent);
    virtual ~Frame();

    virtual void draw(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();

};

class Fixed : public UI
{
public:

    Fixed(UI*parent);
    virtual ~Fixed();

    virtual bool selfLayout();
    virtual bool doLayout();
};

class Button : public UI
{
    bool toggled;
public:
    float z;
    float zAct;
    float zTarg;
    float zSpeed;

    double drawTime;
    double lastDrawTime;

    UICallback<void (*)(void *_This, Button*element, bool pressed, void *arg)> onPress = {};

    Button(UI *parent);
    virtual ~Button();

    virtual bool isToggled();
    virtual void setToggled(bool state);

    virtual void toggle();

    virtual void drawBackground(UI *member, Image *target, QImage *qImage);

    virtual void mouseEnter();
    virtual void mouseLeave();

    virtual bool mouseMove(int x, int y);
    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);
};

class Button_Image : public Button
{
public:

    Image *src_noToggle;
    Image *src_Toggle;

    UICallback<void (*)(void *_This, Button_Image *E, void *arg)> onUpdateSrc= {nullptr,nullptr,nullptr};
    Button_Image(UI *parent);
    virtual ~Button_Image();

    void setSource(Image *src, bool forToggle);
    Image *getSource();

    virtual void draw(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();
};

#define get_member_pointer(Type, Member, Recipient) \
    {\
      union \
        {   Type; \
            void *b;    \
        } c; \
                \
        c.a = Member; \
        *((void **)&Recipient) = c.b;   \
    }

#endif //DEPTHFORGE_UI_H

extern void save_jps(QString fileName, Image *ImageLeft, Image *ImageRight);
extern void save_ana(QString fileName, Image *ImageLeft, Image *ImageRight);
extern void save_sample(QString fileName, Image *ImageLeft, Image *ImageRight);