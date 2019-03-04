//
// Created by jwc on 2/12/19.
//

#ifndef DEPTHFORGE_MAINWND_H
#define DEPTHFORGE_MAINWND_H

#include "DepthForgeWin.h"

#include <QtWidgets/QMainWindow>
#include <QMenuBar>

class MainWnd : public QMainWindow{

public:
    QAction *action_import;
    QAction *action_export_anaglyph;
    QAction *action_export_jps;

    QAction *action_toggle_fps;
    QAction *action_toggle_forceAnaglyph;

    DepthForgeWin *depthForge;


    MainWnd();

    virtual void createActions();
    virtual void createMenus();

    virtual void closeEvent(QCloseEvent *event);
    virtual void showEvent(QShowEvent *event);


    UICallback<void (*)(void *elem, void *arg)> import_proc = {};
    UICallback<void (*)(void *elem, void *arg)> export_anaglyph_proc = {};
    UICallback<void (*)(void *elem, void *arg)> export_jps_proc = {};



private slots:
    void import();
    void export_anaglyph();
    void export_jps();
    void toggle_fps();
    void toggle_forceAnaglyph();
};


#endif //DEPTHFORGE_MAINWND_H
