//
// Created by jwc on 1/28/19.
//

#ifndef DEPTHFORGE_SYNC_H
#define DEPTHFORGE_SYNC_H

void *Barrier_size(void);
void Barrier_init(void *event, int Count);
bool Barrier_wait(void *event);


#endif //DEPTHFORGE_SYNC_H
