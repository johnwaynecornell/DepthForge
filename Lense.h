//
// Created by jwc on 2/16/19.
//

#ifndef DEPTHFORGE_LENSE_H
#define DEPTHFORGE_LENSE_H

typedef float (*LenseProc)(float x, float y);

class Lense {
public:
    float size;
    float intensity;
    LenseProc proc;

    Lense();

    virtual float get(float x, float y);
};


#endif //DEPTHFORGE_LENSE_H
