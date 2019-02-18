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

//int (SDLCALL * SDL_ThreadFunction) (void *data);

void GfxThreadWorker::begin()
{
    /* TODO */ //error handling

    thread = QThread::create(&gfxWorkerThread, this);
    ((QThread *)thread)->start();

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
