//
// Created by jwc on 2/16/19.
//

#include "Lense.h"

Lense::Lense()
{
    size = .05;
    intensity = 1.0;
}

float Lense::get(float x, float y)
{
    return proc(x,y)*intensity;
}
