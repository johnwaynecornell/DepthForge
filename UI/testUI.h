//
// Created by jwc on 2/20/19.
//

#ifndef DEPTHFORGE_TESTUI_H
#define DEPTHFORGE_TESTUI_H


#include <DepthForgeWin.h>
#include "UI.h"

class testUI : public UI {

public:
    int mouseX;
    int mouseY;

    testUI(DepthForgeWin *win);

    virtual void draw(Image *target, QImage *qImage);
    virtual bool mouseMove(int x, int y);
};


#endif //DEPTHFORGE_TESTUI_H
