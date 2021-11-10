//
// Created by jwc on 4/2/19.
//

#ifndef DEPTHFORGE_DRAWMODE_H
#define DEPTHFORGE_DRAWMODE_H

#include <Image/PathAdapter.h>
#include "Brush.h"
#include "Mode.h"
#include "UI.h"
#include "TabCtl.h"
#include "Slider.h"
#include "common.h"

class BrushButton;
class Forge;

class Mode_Draw : public Mode
{
public:
    bool previewBrush;

    Fixed *basicTools;

    Frame *toolFrame;
    Frame *bottomFrame;
    Fixed *tools;
    Fixed *bottom;

    Slider *slideA;
    Slider *slideB;

    Brush *lens;

    Mode_Draw(MainUI *mainUI);

    void applyBrush(Forge *forge);

    virtual void drawForge(Forge *forge, Image *target, QImage *qImage);

    virtual bool mouseMoveForge(Forge *forge, int x, int y);
    virtual bool mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button);

    virtual void selfLayout();
    virtual void doLayout();

    void setBrush(Brush *lens);

    BrushButton * addBrushButton(int x, int y, BrushProc lensProc, int lenssz);

public:
    void sizeEntered(UI *sender, void *arg);
    void sizeLeave(UI *sender, void *arg);
    void sizeChanged(UI *sender, double v, void *arg);
    void intensityChanged(UI *sender, double v, void *arg);

};

class BrushButton : public Button_Image
{
public:
    Brush *lens;

    BrushButton(UI *parent, BrushProc proc, int lenssz);
    virtual ~BrushButton();

    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);

    static float Sphere(float x, float y);
    static float SphereC(float x, float y);
    static float Circle(float x, float y);
    static float Pyramid(float x, float y);
    static float PyramidC(float x, float y);
    static float Square(float x, float y);

};


#endif //DEPTHFORGE_PATHMODE_H
