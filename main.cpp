#include <iostream>

#include <QApplication>
#include <QtCore/QThread>
#include <QAbstractEventDispatcher>
#include <Image/TrigCache.h>

#include "DepthForgeWin.h"
#include "MainWnd.h"

#include "version.h"

const char VERSION[] = "0.0.2";

QApplication *app;

extern double sinTab[65536];
extern double cosTab[65536];

int main(int argc, char **argv) {

    for (int i=0; i<65536; i++)
    {
        double th = (i/65536.0)*M_PI*2;
        sinTab[i] = sin(th);
        cosTab[i] = cos(th);
    }

    Init_JWC_PixelGfx();
    int Threads = QThread::idealThreadCount();

    app = new QApplication(argc, argv);

    GfxInitThreadWorkers(Threads);

    MainWnd *Win = new MainWnd();

    Win->resize(800,800);
    Win->show();

    app->exec();

    GfxTerminate();

    delete Win;
    delete app;
}
