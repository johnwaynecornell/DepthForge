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
    centralWidget()->close();

    QMainWindow::closeEvent(event);
    app->quit();

    delete  centralWidget();
}

void MainWnd::createMenus()
{
    QAction *File = new QAction(tr("&File"), this);

    QMenuBar *mb = menuBar();
    mb->addMenu(tr("&File"));

}
