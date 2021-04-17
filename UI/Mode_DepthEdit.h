//
// Created by jwc on 4/2/19.
//

#ifndef DEPTHFORGE_DEPTHEDITMODE_H
#define DEPTHFORGE_DEPTHEDITMODE_H

#include <Lens.h>
#include "Mode.h"
#include "Slider.h"
#include "TabCtl.h"

class LensButton;
class Forge;

class Mode_DepthEdit : public Mode
{
public:
    bool previewLens;

    DepthForgeTabCtl *tabCtl;
    Fixed *basicTools;

    Frame *toolFrame;
    Frame *bottomFrame;
    Fixed *tools;
    Fixed *bottom;

    Slider *slideA;
    Slider *slideB;

    Lens *lens;

    Mode_DepthEdit(MainUI *mainUI);

    void applyLens(Forge *forge);

    virtual void drawForge(Forge *forge, Image *target, QImage *qImage);

    virtual bool mouseMoveForge(Forge *forge, int x, int y);
    virtual bool mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button);

    virtual void selfLayout();
    virtual void doLayout();

    void setLens(Lens *lens);

    LensButton * addLensButton(int x, int y, LensProc lensProc, int lenssz);

public:
    void sizeEntered(UI *sender, void *arg);
    void sizeLeave(UI *sender, void *arg);
    void sizeChanged(UI *sender, double v, void *arg);
    void intensityChanged(UI *sender, double v, void *arg);

};

class LensButton : public Button_Image
{
public:
    Lens *lens;

    LensButton(UI *parent, LensProc proc, int lenssz);
    virtual ~LensButton();

    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);

    static float Sphere(float x, float y);
    static float SphereC(float x, float y);
    static float Circle(float x, float y);
    static float Pyramid(float x, float y);
    static float PyramidC(float x, float y);
    static float Square(float x, float y);

};


#endif //DEPTHFORGE_DEPTHEDITMODE_H
