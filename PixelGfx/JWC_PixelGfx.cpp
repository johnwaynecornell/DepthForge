#include <climits>
#include <cstring>

extern "C"
{
    #include "JWC_PixelGfx.h"
    #include "../Threading/Sync.h"
}

#include <math.h>

PixTypeInfo pixInfo[] = {
        { PixType_RGBA, 4},
        { PixType_BGRA, 4},
        { PixType_ARGB, 4},
        { PixType_ABGR, 4},
        { PixType_High, 0},
};

float* rgb_v;
unsigned char* ValValAlpha_Mix;

ARGB ARGB::interpolate(ARGB B, unsigned char v)
{
    ARGB dest;
    dest.r = valValAlpha(r, B.r, v);
    dest.g = valValAlpha(g, B.g, v);
    dest.b = valValAlpha(b, B.b, v);
    dest.a = valValAlpha(a, B.a, v);

    return dest;
}


void Init_JWC_PixelGfx()
{
    ValValAlpha_Mix = new unsigned char[1<<24];
    rgb_v = new float[1<<24];

    float maxV = sqrtf(0xFF*0xFF*3);

    int zz,yy,xx;

    for (int z=0; z<0x100; z++) {

        zz = z * z;
        for (int y = 0; y < 0x100; y++) {
            yy = y * y;
            for (int x = 0; x< 0x100; x++) {
                xx = x * x;
                int o = (z<< 16) + (y<<8)+x;

                ValValAlpha_Mix[o] = (unsigned char) (y + (x-y) * z/ 0xFF);
                rgb_v[o] = sqrtf(zz+yy+xx) / maxV;
            }
        }
    }
}

void GfxBltFit(PixType srcFormat, void *src, int sx,int sy, int sw, int sh, int s_stride, PixType  dstFormat, void *dst, int dx, int dy, int dw, int dh, int d_stride)
{
    int neg = dh < 0 ? -1 : 1;
    dh *=neg;

    GfxFitRect(sx,sy,sw,sh, &dx,&dy,&dw,&dh);

    dh *= neg;
    GfxBlt(srcFormat, src, sx,sy, sw, sh, s_stride, dstFormat, dst, dx, dy, dw, dh, d_stride);
}

void GfxFitRect(int toFitX, int toFitY, int toFitW, int toFitH, int *x, int *y, int *w, int *h)
{
    double a1 = *w / (double) *h;
    double a2 = toFitW / (double) toFitH;

    int _w, _h, _x, _y;

    if (a2 <= a1)
    {
        _h = *h;
        _w = (int)(_h * a2);
    }
    else
    {
        _w = *w;
        _h = (int)(_w / a2);
    }

    _x = *x + (*w - _w) / 2;// - (toFit.X / toFit.Width * This.Width);
    _y = *y + (*h - _h) / 2;// - (toFit.Y / toFit.Height * This.Height);

    *x = _x;
    *y = _y;
    *w = _w;
    *h = _h;
}

void GfxBarrier()
{
    Barrier_wait(gfxThreadWorkerBarrier);
}

