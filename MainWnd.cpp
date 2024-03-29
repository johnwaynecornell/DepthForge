//
// Created by jwc on 2/12/19.
//

#include <QApplication>
#include <QMouseEvent>

#include "MainWnd.h"

extern QApplication *app;

MainWnd::MainWnd() : QMainWindow()
{

#ifdef WIN32
    setWindowIcon(QIcon("DepthForge.ico"));
#endif

    QSurfaceFormat format;

    format.setVersion(1,1);
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

    action_export_anaglyph = new QAction(tr("Export &anaglyph"), this);
    action_export_anaglyph->setStatusTip(tr("Export anaglyph image file"));
    connect(action_export_anaglyph, &QAction::triggered, this, &MainWnd::export_anaglyph);

    action_export_jps = new QAction(tr("Export &Jps"), this);
    action_export_jps->setStatusTip(tr("Export Jpeg stereo image file"));
    connect(action_export_jps, &QAction::triggered, this, &MainWnd::export_jps);

    action_export_SBS_Parallel = new QAction(tr("Export Side by Side &Parallel"), this);
    action_export_SBS_ParallelHalf = new QAction(tr("Export Side by Side Parallel Half"), this);
    action_export_SBS_Cross = new QAction(tr("Export Side by Side &Cross view"), this);
    action_export_SBS_CrossHalf = new QAction(tr("Export Side by Side Cross view Half"), this);

    action_export_SBS_Parallel->setStatusTip(tr("Export side by side stereo"));
    action_export_SBS_ParallelHalf->setStatusTip(tr("Export half width side by side stereo"));
    action_export_SBS_Cross->setStatusTip(tr("Export side by side cross view stereo"));
    action_export_SBS_CrossHalf->setStatusTip(tr("Export side by side cross view half width stereo"));

    connect(action_export_SBS_Parallel, &QAction::triggered, this, &MainWnd::export_SBS_Parallel);
    connect(action_export_SBS_ParallelHalf, &QAction::triggered, this, &MainWnd::export_SBS_ParallelHalf);
    connect(action_export_SBS_Cross, &QAction::triggered, this, &MainWnd::export_SBS_Cross);
    connect(action_export_SBS_CrossHalf, &QAction::triggered, this, &MainWnd::export_SBS_CrossHalf);

    action_file_new = new QAction(tr("&New"), this);
    action_file_new->setStatusTip(tr("Create new"));
    connect(action_file_new, &QAction::triggered, this, &MainWnd::file_new);

    action_file_open = new QAction(tr("&Open"), this);
    action_file_open->setStatusTip(tr("Open .dfg file"));
    connect(action_file_open, &QAction::triggered, this, &MainWnd::file_open);


    action_file_reopen = new QAction(tr("&Reopen"), this);
    action_file_reopen->setStatusTip(tr("Re-open .dfg file"));
    connect(action_file_reopen, &QAction::triggered, this, &MainWnd::file_reopen);

    action_file_save = new QAction(tr("&Save"), this);
    action_file_save->setStatusTip(tr("Save .dfg file"));
    connect(action_file_save, &QAction::triggered, this, &MainWnd::file_save);

    action_file_save_as = new QAction(tr("Save &as"), this);
    action_file_save_as->setStatusTip(tr("Save .dfg file as ..."));
    connect(action_file_save_as, &QAction::triggered, this, &MainWnd::file_save_as);
    
    action_toggle_fps = new QAction(tr("Toggle show &FPS"), this);
    action_toggle_fps->setStatusTip(tr("Show &Frames per second"));
    action_toggle_fps->setCheckable(true);
    connect(action_toggle_fps, &QAction::triggered, this, &MainWnd::toggle_fps);

    action_toggle_forceAnaglyph = new QAction(tr("Toggle force &Aanaglyph"), this);
    action_toggle_forceAnaglyph->setStatusTip(tr("force to anaglyph mode"));
    action_toggle_forceAnaglyph->setCheckable(true);
    connect(action_toggle_forceAnaglyph, &QAction::triggered, this, &MainWnd::toggle_forceAnaglyph);

    action_toggle_SBSHalf = new QAction(tr("Toggle &SBS half width (TV Mode)"), this);
    action_toggle_SBSHalf->setStatusTip(tr("Toggle &SBS half width (TV Mode)"));
    action_toggle_SBSHalf->setCheckable(true);
    connect(action_toggle_SBSHalf, &QAction::triggered, this, &MainWnd::toggle_SBSHalf);
}

void MainWnd::createMenus()
{
    QAction *File = new QAction(tr("&File"), this);

    QMenuBar *mb = menuBar();
    QMenu *file = mb->addMenu(tr("&File"));
    
    file->addAction(action_file_new);
    file->addAction(action_file_open);
    file->addAction(action_file_reopen);
    file->addAction(action_file_save);
    file->addAction(action_file_save_as);

    file->addSeparator();
    
    file->addAction(action_import);

    QMenu *Export = file->addMenu("&Export");

    Export->addAction(action_export_anaglyph);
    Export->addAction(action_export_jps);
    
    QMenu *Export_SBS = Export->addMenu("&Side by side");

    Export_SBS->addAction(action_export_SBS_Parallel);
    Export_SBS->addAction(action_export_SBS_ParallelHalf);
    Export_SBS->addAction(action_export_SBS_Cross);
    Export_SBS->addAction(action_export_SBS_CrossHalf);

    QMenu *Settings = mb->addMenu("&Settings");
    Settings->addAction(action_toggle_fps);
    Settings->addAction(action_toggle_forceAnaglyph);
    Settings->addAction(action_toggle_SBSHalf);
}

void MainWnd::setFileName(QString &fileName)
{

    if (fileName.isNull()) setWindowTitle(tr("DepthForge"));
    else
    {
        setWindowTitle(fileName);
    }
}

void MainWnd::import()
{
    if (import_proc.function != nullptr) import_proc.function(
                import_proc._This, import_proc.element,import_proc.argument);
}

void MainWnd::file_new()
{
    if (file_new_proc.function != nullptr) file_new_proc.function(
                file_new_proc._This, file_new_proc.element,file_new_proc.argument);
}
void MainWnd::file_open()
{
    if (file_open_proc.function != nullptr) file_open_proc.function(
                file_open_proc._This, file_open_proc.element,file_open_proc.argument);
}
void MainWnd::file_reopen()
{
    if (file_reopen_proc.function != nullptr) file_reopen_proc.function(
                file_reopen_proc._This, file_reopen_proc.element,file_reopen_proc.argument);
}
void MainWnd::file_save()
{
    if (file_save_proc.function != nullptr) file_save_proc.function(
                file_save_proc._This, file_save_proc.element,file_save_proc.argument);
}
void MainWnd::file_save_as()
{
    if (file_save_as_proc.function != nullptr) file_save_as_proc.function(
                file_save_as_proc._This, file_save_as_proc.element,file_save_as_proc.argument);
}

void MainWnd::export_anaglyph()
{
    if (export_anaglyph_proc.function!= nullptr) export_anaglyph_proc.function(
            export_anaglyph_proc._This, export_anaglyph_proc.element, export_anaglyph_proc.argument);
}

void MainWnd::export_jps()
{
    if (export_jps_proc.function != nullptr) export_jps_proc.function(
            export_jps_proc._This, export_jps_proc.element, export_jps_proc.argument);
}

void MainWnd::export_SBS_Parallel()
{
    if (export_SBS_Parallel_proc.function != nullptr) export_SBS_Parallel_proc.function(
                export_SBS_Parallel_proc._This, export_SBS_Parallel_proc.element, export_SBS_Parallel_proc.argument);
}

void MainWnd::export_SBS_ParallelHalf()
{
    if (export_SBS_ParallelHalf_proc.function != nullptr) export_SBS_ParallelHalf_proc.function(
                export_SBS_ParallelHalf_proc._This, export_SBS_ParallelHalf_proc.element, export_jps_proc.argument);
}

void MainWnd::export_SBS_Cross()
{
    if (export_SBS_Cross_proc.function != nullptr) export_SBS_Cross_proc.function(
                export_SBS_Cross_proc._This, export_SBS_Cross_proc.element, export_SBS_Cross_proc.argument);
}

void MainWnd::export_SBS_CrossHalf()
{
    if (export_SBS_CrossHalf_proc.function != nullptr) export_SBS_CrossHalf_proc.function(
                export_SBS_CrossHalf_proc._This, export_SBS_CrossHalf_proc.element, export_SBS_CrossHalf_proc.argument);
}


/*
export_SBS_Parallel;
export_SBS_ParallelHalf;
export_SBS_Cross;
export_SBS_CrossHalf;
*/

void MainWnd::toggle_fps()
{
    depthForge->setShowFPS(action_toggle_fps->isChecked());
}

void MainWnd::toggle_forceAnaglyph()
{
    depthForge->forceAnaglyph = action_toggle_forceAnaglyph->isChecked();
    if (depthForge->forceAnaglyph)
    {
        action_toggle_SBSHalf->setChecked(false);
        depthForge->SBSHalf = false;
    }
}

void MainWnd::toggle_SBSHalf()
{
    depthForge->SBSHalf = action_toggle_SBSHalf->isChecked();
    if (depthForge->SBSHalf)
    {
        action_toggle_forceAnaglyph->setChecked(false);
        depthForge->forceAnaglyph = false;
    }
}