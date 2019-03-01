//
// Created by jwc on 12/1/18.
//

extern "C"
{
    #include "JWC_PixelGfx.h"
    #include "../Threading/Sync.h"

}

#include <QApplication>
#include <QThread>

class MyThread : public QThread
{
public:
    void (*proc)(void *);
    void *data;

    bool doRun;

    MyThread(void (*proc)(void *), void *data);
    virtual ~MyThread();

    virtual void run();

private slots:
    void aboutToQuit();

};

GfxThreadWorker::GfxThreadWorker(void *barrier)
{
    this->barrier = barrier;
}

GfxThreadWorker::~GfxThreadWorker()
{
    ((MyThread *)thread)->wait();
    delete ((MyThread *)thread);
}

//void gfxWorkerThread(void *data)
void gfxWorkerThread(void *data)
{
    GfxThreadWorker *worker = (GfxThreadWorker *)data;

    //while ()
    {
        Barrier_wait(worker->barrier);
        if (((MyThread *)worker->thread)->doRun) {
            worker->WorkerProc(worker);
            Barrier_wait(worker->barrier);
        }
    }
}

extern QApplication *app;

MyThread::MyThread(void (*proc)(void *), void *data) : QThread(nullptr)
{

    this->proc = proc;
    this->data = data;
    doRun = true;

    QApplication::connect(app, &QApplication::aboutToQuit, this, &MyThread::aboutToQuit);
}

MyThread::~MyThread()
{
    QApplication::disconnect(app, &QApplication::aboutToQuit, this, &MyThread::aboutToQuit);
}

void MyThread::run()
{
    while (doRun) {
        proc(data);
    }
}

void MyThread::aboutToQuit()
{
    doRun = false;
}

void GfxThreadWorker::begin()
{
    thread = new MyThread(&gfxWorkerThread, this);

    ((MyThread *)thread)->start();

    //SDL_CreateThread(gfxWorkerThread, "SliceThread", this);

    //pthread_create(&thread, nullptr, (void *(*)(void *))gfxWorkerThread, this);

}


thread_local GfxThreadWorker **gfxThreadWorkers = nullptr;
thread_local int gfxThreadWorkerCount = 0;
thread_local void *gfxThreadWorkerBarrier = nullptr;

void GfxInitThreadWorkers(int count)
{
    gfxThreadWorkers = new GfxThreadWorker*[count];
    gfxThreadWorkerCount = count;

    gfxThreadWorkerBarrier = new unsigned char[(unsigned long) Barrier_size()];
    Barrier_init(gfxThreadWorkerBarrier, count+1);

    for (int i=0; i<count; i++)
    {
        gfxThreadWorkers[i] = new GfxThreadWorker(gfxThreadWorkerBarrier);
        gfxThreadWorkers[i]->index = i;
        gfxThreadWorkers[i]->of = count;
        gfxThreadWorkers[i]->begin();
    }
}

void GfxTerminate()
{
    Barrier_wait(gfxThreadWorkerBarrier);

    for (int i=0; i<gfxThreadWorkerCount; i++)
    {
        delete gfxThreadWorkers[i];
    }

    delete [] gfxThreadWorkers;
}
