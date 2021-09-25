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
    QAction *action_export_SBS_Parallel;
    QAction *action_export_SBS_ParallelHalf;
    QAction *action_export_SBS_Cross;
    QAction *action_export_SBS_CrossHalf;

    QAction *action_file_new;
    QAction *action_file_open;
    QAction *action_file_reopen;

    QAction *action_file_save;
    QAction *action_file_save_as;

    QAction *action_toggle_fps;
    QAction *action_toggle_forceAnaglyph;

    DepthForgeWin *depthForge;

    MainWnd();

    virtual void createActions();
    virtual void createMenus();

    virtual void closeEvent(QCloseEvent *event);
    virtual void showEvent(QShowEvent *event);

    UICallback<void (*)(void *elem, UI *sender, void *arg)> file_new_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> file_open_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> file_reopen_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> file_save_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> file_save_as_proc = {};

    UICallback<void (*)(void *elem, UI *sender, void *arg)> import_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> export_anaglyph_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> export_jps_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> export_SBS_Parallel_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> export_SBS_ParallelHalf_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> export_SBS_Cross_proc = {};
    UICallback<void (*)(void *elem, UI *sender, void *arg)> export_SBS_CrossHalf_proc{};

    void setFileName(QString &file);

private slots:
    void import();
    void export_anaglyph();
    void export_jps();
    void export_SBS_Parallel();
    void export_SBS_ParallelHalf();
    void export_SBS_Cross();
    void export_SBS_CrossHalf();

    void file_new();
    void file_open();
    void file_reopen();

    void file_save();
    void file_save_as();

    void toggle_fps();
    void toggle_forceAnaglyph();

};


#endif //DEPTHFORGE_MAINWND_H
