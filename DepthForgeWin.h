//
// Created by jwc on 1/28/19.
//

#ifndef DEPTHFORGE_DEPTHFORGEWIN_H
#define DEPTHFORGE_DEPTHFORGEWIN_H

#include <QOpenGLWindow>
#include <QAbstractEventDispatcher>
#include <QtOpenGL/QGLWidget>
#include <QMainWindow>

#include "Image/Image.h"
#include "UI/UI.h"
#include "UI/MainUI.h"

#include "FpsMonitor.h"

extern "C"
{
    #include "PixelGfx/JWC_PixelGfx.h"
}

class MainUI;

class DepthForgeWin : public QOpenGLWindow//QGLWidget
{
    Q_OBJECT
public:

    int Width;
    int Height;

    int oldWidth=-1;
    int oldHeight=-1;

    FpsMonitor fps;

    PixType RenderBufferType;

    QMainWindow *parent;

    QImage *rend;
    Image *UI_Image;

    bool anaglyph;
    bool forceAnaglyph;
    bool real_stereo;

    Image *UI_ImageAnaglyph;
    Image *UI_ImageLeft;
    Image *UI_ImageRight;

    BGRA *obuf;

    bool showFPS;
    bool showMouse = true;

    QAbstractEventDispatcher *dispatcher;

    bool hasMouse;

    UI *ui;

    UI *mouseCapture;

    int lastMouseX;
    int lastMouseY;

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w,int h);

    virtual void closeEvent(QCloseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *eventMove);
    virtual void mousePressEvent(QMouseEvent *eventPress);
    virtual void mouseReleaseEvent(QMouseEvent *releaseEvent);

    void giveMouse(UI *element);
    void freeMouse(UI *element);

    void takeMouse();
    bool checkRelinquishMouse(int x, int y);

    DepthForgeWin(QMainWindow *appWindow, QWindow *parent);

    virtual void MouseButtonDown();

    virtual void OnIdle(void);

    void checkResize();

    void setShowFPS(bool state);

    void take_picture_jps(UI *sender, void *arg);
    void take_picture_ana(UI *sender, void *arg);

private slots:
    void aboutToBlock();
};


#endif //DEPTHFORGE_DEPTHFORGEWIN_H
