//
// Created by jwc on 2/8/19.
//

#ifndef DEPTHFORGE_IMAGE_H
#define DEPTHFORGE_IMAGE_H

extern "C"
{
    #include "../PixelGfx/JWC_PixelGfx.h"
}

enum PixOp
{
    PixOp_SRC_ALPHA,
    PixOp_SRC
};

enum ZOp
{
    ZOp_SRC_ADD,
    ZOp_SRC
};

struct ImgOp
{
    PixOp pixOp;
    ZOp zOp;
};

struct ARGBz : ARGB
{
    float z;

    ARGBz()
    {

    }


    ARGBz(int a, int r,int g, int b, float z)
    {
        this->a = a;
        this->r = r;
        this->g = g;
        this->b = b;
        this->z = z;
    }
};

class Image {
public:
    ARGB *imageMemory;
    ARGB **pix;

    float *zMemory;
    float **z;

    int stride;

    int xLowBound;
    int xHighBound;
    int yLowBound;
    int yHighBound;

    int Width;
    int Height;

    int pathMax;
    int pathIndex;
    int *pathX;
    int *pathY;

    int _preservePath;

    void PreservePath();

    void ClearPath();
    void PathAdd(int x, int y);


    Image(int Width, int Height);

    void FillPath(PixOp pixOp, ARGB p, ZOp zOp, float z);
    void DrawPath(PixOp pixOp, ARGB p, ZOp zOp, float z);


    void Line(int xA,int yA, int xB, int yB, PixOp pixOp, ARGB pA, ARGB pB, ZOp zOp, float zA, float zB);
    void FillRect(int x1,int y1, int x2, int y2, PixOp pixOp, ARGB p, ZOp zOp, float z);
    void DrawImage(int dx,int dy, int dw, int dh, PixOp pixOp, ZOp zOp,
                   Image *src, int sx,int sy, int sw, int sh);

    void CalcZ();

    void Artif3d(int sep, Image *left, Image *right);
    void AnaglyphFrom(Image *L, Image *R);

};


#endif //DEPTHFORGE_IMAGE_H
