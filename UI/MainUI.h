//
// Created by jwc on 2/16/19.
//

#ifndef DEPTHFORGE_MAINUI_H
#define DEPTHFORGE_MAINUI_H


#include <Lense.h>
#include <DepthForgeWin.h>
#include "UI.h"

class Forge;
class LenseButton;
class DepthForgeWin;


class MainUI : public Fixed
{
public:
    Lense *lense;

    Frame *toolFrame;
    Frame *bottomFrame;
    Fixed *tools;
    Fixed *bottom;

    Forge *forge;

    DepthForgeWin *owner;

    MainUI(DepthForgeWin *win);

    virtual void draw(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();

    LenseButton * addLenseButton(int x, int y, LenseProc lensProc);
};

class LenseButton : public Button_Image
{
public:
    Lense *lense;

    LenseButton(UI *parent, LenseProc proc);
    virtual ~LenseButton();

    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);

    static float Sphere(float x, float y);
    static float Circle(float x, float y);
    static float Pyramid(float x, float y);
    static float Square(float x, float y);

};

#endif //DEPTHFORGE_MAINUI_H
