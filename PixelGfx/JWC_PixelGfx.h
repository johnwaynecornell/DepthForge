#ifndef JWC_PIXELGFX_LIBRARY_H
#define JWC_PIXELGFX_LIBRARY_H

#include "GfxThreadWorker.h"

enum PixType
{
    PixType_RGBA, PixType_BGRA, PixType_ARGB, PixType_ABGR,

    PixType_High = 256
};

struct ABGR
{
    unsigned char a;
    unsigned char b;
    unsigned char g;
    unsigned char r;

    static const PixType pixType = PixType_RGBA;
    static const int size=4;
};

struct ARGB
{
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    static const PixType pixType = PixType_ARGB;
    static const int size=4;

    ARGB interpolate(ARGB B, unsigned char v);
};

struct RGBA
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    static const PixType pixType = PixType_RGBA;
    static const int size=4;
};

struct BGRA
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;

    static const PixType pixType = PixType_BGRA;
    static const int size=4;
};

extern float *rgb_v;
extern unsigned char* ValValAlpha_Mix;

#define valValAlpha(V1,V2,A) ValValAlpha_Mix[(A<<16)+(V1<<8)+V2]
#define Rgb_v(r,g,b) rgb_v[(r<<16)+(g<<8)+b]

struct PixTypeInfo
{
    PixType pixType;
    int size;
};

extern PixTypeInfo pixInfo[];

struct GfxRect
{
    int x;
    int y;
    int w;
    int h;
};

typedef void *(*GfxWorker_ProcType)(GfxThreadWorker *w);

void GfxInitThreadWorkers(int count);
void GfxTerminate();

void Init_JWC_PixelGfx();
void GfxBlt(PixType srcFormat, void *src, int sx,int sy, int sw, int sh, int s_stride, PixType  dstFormat, void *dst, int dx, int dy, int dw, int dh, int d_stride);

struct GfxBlt_Params{
    PixType srcFormat;
    void* src;
    int sx;
    int sy;
    int sw;
    int sh;
    int s_stride;
    PixType dstFormat;
    void* dst;
    int dx;
    int dy;
    int dw;
    int dh;
    int d_stride;
    bool flip;
    bool stretchX;
    bool stretchY;
}
;
typedef void (*GfxBlt_Proc)(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY);
GfxBlt_Proc GfxBlt_Selector(PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY, GfxBlt_Params* params);

//void GfxBlt(PixType srcFormat, void *src, int sx,int sy, int sw, int sh, int s_stride, PixType  dstFormat, void *dst, int dx, int dy, int dw, int dh, int d_stride);
void GfxBltFit(PixType srcFormat, void *src, int sx,int sy, int sw, int sh, int s_stride, PixType  dstFormat, void *dst, int dx, int dy, int dw, int dh, int d_stride);
void GfxBarrier();

void GfxFitRect(int toFitX, int toFitY, int toFitW, int toFitH, int *x, int *y, int *w, int *h);

#endif