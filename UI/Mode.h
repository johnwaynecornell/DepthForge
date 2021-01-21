//
// Created by jwc on 4/2/19.
//

#ifndef DEPTHFORGE_MODE_H
#define DEPTHFORGE_MODE_H

#include <QtGui/QImage>
#include <Image/Image.h>

class MainUI;
class Forge;

class Mode {
public:
    MainUI *mainUI;

    Mode(MainUI *mainUI);

    virtual void drawForge(Forge *forge, Image *target, QImage *qImage) = 0;
    virtual bool mouseMoveForge(Forge *forge, int x, int y) = 0;
    virtual bool mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button) = 0;
    virtual bool mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button) = 0;

    virtual void selfLayout() = 0;
    virtual void doLayout() = 0;

};


#endif //DEPTHFORGE_MODE_H
