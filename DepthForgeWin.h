//
// Created by jwc on 1/28/19.
//

#ifndef DEPTHFORGE_DEPTHFORGEWIN_H
#define DEPTHFORGE_DEPTHFORGEWIN_H

#include <QOpenGLWindow>
#include <QAbstractEventDispatcher>
#include <Image/Image.h>
#include <QtOpenGL/QGLWidget>
#include <UI/UI.h>
#include <UI/MainUI.h>

extern "C"
{
    #include "PixelGfx/JWC_PixelGfx.h"
}

class MainUI;

class DepthForgeWin : public QGLWidget
{
    Q_OBJECT
public:

    int Width;
    int Height;

    PixType RenderBufferType;

    QImage *rend;
    Image *UI_Image;

    Image *UI_ImageAnaglyph;
    Image *UI_ImageLeft;
    Image *UI_ImageRight;
    bool StereoPresent;

    QAbstractEventDispatcher *dispatcher;

    bool hasMouse;

    UI *ui;

    virtual void paintGL();
    virtual void resizeGL(int w,int h);

    virtual void mouseMoveEvent(QMouseEvent *eventMove);
    virtual void mousePressEvent(QMouseEvent *eventPress);
    virtual void mouseReleaseEvent(QMouseEvent *releaseEvent);

    DepthForgeWin();

    virtual void MouseButtonDown();

    virtual void OnIdle(void);

    void takeMouse();
    bool checkRelinquishMouse(int x, int y);

private slots:
    void aboutToBlock();
};


#endif //DEPTHFORGE_DEPTHFORGEWIN_H
