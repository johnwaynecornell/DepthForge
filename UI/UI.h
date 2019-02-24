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
    bool dirty;
    T val;
    Resp resp;

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

template <class f> struct UICallback
{
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
    LayoutProc layoutProc;

    ImgOp backOp;
    Image *backImage;
    ARGBz backColor;

    UI *mouseIn;

    UI(UI *parent);

    UI * rootElement();

    virtual void drawBackground(UI *member, Image *target, QImage *qImage);
    virtual void draw(Image *target, QImage *qImage);

    void finalLayout();

    virtual bool selfLayout();
    virtual bool doLayout();

private:
    UICallback<void (*)(UI*, void *)> mouseEnterProc;
    UICallback<void (*)(UI*, void *)> mouseLeaveProc;

public:
    void setMouseEnterProc(void (*proc)(UI *elem, void *arg), UI *elem, void *arg);
    void setMouseLeaveProc(void (*proc)(UI *elem, void *arg), UI *elem, void *arg);

    virtual void mouseEnter();
    virtual void mouseLeave();

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

    virtual ~UI();
};

class Frame : public UI
{
public:

    Frame(UI *parent);

    virtual void draw(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();

    virtual ~Frame();
};

class Fixed : public UI
{
public:

    Fixed(UI*parent);

    //virtual void draw(Image *target, QImage *qImage);

    virtual bool doLayout();

    virtual ~Fixed();

};

class Button : public UI
{
public:
    Button(UI *parent);
    virtual ~Button();

    float z;
    float zAct;
    float zTarg;
    float zSpeed;

    double drawTime;
    double lastDrawTime;

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
    Image *src;


    Button_Image(UI *parent);
    virtual ~Button_Image();

    virtual void draw(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();
};


#endif //DEPTHFORGE_UI_H
