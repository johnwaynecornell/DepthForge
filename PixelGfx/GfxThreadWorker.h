//
// Created by jwc on 12/1/18.
//

#ifndef X_IO_THREADWORKER_H
#define X_IO_THREADWORKER_H

#include <string.h>

struct GfxThreadWorker;

struct GfxThreadWorker {
public:
    void *(*WorkerProc)(GfxThreadWorker *worker);
    void *barrier;
    void *thread;

    int index = -1;
    int of = 0;

    int w[32];
    int h[32];
    int x[32];
    int y[32];

    int i[32];

    int e[32];

    void *p[32];

    GfxThreadWorker(void *barrier);
    virtual ~GfxThreadWorker();

    void begin();
};

extern thread_local GfxThreadWorker **gfxThreadWorkers;
extern thread_local int gfxThreadWorkerCount;
extern thread_local void *gfxThreadWorkerBarrier;

#endif //X_IO_THREADWORKER_H
