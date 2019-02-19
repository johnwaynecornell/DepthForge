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

    QApplication application(argc, argv);
    app = &application;

    GfxInitThreadWorkers(Threads);

    MainWnd Win;

    Win.resize(800,600);
    Win.show();


    application.exec();
}