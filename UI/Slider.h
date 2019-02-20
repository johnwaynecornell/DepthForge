//
// Created by jwc on 2/19/19.
//

#ifndef DEPTHFORGE_SLIDER_H
#define DEPTHFORGE_SLIDER_H


#include "UI.h"

class Slider : public UI {
public:
    double v;

    class Element;
    Element *element;

    Slider(UI *parent);

    virtual void drawBackground(UI *member, Image *target, QImage *qImage);
    virtual void draw(Image *target, QImage *qImage);

    void finalLayout();

    virtual bool selfLayout();
    virtual bool doLayout();

    virtual void mouseEnter();
    virtual void mouseLeave();

    virtual bool mouseMove(int x, int y);
    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);

    virtual ~Slider();

    class Element : public UI {
    public:

        Element(Slider *slider);

        virtual void drawBackground(UI *member, Image *target, QImage *qImage);
        virtual void draw(Image *target, QImage *qImage);

        void finalLayout();

        virtual bool selfLayout();
        virtual bool doLayout();

        virtual void mouseEnter();
        virtual void mouseLeave();

        virtual bool mouseMove(int x, int y);
        virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
        virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);

        virtual ~Element();

    };


};


#endif //DEPTHFORGE_SLIDER_H
