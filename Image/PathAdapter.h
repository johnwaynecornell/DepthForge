//
// Created by jwc on 3/5/19.
//

#ifndef DEPTHFORGE_PATHADAPTER_H
#define DEPTHFORGE_PATHADAPTER_H

#include "Image.h"
#include "Geometry.h"

struct dPathEntry
{
    dPnt2D A;
    dPnt2D B;

    double r;

    bool point;
    bool invert;

    void *data;

};

class PathAdapter {
public:
    dPnt2D last;
    dMatrix2D inputMatrix;
    dMatrix2D outputMatrix;

    int pathMax;
    int pathIndex;
    dPathEntry *path;

    int _preservePath;

    PathAdapter();

    void ClearPath();

    void MoveTo(dPnt2D A);
    void Circle(double r, bool Invert);
    void Circle(dPnt2D A, double r, bool Invert);
    void LineTo(dPnt2D A);
    void Line(dPnt2D A, dPnt2D B);

    void Apply(Image *image);

    void Nearest(dPnt2D interest, int &I, double &X);

    void BoundingBox(dPnt2D &topLeft, dPnt2D &bottomRight);

};


#endif //DEPTHFORGE_PATHADAPTER_H
