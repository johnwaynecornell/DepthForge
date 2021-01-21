//
// Created by jwc on 3/5/19.
//

#include <cmath>
#include "Geometry.h"

double & dPnt2D::operator[](int idx)
{
    if (idx == 0) return x;
    if (idx == 1) return y;

    throw 3;
}

dPnt2D dPnt2D::operator-()
{
    return {-x,-y};
}

dPnt2D dPnt2D::operator-(dPnt2D other)
{
    return {x-other.x, y-other.y};
}

dPnt2D dPnt2D::operator+(dPnt2D other)
{
    return {x+other.x, y+other.y};
}


dPnt2D dPnt2D::operator*(dPnt2D other)
{
    return {x*other.x, y*other.y};
}

dPnt2D dPnt2D::operator/(dPnt2D other)
{
    return {x/other.x, y/other.y};
}


dPnt2D dPnt2D::operator*(double scaler)
{
    return {x*scaler, y*scaler};
}

dPnt2D dPnt2D::operator/(double scaler)
{
    return {x/scaler, y/scaler};
}


dPnt2D dPnt2D::sinCos(double Th)
{
    return { cos(Th),sin(Th)};
}

double dPnt2D::atan2()
{
    return ::atan2(y,x);
}

double dPnt2D::len()
{
    return sqrt(x*x+y*y);
}

dPnt2D dPnt2D::negate()
{
    return {-x,-y};
}
dPnt2D dPnt2D::invert()
{
    return {y,x};
}


dMatrix2D & dMatrix2D::Identity()
{
    val[0][0] = val[1][1] = val[2][2] = 1.0;
    val[0][1] = val[0][2] = 0.0;
    val[1][0] = val[1][2] = 0.0;
    val[2][0] = val[2][1] = 0.0;

    return *this;
}

dPnt2D dMatrix2D::operator *(dPnt2D G)
{
    dPnt2D Return;

    int r = 1;
    int n = 3;

    int c = 3;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double Val = 0.0;

            for (int k = 0; k < n; k++)
            {
                double q = k<2 ? G[k] : 1;

                Val = Val + q * val [k][ j];//(double) Add(Val, Multiply(G[k] , F[k,j]));
            }

            if (j<2) Return[j] = Val;
        }
    }

    return Return;
}

dMatrix2D& dMatrix2D::operator *=(dMatrix2D G)
{
    (*this) = (*this) * G;
    return *this;
}

dMatrix2D dMatrix2D::operator *(dMatrix2D G)
{
    dMatrix2D Return;

    int r = 3;
    int n = 3;

    int c = 3;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double Val = 0.0;

            for (int k = 0; k < n; k++)
            {
                Val = Val + val [i][k] * G.val [k][j];
            }

            Return.val[i][j] = Val;
        }
    }

    return Return;
}

dMatrix2D dMatrix2D::Translate(dPnt2D B)
{
    dMatrix2D R;

    R.Identity();

    R.val[2][0] = B.x;
    R.val[2][1] = B.y;

    return R;

}

dMatrix2D dMatrix2D::Rotate(double th)
{
    dMatrix2D R;

    R.Identity();

    double sn = sin(th);
    double cs = cos(th);

    R.val[0][0] = cs; R.val[0][1]=-sn;
    R.val[1][0] = sn; R.val[1][1] = cs;

    return R;
}

dMatrix2D dMatrix2D::Scale(dPnt2D B)
{
    dMatrix2D R;

    R.Identity();

    R.val[0][0] = B.x;
    R.val[1][1] = B.y;

    return R;
}
