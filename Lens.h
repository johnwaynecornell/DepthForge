//
// Created by jwc on 2/16/19.
//

#ifndef DEPTHFORGE_Lens_H
#define DEPTHFORGE_Lens_H

#include <Image/Image.h>

typedef float (*LensProc)(float x, float y);

class Lens {
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
    LensProc proc;

    Lens();

    virtual float get(float x, float y);
    void setSize(float size);
    void setIntensity(float intensity);

    bool getData(int entry, int s, Cache **data);

    float **map(int sz);
    void freeMap(float **m, int sz);

    void updateMap(float **map, int sz);
};


#endif //DEPTHFORGE_Lens_H
