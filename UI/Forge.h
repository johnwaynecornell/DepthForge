//
// Created by jwc on 2/16/19.
//

#ifndef DEPTHFORGE_FORGE_H
#define DEPTHFORGE_FORGE_H


#include "UI.h"
#include "../DepthForgeWin.h"

class MainWnd;

class Forge : public UI
{
public:
    bool hasMouse;
    Qt::MouseButtons mouseDown;

    double mouseX;
    double mouseY;

    Image *src;

    bool swapViews = false;
    Image *greyMap = new Image(1,1);

    int _x;
    int _y;

    int _w;
    int _h;

    int _srcW;
    int _srcH;
    int _srcX;
    int _srcY;

    QString lastPath1;
    QString lastPath2;
    QString fileName = QString();

    Image *bkgImage;
    Image *bkgTile;

    double scrollX = 0.5;
    double scrollY = 0.5;
    float scale = 1.0;

    Forge(UI *parent);
    virtual ~Forge();

    MainWnd *wnd();

    void updateGreyMap(void);
    void setMouseXY(int x, int y);

    void drawInitial();

    virtual void drawBackground(UI *member, Image *target, QImage *qImage);
    virtual void draw(Image *target, QImage *qImage);

    virtual void mouseEnter();
    virtual void mouseLeave();

    virtual bool mouseMove(int x, int y);
    virtual bool mouseButtonPress(int x, int y, Qt::MouseButton button);
    virtual bool mouseButtonRelease(int x, int y, Qt::MouseButton button);

    void open(QString &fileName);
    void save(QString &fileName);

    void file_new(UI *sender, void *arg);
    void file_open(UI *sender, void *arg);
    void file_reopen(UI *sender, void *arg);
    void file_save(UI *sender, void *arg);
    void file_save_as(UI *sender, void *arg);

    void import(UI *sender, void *arg);
    void export_anaglyph(UI *sender, void *arg);
    void export_jps(UI *sender, void *arg);
    void export_SBS_Parallel(UI *sender, void *arg);
    void export_SBS_ParallelHalf(UI *sender, void *arg);
    void export_SBS_Cross(UI *sender, void *arg);
    void export_SBS_CrossHalf(UI *sender, void *arg);
};

#endif //DEPTHFORGE_FORGE_H
