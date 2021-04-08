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

class ImageMask
{
public:

    unsigned char *imageMemory;
    unsigned char **pix;

    int stride;

    int Width;
    int Height;

    ImageMask(int Width, int Height);
    virtual ~ImageMask();

    void Line(int xA,int yA, int xB, int yB, unsigned char pA, unsigned char pB);
    void FloodFill(int x, int y);

    bool Bound(int x, int y)
    {
        if (x<0||x>=Width) return false;
        if (y<0||y>=Height) return false;

        return true;
    }
};

struct PathEntry
{
    int x1;
    int y1;
    int x2;
    int y2;
    int r;

    bool point;
    bool invert;

};

struct pdata
{
    int i;
    double mv;
    int x;
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

    int pathLastX;
    int pathLastY;

    int pathMax;
    int pathIndex;
    PathEntry *path;

    int _preservePath;

    bool needUpdate;

    void PreservePath();
    void ClearPath();

    void MoveTo(int x1, int y1);
    void Circle(int r, bool Invert);
    void Circle(int x, int y, int r, bool Invert);
    void LineTo(int x2, int y2);
    void Line(int x1, int y1, int x2, int y2);


    Image(int Width, int Height);
    virtual ~Image();

    int boundX,boundY,boundW,boundH;

    bool Bound(int x, int y)
    {
        if (x<boundX||x>=boundX+boundW) return false;
        if (y<boundY||y>=boundY+boundH) return false;

        return true;
    }

    void setBound(int boundX, int boundY, int boundW, int boundH);
    void resetBound();

    //void FillPath(int x, int y, PixOp pixOp, ARGB p, ZOp zOp, float z);
    pdata* ComputePath(void);

    void DrawPath(PixOp pixOp, ARGB p, ZOp zOp, float z);
    void DrawPath(PixOp pixOp, ZOp zOp, double yScale,
            bool (*pixFunc)(int index, double y, ARGB &p, float &z, void *arg), void *arg);
    void DrawPath(PixOp pixOp, ZOp zOp, double yScale,
                  double *min, double *max,
                  bool (*pixFunc)(int index, double y, ARGB &p, float &z, void *arg), void *arg);


    void DrawPathOutline(PixOp pixOp, ZOp zOp,
            bool (*func)(int I, double X, int x, int xD, ARGB &P, float &Z, void *arg), void *arg);

    int Line(int xA,int yA, int xB, int yB, PixOp pixOp, ZOp zOp,
            bool (*pixFunc)(int x, int y, int v, int Vd, ARGB &p, float &z, void *arg), void *arg);

    void Line(int xA,int yA, int xB, int yB, PixOp pixOp, ARGB pA, ARGB pB, ZOp zOp, float zA, float zB);
    void FillRect(int x,int y, int w, int h, PixOp pixOp, ARGB p, ZOp zOp, float z);
    void DrawImage(int dx,int dy, int dw, int dh, PixOp pixOp, ZOp zOp,
                   Image *src, int sx,int sy, int sw, int sh);

    void DrawImage(int boundX, int boundY, int boundW, int boundH, int dx,int dy, int dw, int dh,
                    PixOp pixOp, ZOp zOp,
                    Image *src, int sx,int sy, int sw, int sh);

    void Tile(int dx,int dy, int dw, int dh,
              PixOp pixOp, ZOp zOp, Image *src, int sxo, int syo, int sx, int sy, int sw, int sh);

    void CalcZ();

    void InferDepth(float scale=1.0f, float offset = 0.0f, float filter=0.0f);
    void Artif3d(int sep, Image *left, Image *right);
    void AnaglyphFrom(Image *L, Image *R);

};


#endif //DEPTHFORGE_IMAGE_H
