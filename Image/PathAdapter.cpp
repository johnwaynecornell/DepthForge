//
// Created by jwc on 3/5/19.
//

#include <QtCore/QtCore>
#include "PathAdapter.h"

PathAdapter::PathAdapter()
{
    ClearPath();
    inputMatrix.Identity();
    outputMatrix.Identity();

    pathMax = 1024;
    path = new dPathEntry[pathMax];
}

void PathAdapter::ClearPath()
{
    _preservePath = 0;
    pathIndex = 0;

}

void PathAdapter::MoveTo(dPnt2D A)
{
    last = A;
}
void PathAdapter::Circle(double r, bool Invert)
{
    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {last, last, r, true, Invert};
    pathIndex++;

}
void PathAdapter::Circle(dPnt2D A, double r, bool Invert)
{
    A = inputMatrix * A;

    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {A, A, r, true, Invert};
    pathIndex++;

    last = A;
}

void PathAdapter::Line(dPnt2D A, dPnt2D B)
{
    A = inputMatrix * A;
    B = inputMatrix * B;

    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {A, B, 0, false, false};
    pathIndex++;

    last = B;

}
void PathAdapter::LineTo(dPnt2D A)
{
    A = inputMatrix * A;

    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {last, A, 0, false, false};
    pathIndex++;

    last = A;
}

void PathAdapter::Apply(Image *image)
{
    for (int i=0; i<pathIndex; i++)
    {
        dPathEntry &dp = path[i];
        PathEntry &p = image->path[image->pathIndex];

        dPnt2D A, B, C;

        A = outputMatrix * dp.A;
        B = outputMatrix * dp.B;
        C = outputMatrix * dPnt2D { dp.r, dp.r };

        p.x1 = (int) A.x;
        p.y1 = (int) A.y;

        p.x2 = (int) B.x;
        p.y2 = (int) B.y;

        p.r = (int) sqrt(C.x*C.x+C.y*C.y);

        p.invert = dp.invert;
        p.point = dp.point;

        image->pathIndex++;
    }
}