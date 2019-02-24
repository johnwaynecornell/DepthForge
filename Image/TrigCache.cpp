//
// Created by jwc on 2/22/19.
//

#include "TrigCache.h"
#include <math.h>
#include <cstdio>

void TrigEntry::set(int x, int y)
{
    this->init = true;

    this->x = x;
    this->y = y;

    this->th = atan2((double) y,(double) x);
    this->cos = ::cos(this->th);
    this->sin = ::sin(this->th);

    this->rCos = ::cos(-this->th);
    this->rSin = ::sin(-this->th);

    this->sqrt = x * rCos - y * rSin;
}

TrigCell::TrigCell()
{
    data = new TrigEntry[0x100*0x100];
}

TrigData::TrigData(int N, int xKey, int yKey) {
    this->xkey = xkey;
    this->ykey = ykey;

    if (N == -1) { children = nullptr; }
    else {
        children = new TrigData *[0x100*0x100];
/*
        if (N == 0) {
            for (int i = 0; i < 0x100 * 0x100; i++) children[i] = new TrigData<Q> i);
        } else
  */
            for (int i = 0; i < 0x100 * 0x100; i++) children[i] = nullptr;
    }
    this->N = N;
}

void ** TrigData::get(unsigned int xKey, unsigned int yKey)
{
    TrigData *t = this;

    int k;

    while (t->N > 0)
    {
        unsigned int _xKey = (xKey & places[(t->N-1)])>>((t->N-1)<<3);
        unsigned int _yKey = (yKey & places[(t->N-1)])>>((t->N-1)<<3);

        k = (_yKey<<8)+_xKey;
        if (t->children[k] == nullptr)
        {
            t->children[k] = new TrigData(t->N-1, _xKey, _yKey);
        }
        t = t->children[k];
    }

    return &t->E;

    /*
    //unsigned int pKey = Key & highplaces[N];

    TrigData<Q> *t = this;
    TrigData<Q> *o = this;

    int ii, i =0;


    int n = t->N;

    for (i=3; i>n; i--) if ((Key & places[i]) !=0) break;

    ii = i;


    if (i>t->N)
    {
        TrigData<Q> *p = this;

        do {
            t = p;
            p = new TrigData<Q>(t->N + 1, 0);
            p->children[t->key] = t;

            i--;
        } while (i>t->N);

        *link = p;

        i = ii;

        for (int i=n+1; i<=ii; i++)
        {
            unsigned int k = (Key & places[i]) >> (i<<3);

            t = new TrigData<Q>(i, k);
            p->children[k] = t;

            p = t;
        }

        p->children[o->key] = o;

        t = o;
    }


    while (t->N != 0)
    {
        int k = (Key & places[(t->N)])>>((t->N)<<3);
        if (t->children[k] == nullptr)
        {
            t = t->children[k] = new TrigData<Q>(t->N-1, k);
        } else t = t->children[k];
    }

    return &t->children[Key&0xFF]->E;
     */
}

TrigCache::TrigCache()
{
    for (int i=0; i<4; i++) root[i] = new TrigData(0,0, 0);
}

void ** TrigCache::get(int x, int y, int sx, int sy)
{
    int e = 0;

    int xKey;
    int yKey;

    if (sx<0)
    {
        e += 1;
    }

    xKey = x;

    if (sy<0)
    {
        e += 2;
    }

    yKey = y;

    TrigData **r = root+e;

    int xi;
    for (xi=3; xi>=0; xi--) if ((xKey & places[xi]) !=0) break;

    int yi;
    for (yi=3; yi>=0; yi--) if ((yKey & places[yi]) !=0) break;

    int i = yi > xi ? yi : xi;

    TrigData *cur = *r;

    while (i>=cur->N)
    {
        *r = new TrigData(cur->N+1, 0, 0);
        (*r)->children[0] = cur;
        cur = *r;
    }

    return cur->get(xKey, yKey);

    //printf("TrigCache::get(%d,%d)\n", x, y);

    /*
    TrigData<TrigEntry> **_y = root[e]->get(yKey, &root[e], nullptr);
    if (*_y == nullptr)
        *_y = new TrigData<TrigEntry>(0,0);
    TrigEntry *_x = (*_y)->get(xKey, _y, nullptr);

    if (!_x->init) _x->set(x,y);
*/
    //return _x;

}

void** TrigCellCache::get(int x, int y, int sx, int sy)
{
    void **r = TrigCache::get(x,y, sx, sy);
    if (*r == nullptr)
    {
        TrigCell *tc;

        *r = tc = new TrigCell();

        int xx = x<<8;
        int yy = y<<8;

        for (int _y=0; _y<0x100; _y++)
        {
            for (int _x=0; _x<0x100; _x++)
            {
                tc->data[(_y<<8)+_x].set((xx+_x)*sx, (yy+_y)*sy);
            }
        }
    }

    return r;
}