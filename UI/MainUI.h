//
// Created by jwc on 2/16/19.
//

#ifndef DEPTHFORGE_MAINUI_H
#define DEPTHFORGE_MAINUI_H

#include <chrono>

#include "Lens.h"
#include "DepthForgeWin.h"
#include "UI.h"
#include "Slider.h"
#include "TabCtl.h"
#include "Forge.h"
#include "ForgeContainer.h"

#include "../FpsMonitor.h"

#include "Mode_DepthEdit.h"
#include "Mode_Path.h"

class Forge;
class ForgeContainer;
class DepthForgeWin;

class MainUI : public Fixed
{
public:
    std::chrono::high_resolution_clock clk;
    std::chrono::time_point<std::chrono::high_resolution_clock> timeUp;

    Mode *mode_Current;
    Mode_DepthEdit *mode_DepthEdit;
    Mode_Path *mode_Path;

    TabFolder *tabs;

    Image *ArrowCursor;

    ForgeContainer *forgeContainer;

    DepthForgeWin *owner;

    bool firstDraw = true;

    int mouseX;
    int mouseY;

    MainUI(DepthForgeWin *win);

    virtual void draw(Image *target, QImage *qImage);
    virtual void drawOverlay(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();
    virtual double getTimeInSeconds();

    virtual bool mouseMove(int x, int y);

private:
    virtual void giveMouse(UI *element);
    virtual void freeMouse(UI *element);

};


#endif //DEPTHFORGE_MAINUI_H
