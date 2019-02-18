//
// Created by jwc on 1/28/19.
//

extern "C"
{
#include "Sync.h"
}

#include <QMutex>
#include <QWaitCondition>

struct _barrier {
    QMutex *mutex;
//    pthread_mutex_t mutexreceived;

    QWaitCondition *cond;
//    pthread_cond_t condreceived;

    int received;
    int current;
    int count;
};

void *Barrier_size(void)
{
    return (void *) sizeof(_barrier);
}

void Barrier_init(void *event, int Count)
{
    struct _barrier *ev = (struct _barrier *) event;

    ev->mutex = new QMutex();
    ev->cond = new QWaitCondition();

    ev->count = Count;
    ev->current = Count;
    ev->received = Count;
}

bool Barrier_wait(void *event) {
    struct _barrier *ev = (struct _barrier *) event;

    bool rc;
    {
        ev->mutex->lock();

        while (ev->received != ev->count)
            while (!ev->cond->wait(ev->mutex));


        //pthread_mutex_unlock(&ev->mutex);
    }

    {
        //while (pthread_mutex_lock(&ev->mutex) != 0);
        ev->current--;

        rc = ev->current == 0;

        if (rc) ev->received = 0;

        ev->cond->notify_all();
        //pthread_mutex_unlock(&ev->mutex);
    }

    {
        //while (pthread_mutex_lock(&ev->mutex) != 0);

        while (ev->current != 0)
            while (!ev->cond->wait(ev->mutex));

        //pthread_mutex_unlock(&ev->mutex);
    }

    bool rc2;

    {
        //while (pthread_mutex_lock(&ev->mutex) != 0);
        ev->received++;


        rc2 = ev->received == ev->count;

        if (rc2)
            ev->current = ev->count;

        ev->cond->notify_all();
        ev->mutex->unlock();
    }

    return rc;
}
