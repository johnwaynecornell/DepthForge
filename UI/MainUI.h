//
// Created by jwc on 2/16/19.
//

#ifndef DEPTHFORGE_MAINUI_H
#define DEPTHFORGE_MAINUI_H

#include <chrono>

#include "Lense.h"
#include "DepthForgeWin.h"
#include "UI.h"
#include "Slider.h"
#include "TabCtl.h"

#include "../FpsMonitor.h"

class Forge;
class LenseButton;
class DepthForgeWin;


class MainUI : public Fixed
{
public:
    std::chrono::high_resolution_clock clk;
    std::chrono::time_point<std::chrono::high_resolution_clock> timeUp;

    Lense *lense;

    TabFolder *tabs;
    TabCtl *basicToolsCtl;
    Fixed *basicTools;

    TabCtl *pathToolsCtl;
    Fixed *pathTools;


    Frame *toolFrame;
    Frame *bottomFrame;
    Fixed *tools;
    Fixed *bottom;

    Slider *slideA;
    Slider *slideB;

    Forge *forge;

    DepthForgeWin *owner;

    bool firstDraw = true;

    MainUI(DepthForgeWin *win);

    virtual void draw(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();
    virtual double getTimeInSeconds();

private:
    virtual void giveMouse(UI *element);
    virtual void freeMouse(UI *element);

public:
    void sizeEntered(UI *sender, void *arg);
    void sizeLeave(UI *sender, void *arg);
    void sizeChanged(UI *sender, double v, void *arg);
    void intensityChanged(UI *sender, double v, void *arg);

    void setLense(Lense *lense);

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
