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

    bool previewLense;

    Image *bkgImage;

    Forge(UI *parent);
    virtual ~Forge();

    Image *bkgTile;

    void drawInitial();

    virtual void drawBackground(UI *member, Image *target, QImage *qImage);
    virtual void draw(Image *target, QImage *qImage);

    virtual void mouseEnter();
    virtual void mouseLeave();

    virtual bool mouseMove(int x, int y);
    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);

    void applyLense();

    void import(UI *sender, void *arg);
    void export_anaglyph(UI *sender, void *arg);
    void export_jps(UI *sender, void *arg);

};


#endif //DEPTHFORGE_FORGE_H
