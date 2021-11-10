//
// Created by jwc on 10/30/21.
//

#ifndef DEPTHFORGE_BRUSH_H
#define DEPTHFORGE_BRUSH_H


#include <Image/Image.h>

typedef float (*BrushProc)(float x, float y);

class Brush {
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
    BrushProc proc;

    Brush();

    virtual float get(float x, float y);
    void setSize(float size);
    void setIntensity(float intensity);

    bool getData(int entry, int s, Cache **data);

    float **map(int sz);
    void freeMap(float **m, int sz);

    void updateMap(float **map, int sz);
};


#endif //DEPTHFORGE_BRUSH_H
