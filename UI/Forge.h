//
// Created by jwc on 2/16/19.
//

#ifndef DEPTHFORGE_FORGE_H
#define DEPTHFORGE_FORGE_H


#include "UI.h"

class Forge : public UI
{
public:
    bool hasMouse;
    Qt::MouseButtons mouseDown;

    double mouseX;
    double mouseY;

    Image *src;

    int _x;
    int _y;

    int _w;
    int _h;


    Forge(UI *parent);
    virtual ~Forge();

    virtual void draw(Image *target, QImage *qImage);

    virtual void mouseEnter();
    virtual void mouseLeave();

    virtual bool mouseMove(int x, int y);
    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);

    void applyLense();

};


#endif //DEPTHFORGE_FORGE_H
