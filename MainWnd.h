//
// Created by jwc on 2/12/19.
//

#ifndef DEPTHFORGE_MAINWND_H
#define DEPTHFORGE_MAINWND_H


#include <QtWidgets/QMainWindow>
#include <QMenuBar>
#include "DepthForgeWin.h"

class MainWnd : public QMainWindow{

public:

    MainWnd();

    virtual void createMenus();

    virtual void closeEvent(QCloseEvent *event);

};


#endif //DEPTHFORGE_MAINWND_H
