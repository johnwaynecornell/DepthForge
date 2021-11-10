//
// Created by jwc on 10/30/21.
//

#include "Brush.h"

Brush::Brush()
{
    for (int i=0; i<2; i++) {
        cacheData[i].s=-1;
        cacheData[i].dta = nullptr;
        cacheData[i].needUpdate = true;
    }

    size = .05;
    intensity = 1.0;
}

float Brush::get(float x, float y)
{
    float v = intensity + proc(x,y)*.05;
    return v;
}

void Brush::setSize(float size)
{
    if (size != this->size)
    {
        //cacheData[0].s = -1;
        //cacheData[1].s = -1;

        this->size = size;

    }
}

void Brush::setIntensity(float intensity) {
    if (intensity != this->intensity) {
        cacheData[0].needUpdate = true;
        cacheData[1].needUpdate = true;

        this->intensity = intensity;
    }
}

bool Brush::getData(int entry, int s, Cache **data)
{
    bool rc;
    if (s != cacheData[entry].s)
    {
        rc = false;
    } else rc = true;

    *data = &cacheData[entry];

    return rc;
}

float **Brush::map(int sz)
{
    int q = (sz<<1)+1;

    float *m = new float[q*q];

    float **lines = new float*[q];

    float *cur = m+sz;

    for (int y=0; y<q; y++)
    {
        lines[y] = cur;
        cur += q;
    }

    float **ret = lines+sz;

    return ret;
}

void Brush::updateMap(float **map, int sz)
{
    float _sz = (float)sz;

    for (int y=-sz; y<=sz; y++)
    {
        float _y = y /  _sz;

        for (int x=-sz; x<=sz; x++)
        {
            float _x = x / _sz;

            map[y][x] = get(_x,_y);

        }
    }
}

void Brush::freeMap(float **map, int sz)
{
    int q = (sz<<1)+1;

    float *m = map[-sz]-sz;

    delete[] (map-sz);
    delete[] m;
}