//
// Created by jwc on 2/12/19.
//

#include "MainWnd.h"
#include <QApplication>

extern QApplication *app;

MainWnd::MainWnd() : QMainWindow()
{
    setCentralWidget(new DepthForgeWin());

    createMenus();
}

void MainWnd::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    app->quit();
}

void MainWnd::createMenus()
{
    QAction *File = new QAction(tr("&File"), this);

    QMenuBar *mb = menuBar();
    mb->addMenu(tr("&File"));

}
