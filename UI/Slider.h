//
// Created by jwc on 2/19/19.
//

#ifndef DEPTHFORGE_SLIDER_H
#define DEPTHFORGE_SLIDER_H


#include "UI.h"

class Slider : public UI {
public:
    double v;
    bool _signed;

    class Element;
    Element *element;

    const char *label;
    Image *src;

    UICallback<void (*)(void *, UI *sender, double, void *)> vCallback;

    Slider(UI *parent, const char *label, bool _signed);
    virtual ~Slider();

    virtual void setV(double val);
    void setVCallvack(void (*proc)(void *, UI *sender, double, void *), void *elem, void *arg);

    void makeSrc();

    virtual void drawBackground(UI *member, Image *target, QImage *qImage);
    virtual void draw(Image *target, QImage *qImage);

    virtual void updateElementPosition();

    virtual bool selfLayout();
    virtual bool doLayout();

    virtual void mouseEnter();
    virtual void mouseLeave();

    virtual bool mouseMove(int x, int y);
    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);

    bool moveElement(int xd, int yd);

    class Element : public UI {
    public:

        Image *src;

        int mouseX;
        int mouseY;

        bool mouseDown;

        Element(Slider *slider, int width, int height);
        virtual ~Element();

        virtual void drawBackground(UI *member, Image *target, QImage *qImage);
        virtual void draw(Image *target, QImage *qImage);

        virtual bool selfLayout();
        virtual bool doLayout();

        virtual void mouseEnter();
        virtual void mouseLeave();

        virtual bool mouseMove(int x, int y);
        virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
        virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);

    };


};


#endif //DEPTHFORGE_SLIDER_H
