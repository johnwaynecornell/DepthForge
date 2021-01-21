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

    last = {INFINITY,INFINITY};
}

void PathAdapter::ClearPath()
{
    _preservePath = 0;
    pathIndex = 0;

    last = {INFINITY,INFINITY};
}

void PathAdapter::MoveTo(dPnt2D A)
{
    A = inputMatrix * A;
    last = A;
}
void PathAdapter::Circle(double r, bool Invert)
{
    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {last, last, r, true, Invert, nullptr};
    pathIndex++;

}
void PathAdapter::Circle(dPnt2D A, double r, bool Invert)
{
    A = inputMatrix * A;

    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {A, A, r, true, Invert, nullptr};
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

    bool clearPath = _preservePath == 0;
    if (!clearPath) _preservePath--; else ClearPath();
}

struct dpdata
{
    double mv = INFINITY;
    double x;
    double _x;
    int i = -1;
};


#define pathApply(v, _x, d, i, __x) \
{\
    if (abs(abs(v) - abs(d->mv)) < .00001) {\
        if (abs(_x) < abs(d->x)) {\
            {\
                d->mv = v;\
                d->i = i;\
                d->x = _x;\
                d->_x = __x;\
            }\
        }\
    } else if (abs(v) < abs(d->mv)) {\
        d->mv = v;\
        d->i = i;\
        d->x = _x;\
        d->_x = __x;\
    }\
}

void PathAdapter::Nearest(dPnt2D interest, int &I,double &X)
{
    double x = interest.x;
    double y = interest.y;

    dpdata _d;
    dpdata *d = &_d;

    for (int i=0; i<pathIndex; i++) {

        dPathEntry *pe = path + i;

        if (!pe->point) {

            double x1 = pe->A.x;
            double y1 = pe->A.y;

            double xd = pe->B.x - x1;
            double yd = pe->B.y - y1;

            double th = -atan2(yd, xd);

            if (th < 0) th += M_PI * 2;

            double cs = cos(th);
            double sn = sin(th);

//    int q = (int) ((th/(M_PI*2))*65536);

            double _sqrt = sqrt(xd * xd + yd * yd);

            //for (int y = ly; y < hy; y++) {
            //    for (int x = 0; x < Width; x++) {

            double xx = x - x1;
            double yy = y - y1;


            //if (absmvsqr +10> (xx*xx+yy*yy))
            {
                //Q_ASSERT(E->x == xd && E->y == yd);

                /*
                double cs = E->rCos;
                double sn = E->rSin;
                double _sqrt = E->sqrt;
                */


                double __x = xx * cs - yy * sn;
                double __y = yy * cs + xx * sn;

                double _x = __x;
                double _y = __y;

                if ((_x >= 0) && (_x <= _sqrt)) {
                    _x = 0;
                } else if (_x < 0) {
                    _x = _x;
                } else if (_x > _sqrt) {
                    _x -= _sqrt;
                }

                //E = cache.get((int)_x, (int)_y);

                //th = atan2(_y,_x);
                //double v = (_x) * cos(-th) - (_y) * sin(-th);
                double v = (_x == 0) ? abs(_y) : sqrt(_x * _x + _y * _y);

                if (_y < 0) v *= -1;// else if (_x>0) v *= -1;

                //th = atan2(_y,_x);
                //if (th<=0) v *= -1;

                //th = atan2(_y,_x);

                if (_x<0) __x=0;
                if (_x>0) __x = _sqrt;

                pathApply(v, _x, d, i, __x);
            }


        } else {
            double x1 = pe->A.x;
            double y1 = pe->A.y;

            double xx = x - x1;
            double yy = y - y1;

            double v = (pe->r - sqrt(xx * xx + yy * yy)) * (pe->invert ? -1 : 1);

            double _x = 0.0;

            pathApply(v, _x, d, i, 0);

            /*if (abs(abs(v) - abs(d->mv)) < .00001) {
                if (abs(_x) < abs(d->x)) {
                    d->mv = v;
                    d->i = i;
                    d->x = _x;
                }
            } else*/


        }

    }

    I = d->i;
    X = d->_x;

}

#undef pathApply

void PathAdapter::BoundingBox(dPnt2D &topLeft, dPnt2D &bottomRight)
{
    topLeft.x = topLeft.y = INFINITY;
    bottomRight.x = bottomRight.y = - INFINITY;


    for (int i=0; i<pathIndex; i++) {

        dPathEntry *pe = path + i;

        if (!pe->point) {

            double x1 = pe->A.x;
            double y1 = pe->A.y;

            double x2 = pe->B.x;
            double y2 = pe->B.y;

            if (x1<topLeft.x) topLeft.x = x1;
            if (x1>bottomRight.x) bottomRight.x = x1;

            if (y1<topLeft.y) topLeft.y = y1;
            if (y1>bottomRight.y) bottomRight.y = y1;


            if (x2<topLeft.x) topLeft.x = x2;
            if (x2>bottomRight.x) bottomRight.x = x2;

            if (y2<topLeft.y) topLeft.y = y2;
            if (y2>bottomRight.y) bottomRight.y = y2;



        } else {
            double x1 = pe->A.x - pe->r;
            double y1 = pe->A.y - pe->r;

            double x2 = pe->A.x + pe->r;
            double y2 = pe->A.y + pe->r;

            if (x1<topLeft.x) topLeft.x = x1;
            if (x1>bottomRight.x) bottomRight.x = x1;

            if (y1<topLeft.y) topLeft.y = y1;
            if (y1>bottomRight.y) bottomRight.y = y1;


            if (x2<topLeft.x) topLeft.x = x2;
            if (x2>bottomRight.x) bottomRight.x = x2;

            if (y2<topLeft.y) topLeft.y = y2;
            if (y2>bottomRight.y) bottomRight.y = y2;
        }

    }
}
