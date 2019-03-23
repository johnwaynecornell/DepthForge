//
// Created by jwc on 3/7/19.
//

#ifndef DEPTHFORGE_TABCTL_H
#define DEPTHFORGE_TABCTL_H


#include "UI.h"

class TabCtl : public Frame {

public:
    enum State
    {
        State_open,State_closed,State_collapsed, State_opening, State_closing
    };

    double animTime;
    double q;

    State myState = State_collapsed;

    UIProp<int> tabPosition;
    UIProp<int> tabSize;
    UIProp<int> tabLength;
    UIProp<int> borderSize;

    Image *frameSrc = nullptr;

    Image *animation;
    QImage *qAnimation;

    UICallback<void (*)(void *_This, TabCtl *ctl, State state, void *arg)>
        stateChangeCallback = {0,0,0};

    TabCtl(UI *parent);
    virtual ~TabCtl();

    void drawFrameSrc();

    virtual void draw(Image *target, QImage *qImage);
    virtual void drawChildern(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();

    virtual bool contains(int x, int y);
    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonPress_Tab(int x, int y, Qt::MouseButton button);

    virtual UI *childAt(int &x, int &y);

    void invokeStateChangeCallback(State state);
    virtual void setStateChangeCallback(
            void *_This,
            void (*callback)(void *_This, TabCtl *ctl, State state, void *arg),
            void *arg);

    virtual void open();
    virtual void close();
};

class TabFolder : public UI
{
public:
    TabFolder(UI *parent);
    virtual ~TabFolder();

    virtual void draw(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();

    virtual bool tabPress(TabCtl *ctl, int x, int y, Qt::MouseButton button);

    TabCtl *activeCtl();
};


#endif //DEPTHFORGE_TABCTL_H
