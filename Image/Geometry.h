//
// Created by jwc on 3/5/19.
//

#ifndef DEPTHFORGE_GEOMETRY_H
#define DEPTHFORGE_GEOMETRY_H

struct iPnt2D {
    int x;
    int y;
};

struct dPnt2D
{
    double x;
    double y;

    double & operator[](int idx);
    dPnt2D operator-();

    dPnt2D operator-(dPnt2D other);
    dPnt2D operator+(dPnt2D other);

    dPnt2D operator*(dPnt2D other);
    dPnt2D operator/(dPnt2D other);

    dPnt2D operator*(double scaler);
    dPnt2D operator/(double scaler);

    static dPnt2D sinCos(double Th);
    double atan2();

    double len();

    dPnt2D negate();
    dPnt2D invert();

};

struct dMatrix2D
{
    double val[3][3];

    dMatrix2D & Identity();

    dMatrix2D& operator *=(dMatrix2D B);
    dMatrix2D operator *(dMatrix2D B);
    dPnt2D operator *(dPnt2D G);

    static dMatrix2D Translate(dPnt2D B);
    static dMatrix2D Rotate(double th);
    static dMatrix2D Scale(dPnt2D B);

};



#endif //DEPTHFORGE_GEOMETRY_H
