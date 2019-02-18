//
// Created by jwc on 12/1/18.
//

extern "C"
{
    #include "JWC_PixelGfx.h"
    #include "../Threading/Sync.h"

}

#include <QThread>



GfxThreadWorker::GfxThreadWorker(void *barrier)
{
    this->barrier = barrier;
}

//void gfxWorkerThread(void *data)
void gfxWorkerThread(void *data)
{
    GfxThreadWorker *worker = (GfxThreadWorker *)data;

    while (true)
    {
        Barrier_wait(worker->barrier);
        worker->WorkerProc(worker);
        Barrier_wait(worker->barrier);
    }
}

class MyThread : public QThread
{
public:
    void (*proc)(void *);
    void *data;

    MyThread(void (*proc)(void *), void *data);

    virtual void run();

};

MyThread::MyThread(void (*proc)(void *), void *data) : QThread(nullptr)
{
    this->proc = proc;
    this->data = data;
}

void MyThread::run()
{
    proc(data);
}

void GfxThreadWorker::begin()
{
    /* TODO */ //error handling

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
