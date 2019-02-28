//
// Created by jwc on 2/16/19.
//

#ifndef DEPTHFORGE_LENSE_H
#define DEPTHFORGE_LENSE_H

#include <Image/Image.h>

typedef float (*LenseProc)(float x, float y);

class Lense {
public:
    struct Cache
    {
        bool needUpdate;
        int s;
        void *dta;
    };

    Cache cacheData[2];

    float size;
    float intensity;
    LenseProc proc;

    Lense();

    virtual float get(float x, float y);
    void setSize(float size);
    void setIntensity(float intensity);

    bool getData(int entry, int s, Cache **data);

    float **map(int sz);
    void freeMap(float **m, int sz);

    void updateMap(float **map, int sz);
};


#endif //DEPTHFORGE_LENSE_H
