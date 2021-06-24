//
// Created by jwc on 5/4/21.
//

#ifndef DEPTHFORGE_CURSOR_H
#define DEPTHFORGE_CURSOR_H

#include <Image/Image.h>
#include <Image/Geometry.h>

class Cursor {
public:

    dPnt2D Hotspot = {0,0};
    Image *src = nullptr;

    ~Cursor()
    {
        if (src != nullptr) delete src;
    }
};


#endif //DEPTHFORGE_CURSOR_H
