#include <iostream>

#include <QApplication>
#include <QtCore/QThread>
#include <QAbstractEventDispatcher>

#include "DepthForgeWin.h"
#include "MainWnd.h"

QApplication *app;

int main(int argc, char **argv) {

    Init_JWC_PixelGfx();
    int Threads = QThread::idealThreadCount();

    app = new QApplication(argc, argv);

    GfxInitThreadWorkers(Threads);

    MainWnd *Win = new MainWnd();

    Win->resize(800,600);
    Win->show();

    app->exec();

    GfxTerminate();

    delete Win;
    delete app;
}