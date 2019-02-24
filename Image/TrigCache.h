//
// Created by jwc on 2/22/19.
//

#ifndef DEPTHFORGE_TRIGCACHE_H
#define DEPTHFORGE_TRIGCACHE_H

struct TrigEntry
{
public:
    bool init = false;
    int x;
    int y;
    double th;
    double cos;
    double sin;

    double rCos;
    double rSin;
    double sqrt;

    const char *tag;

    void set(int x, int y);
};

class TrigCell
{
public:
    TrigCell();
    TrigEntry *data;
};

static unsigned int places[]={0x000000FF,0x0000FF00,0x00FF0000,0xFF000000};
//static unsigned int highplaces[]={0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF};

class TrigData
{
public:

    int xkey;
    int ykey;

    int N;
    TrigData ** children;

    void *E = {};

    TrigData(int N, int xKey, int yKey);

    void ** get(unsigned int xKey, unsigned int yKey);
};

class TrigCache {
public:
    TrigData  *root[4];

    TrigCache();

    virtual void **get(int x, int y, int sx, int sy);
};

class TrigCellCache : public TrigCache
{
public:
    virtual void **get(int x, int y, int sx, int sy);
};


#endif //DEPTHFORGE_TRIGCACHE_H
