//
// Created by jwc on 2/12/19.
//

#include "MainWnd.h"
#include <QApplication>
#include <QMouseEvent>

extern QApplication *app;

MainWnd::MainWnd() : QMainWindow()
{
    QSurfaceFormat format;

    //format.setVersion(3,3);
    format.setOption(QSurfaceFormat::FormatOption::StereoBuffers);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setStereo(true);


//    format.setAlphaBufferSize(8);
//    format.setRedBufferSize(8);
//    format.setGreenBufferSize(8);
//    format.setBlueBufferSize(8);


    QSurfaceFormat::setDefaultFormat(format);

    depthForge = new DepthForgeWin(this, nullptr);

    setCentralWidget(createWindowContainer(depthForge));

    centralWidget()->setAttribute( Qt::WA_TransparentForMouseEvents );
    //depthForge->setAttribute( Qt::WA_TransparentForMouseEvents );

    //centralWidget()->setMouseTracking(true);
    setMouseTracking(true);

    createActions();
    createMenus();
}

void MainWnd::closeEvent(QCloseEvent *event)
{
    centralWidget()->close();

    delete depthForge;

    QMainWindow::closeEvent(event);
    app->quit();

    delete  centralWidget();
}

void MainWnd::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    //depthForge->show();
}


void MainWnd::createActions() {


    action_import = new QAction(tr("&Import"), this);
    action_import->setStatusTip(tr("Import image file"));
    connect(action_import, &QAction::triggered, this, &MainWnd::import);

    action_export_anaglyph = new QAction(tr("Export &Anaglyph"), this);
    action_export_anaglyph->setStatusTip(tr("Export Anaglyph image file"));
    connect(action_export_anaglyph, &QAction::triggered, this, &MainWnd::export_anaglyph);

    action_export_jps = new QAction(tr("Export &Jps"), this);
    action_export_jps->setStatusTip(tr("Export Jpeg stereo image file"));
    connect(action_export_jps, &QAction::triggered, this, &MainWnd::export_jps);

    action_toggle_fps = new QAction(tr("Toggle show &FPS"), this);
    action_toggle_fps->setStatusTip(tr("Show &Frames per second"));
    action_toggle_fps->setCheckable(true);
    connect(action_toggle_fps, &QAction::triggered, this, &MainWnd::toggle_fps);
}

void MainWnd::createMenus()
{
    QAction *File = new QAction(tr("&File"), this);

    QMenuBar *mb = menuBar();
    QMenu *file = mb->addMenu(tr("&File"));
    file->addAction(action_import);

    QMenu *Export = file->addMenu("&Export");

    Export->addAction(action_export_anaglyph);
    Export->addAction(action_export_jps);

    QMenu *Settings = mb->addMenu("&Settings");
    Settings->addAction(action_toggle_fps);
}

void MainWnd::import()
{
    if (import_proc.function != nullptr) import_proc.function(import_proc.element,
            import_proc.argument);
}

void MainWnd::export_anaglyph()
{
    if (export_anaglyph_proc.function!= nullptr) export_anaglyph_proc.function(
            export_anaglyph_proc.element, export_anaglyph_proc.argument);
}

void MainWnd::export_jps()
{
    if (export_jps_proc.function != nullptr) export_jps_proc.function(
            export_jps_proc.element, export_jps_proc.argument);
}

void MainWnd::toggle_fps()
{
    depthForge->setShowFPS(action_toggle_fps->isChecked());
}