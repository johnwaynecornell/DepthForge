//
// Created by jwc on 4/2/19.
//

#ifndef DEPTHFORGE_DEPTHEDITMODE_H
#define DEPTHFORGE_DEPTHEDITMODE_H

#include <Lense.h>
#include "Mode.h"
#include "Slider.h"
#include "TabCtl.h"

class LenseButton;
class Forge;

class Mode_DepthEdit : public Mode
{
public:
    bool previewLense;

    DepthForgeTabCtl *basicToolsCtl;
    Fixed *basicTools;

    Frame *toolFrame;
    Frame *bottomFrame;
    Fixed *tools;
    Fixed *bottom;

    Slider *slideA;
    Slider *slideB;

    Lense *lense;

    Mode_DepthEdit(MainUI *mainUI);

    void applyLense(Forge *forge);

    virtual void drawForge(Forge *forge, Image *target, QImage *qImage);

    virtual bool mouseMoveForge(Forge *forge, int x, int y);
    virtual bool mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button);

    virtual void selfLayout();
    virtual void doLayout();

    void setLense(Lense *lense);

    LenseButton * addLenseButton(int x, int y, LenseProc lensProc);

public:
    void sizeEntered(UI *sender, void *arg);
    void sizeLeave(UI *sender, void *arg);
    void sizeChanged(UI *sender, double v, void *arg);
    void intensityChanged(UI *sender, double v, void *arg);

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


#endif //DEPTHFORGE_DEPTHEDITMODE_H
