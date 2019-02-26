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
    QAction *action_toggle_fps;
    QAction *action_import;
    QAction *action_export_anaglyph;
    QAction *action_export_jps;

    MainWnd();

    virtual void createActions();
    virtual void createMenus();

    virtual void closeEvent(QCloseEvent *event);

    UICallback<void (*)(UI *elem, void *arg)> import_proc = {};
    UICallback<void (*)(UI *elem, void *arg)> export_anaglyph_proc = {};
    UICallback<void (*)(UI *elem, void *arg)> export_jps_proc = {};

private slots:
    void import();
    void export_anaglyph();
    void export_jps();
    void toggle_fps();
};


#endif //DEPTHFORGE_MAINWND_H
