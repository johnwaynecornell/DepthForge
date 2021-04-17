//
// Created by jwc on 4/2/19.
//

#ifndef DEPTHFORGE_MODE_H
#define DEPTHFORGE_MODE_H

#include <QtGui/QImage>
#include <Image/Image.h>
#include <UI/UI.h>
#include "UI/TabCtl.h"

class MainUI;
class Forge;

class DepthForgeTabCtl;

class Mode {
public:
    DepthForgeTabCtl *tabCtl;

    MainUI *mainUI;
    Image *ancillaryImage;
    Frame *ancillaryFrame;
    Button_Image * ancillaryView;

    Mode(MainUI *mainUI);

    virtual void resizeAncillary(int width);

    virtual void updateSrc(Forge *forge);
    virtual void drawForge(Forge *forge, Image *target, QImage *qImage) = 0;
    virtual bool mouseMoveForge(Forge *forge, int x, int y) = 0;
    virtual bool mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button) = 0;
    virtual bool mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button) = 0;

    virtual void selfLayout() = 0;
    virtual void doLayout() = 0;

};


#endif //DEPTHFORGE_MODE_H
