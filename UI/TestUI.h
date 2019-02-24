//
// Created by jwc on 2/20/19.
//

#ifndef DEPTHFORGE_TESTUI_H
#define DEPTHFORGE_TESTUI_H


#include <DepthForgeWin.h>
#include "UI.h"

class TestUI : public UI {

public:
    std::chrono::high_resolution_clock clk;
    std::chrono::time_point<std::chrono::high_resolution_clock> timeUp;

    FpsMonitor fps;

    int mouseX;
    int mouseY;

    TestUI(DepthForgeWin *win);

    virtual void draw(Image *target, QImage *qImage);
    virtual bool mouseMove(int x, int y);

    virtual double getTimeInSeconds();
};


#endif //DEPTHFORGE_TESTUI_H
