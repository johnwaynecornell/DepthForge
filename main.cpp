#include <iostream>

#include <QApplication>
#include <QtCore/QThread>
#include <QAbstractEventDispatcher>

#include "DepthForgeWin.h"
#include "MainWnd.h"

int main(int argc, char **argv) {

    Init_JWC_PixelGfx();
    int Threads = QThread::idealThreadCount();

    GfxInitThreadWorkers(Threads);

    QApplication application(argc, argv);

    MainWnd Win;

    Win.resize(800,600);
    Win.show();


    application.exec();
}