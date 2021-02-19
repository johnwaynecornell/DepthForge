//
// Created by jwc on 4/2/19.
//

#ifndef DEPTHFORGE_PATHMODE_H
#define DEPTHFORGE_PATHMODE_H

#include <Image/PathAdapter.h>
#include "Mode.h"
#include "UI.h"
#include "TabCtl.h"

class Mode_Path : public Mode
{
public:
    DepthForgeTabCtl *pathToolsCtl;

    Fixed *pathToolsFixed;

    Frame *pathToolsFrame;
    Frame *pathOpsFrame;


    Fixed *pathTools;
    Fixed *pathOps;

    Button_Image *button_Divide;
    Button_Image *button_Move;
    Button_Image *button_Plus;
    Button_Image *button_Connect;
    Button_Image *button_Select;

    Button_Image *button_ShapeToggle;


    Image *image_Divide;
    Image *image_Move;
    Image *image_Plus;
    Image *image_Connect;
    Image *image_Select;

    Image *image_ShapeToggle;

    Image *image_Divide_t;
    Image *image_Move_t;
    Image *image_Plus_t;
    Image *image_Connect_t;
    Image *image_Select_t;
    Image *image_ShapeToggle_t;

    std::list<dPnt2D> points;

    int pointsCurrent;

    PathAdapter pth;

    ARGB pathPixles[16];

    int nearestIndex=-1;
    double nearestX;

    bool mouseDown = false;
    int mouseX = 0;
    int mouseY = 0;

    enum SubMode
    {
        SubMode_None,
        SubMode_Divide,
        SubMode_Move,
        SubMode_Plus,
        SubMode_Connect,
        SubMode_Select
    };

    SubMode subMode;

    Button_Image *curSubModeButton;

    int selectedPnt = -1;
    int nearsetPnt = -1;

    Mode_Path(MainUI *mainUI);

    Button_Image *addButton(UI *parent, int x, int y, Image *img, Image *img_t);
    Button_Image *addButton2(UI *parent, int x, int y, Image *img, Image *img_t);
    void refreshPth();


    virtual void drawForge(Forge *forge, Image *target, QImage *qImage);

    virtual bool mouseMoveForge(Forge *forge, int x, int y);
    virtual bool mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button);

    virtual void selfLayout();
    virtual void doLayout();

    int nearest(dPnt2D c);

private:
    void BuildDivide();
    void BuildMove();
    void BuildPlus();
    void BuildConnect();
    void BuildSelect();
    void BuildShapeToggle();
};

#endif //DEPTHFORGE_PATHMODE_H
