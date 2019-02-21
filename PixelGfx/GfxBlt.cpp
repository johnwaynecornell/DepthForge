//
// Created by jwc on 1/28/19.
//

#include "GfxThreadWorker.h"

extern "C"
{
    #include "JWC_PixelGfx.h"
    #include "../Threading/Sync.h"
}

void *BltSlice(GfxThreadWorker *w)
{
    GfxBlt_Params *p = (GfxBlt_Params *)w->p[17];
    ((GfxBlt_Proc) w->p[16])(w, p->srcFormat, p->src, p->sx, p->sy, p->sw,p->sh, p->s_stride, p->dstFormat, p->dst, p->dx, p->dy, p->dw, p->dh, p->d_stride, p->flip, p->stretchX, p->stretchY);
    return nullptr;
}


void GfxBlt_0(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*RGBA::size);
            }

        }

    }

}
void GfxBlt_4(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_8(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_12(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_1(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_5(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*BGRA::size);
            }

        }

    }

}
void GfxBlt_9(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_13(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_2(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_6(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_10(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*ARGB::size);
            }

        }

    }

}
void GfxBlt_14(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_3(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_7(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_11(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_15(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*ABGR::size);
            }

        }

    }

}
void GfxBlt_192(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*RGBA::size);
            }

        }

    }

}
void GfxBlt_196(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_200(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_204(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_193(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_197(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*BGRA::size);
            }

        }

    }

}
void GfxBlt_201(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_205(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_194(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_198(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_202(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*ARGB::size);
            }

        }

    }

}
void GfxBlt_206(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_195(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_199(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_203(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_207(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*ABGR::size);
            }

        }

    }

}
void GfxBlt_96(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*RGBA::size);
            }

        }

    }

}
void GfxBlt_100(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_104(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_108(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_97(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_101(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*BGRA::size);
            }

        }

    }

}
void GfxBlt_105(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_109(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_98(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_102(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_106(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*ARGB::size);
            }

        }

    }

}
void GfxBlt_110(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_99(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_103(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_107(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_111(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*ABGR::size);
            }

        }

    }

}
void GfxBlt_288(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*RGBA::size);
            }

        }

    }

}
void GfxBlt_292(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_296(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_300(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        RGBA* s=(RGBA*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_289(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_293(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*BGRA::size);
            }

        }

    }

}
void GfxBlt_297(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_301(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        BGRA* s=(BGRA*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_290(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_294(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_298(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*ARGB::size);
            }

        }

    }

}
void GfxBlt_302(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ARGB* s=(ARGB*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_291(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        RGBA* d=(RGBA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_295(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        BGRA* d=(BGRA*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_299(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        ARGB* d=(ARGB*) dst+o;
        {
            {
                for (int x=0;x<(hy-ly)*d_stride;x=x+1)
                {
                    {

                        {
                            d[x].r=s[x].r;
                            d[x].g=s[x].g;
                            d[x].b=s[x].b;
                            d[x].a=s[x].a;
                        }

                    }

                }

            }

        }

    }

}
void GfxBlt_303(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int o=ly*d_stride;
        ABGR* s=(ABGR*) src+o;
        ABGR* d=(ABGR*) dst+o;
        {
            {
                memcpy(d, s, (hy-ly)*d_stride*ABGR::size);
            }

        }

    }

}
void GfxBlt_48(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_52(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_56(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_60(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_49(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_53(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_57(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_61(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_50(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_54(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_58(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_62(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_51(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_55(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_59(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_63(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_240(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_244(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_248(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_252(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_241(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_245(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_249(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_253(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_242(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_246(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_250(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_254(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_243(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_247(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_251(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_255(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_144(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_148(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_152(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_156(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_145(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_149(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_153(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_157(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_146(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_150(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_154(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_158(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_147(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_151(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_155(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_159(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_336(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_340(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_344(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_348(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_337(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_341(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_345(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_349(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_338(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_342(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_346(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_350(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_339(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_343(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_347(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_351(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_16(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_20(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_24(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_28(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_17(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_21(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_25(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_29(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_18(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_22(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_26(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_30(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_19(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_23(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_27(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_31(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_208(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_212(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_216(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_220(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_209(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_213(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_217(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_221(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_210(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_214(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_218(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_222(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_211(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_215(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_219(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_223(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_112(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_116(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_120(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_124(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_113(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_117(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_121(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_125(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_114(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_118(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_122(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_126(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_115(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_119(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_123(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_127(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_304(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_308(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_312(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_316(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_305(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_309(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_313(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_317(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_306(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_310(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_314(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_318(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_307(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_311(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_315(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_319(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_64(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_68(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_72(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_76(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_65(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_69(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_73(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_77(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_66(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_70(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_74(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_78(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_67(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_71(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_75(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_79(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_256(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_260(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_264(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_268(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_257(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_261(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_265(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_269(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_258(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_262(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_266(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_270(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_259(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_263(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_267(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_271(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_160(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_164(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_168(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_172(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_161(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_165(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_169(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_173(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_162(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_166(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_170(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_174(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_163(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_167(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_171(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_175(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_352(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*RGBA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_356(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_360(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_364(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        RGBA* s=(RGBA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_353(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_357(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*BGRA::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_361(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_365(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        BGRA* s=(BGRA*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_354(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_358(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_362(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ARGB::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_366(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ARGB* s=(ARGB*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_355(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_359(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_363(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    for (int x=0;x<dw;x=x+1)
                    {
                        {

                            {
                                d[x].r=s[x].r;
                                d[x].g=s[x].g;
                                d[x].b=s[x].b;
                                d[x].a=s[x].a;
                            }

                        }

                    }

                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_367(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;

        ABGR* s=(ABGR*) src+sx+s_stride*lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {
                {
                    memcpy(d, s, dw*ABGR::size);
                }

            }

            s=s+s_stride;
            d=d+d_stride;
        }


    }

}
void GfxBlt_32(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_36(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_40(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_44(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_33(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_37(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_41(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_45(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_34(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_38(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_42(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_46(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_35(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_39(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_43(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_47(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_224(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_228(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_232(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_236(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_225(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_229(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_233(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_237(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_226(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_230(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_234(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_238(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_227(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_231(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_235(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_239(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_128(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_132(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_136(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_140(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_129(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_133(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_137(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_141(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_130(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_134(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_138(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_142(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_131(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_135(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_139(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_143(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_320(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_324(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_328(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_332(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_321(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_325(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_329(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_333(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_322(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_326(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_330(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_334(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_323(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_327(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_331(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_335(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*ly;
        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_80(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_84(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_88(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_92(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_81(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_85(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_89(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_93(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_82(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_86(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_90(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_94(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_83(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_87(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_91(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_95(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_272(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_276(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_280(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_284(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_273(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_277(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_281(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_285(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_274(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_278(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_282(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_286(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_275(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_279(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_283(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_287(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xe_plus=sw;
        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_176(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_180(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_184(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_188(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        RGBA* os=nullptr;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_177(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_181(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_185(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_189(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        BGRA* os=nullptr;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_178(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_182(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_186(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_190(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        ARGB* os=nullptr;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_179(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        RGBA* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_183(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        BGRA* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_187(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ARGB* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp.r=s[0].r;
                        sp.g=s[0].g;
                        sp.b=s[0].b;
                        sp.a=s[0].a;
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp.r=s[xx].r;
                                sp.g=s[xx].g;
                                sp.b=s[xx].b;
                                sp.a=s[xx].a;
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_191(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int ye_plus=sh;
        ABGR* od=nullptr;
        ABGR* os=nullptr;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            if (os==s)
            {
                memcpy(d, od, dest_bytes);
            }
            else {
                {

                    {
                        sp=s[0];
                    }

                }

                for (int x=0;x<dw;x=x+1)
                {
                    d[x]=sp;
                    xx=cols[x];
                    if (xx!=ox)
                    {
                        {

                            {
                                sp=s[xx];
                            }

                        }

                        ox=xx;
                    }

                }

            }

            os=s;
            od=d;

            yerr=yerr+ye_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_368(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_372(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_376(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_380(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        RGBA* s=(RGBA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_369(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_373(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_377(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_381(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        BGRA* s=(BGRA*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_370(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_374(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_378(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_382(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ARGB* s=(ARGB*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_371(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        RGBA* d=(RGBA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*RGBA::size;
        RGBA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_375(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        BGRA* d=(BGRA*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*BGRA::size;
        BGRA sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_379(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ARGB* d=(ARGB*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ARGB::size;
        ARGB sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp.r=s[0].r;
                    sp.g=s[0].g;
                    sp.b=s[0].b;
                    sp.a=s[0].a;
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp.r=s[xx].r;
                            sp.g=s[xx].g;
                            sp.b=s[xx].b;
                            sp.a=s[xx].a;
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
void GfxBlt_383(GfxThreadWorker* worker, PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY)
{
    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        ABGR* d=(ABGR*) dst+dx+d_stride*(dy+dh-ly-1);
        d_stride=d_stride*-1;

        int lyy=sh*worker->index/worker->of;
        int yerr=sh*worker->index%worker->of;
        int yy_plus=sh/dh*s_stride;
        int ye_plus=sh%dh;


        ABGR* s=(ABGR*) src+sx+s_stride*lyy;
        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=-1;
        int xerr=0;
        int xe=xerr;
        int xx_plus=sw/dw;
        int xe_plus=sw%dw;

        int dest_bytes=dw*ABGR::size;
        ABGR sp;
        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx;
            xe=xe+xe_plus;
            {
                xx=xx+xx_plus;
            }

            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }


        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp=s[0];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                d[x]=sp;
                xx=cols[x];
                if (xx!=ox)
                {
                    {

                        {
                            sp=s[xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s=s+s_stride;
                yerr=yerr-dh;
            }


            d=d+d_stride;
        }


    }

}
GfxBlt_Proc GfxBlt_Selector(PixType srcFormat, void* src, int sx, int sy, int sw, int sh, int s_stride, PixType dstFormat, void* dst, int dx, int dy, int dw, int dh, int d_stride, bool flip, bool stretchX, bool stretchY, GfxBlt_Params* params)
{
    params->srcFormat=srcFormat;
    params->src=src;
    params->sx=sx;
    params->sy=sy;
    params->sw=sw;
    params->sh=sh;
    params->s_stride=s_stride;
    params->dstFormat=dstFormat;
    params->dst=dst;
    params->dx=dx;
    params->dy=dy;
    params->dw=dw;
    params->dh=dh;
    params->d_stride=d_stride;
    params->flip=flip;
    params->stretchX=stretchX;
    params->stretchY=stretchY;
    if (dh==sh&&dw==sw)
    {
        if (sx==0&&sy==0&&dx==0&&dy==0&&s_stride==d_stride&&s_stride==sw)
        {
            if (flip==false)
            {
                if (stretchX==true)
                {
                    if (stretchY==true)
                    {
                        if (srcFormat==PixType_RGBA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_0;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_4;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_8;
                                    }
                                    else {
                                        return GfxBlt_12;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_BGRA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_1;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_5;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_9;
                                        }
                                        else {
                                            return GfxBlt_13;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ARGB)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_2;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_6;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_10;
                                            }
                                            else {
                                                return GfxBlt_14;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ABGR)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_3;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_7;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_11;
                                                }
                                                else {
                                                    return GfxBlt_15;
                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }
                    else {
                        if (stretchY==false)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_192;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_196;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_200;
                                        }
                                        else {
                                            return GfxBlt_204;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_193;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_197;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_201;
                                            }
                                            else {
                                                return GfxBlt_205;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_194;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_198;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_202;
                                                }
                                                else {
                                                    return GfxBlt_206;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_195;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_199;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_203;
                                                    }
                                                    else {
                                                        return GfxBlt_207;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }
                else {
                    if (stretchX==false)
                    {
                        if (stretchY==true)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_96;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_100;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_104;
                                        }
                                        else {
                                            return GfxBlt_108;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_97;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_101;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_105;
                                            }
                                            else {
                                                return GfxBlt_109;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_98;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_102;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_106;
                                                }
                                                else {
                                                    return GfxBlt_110;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_99;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_103;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_107;
                                                    }
                                                    else {
                                                        return GfxBlt_111;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }
                        else {
                            if (stretchY==false)
                            {
                                if (srcFormat==PixType_RGBA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_288;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_292;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_296;
                                            }
                                            else {
                                                return GfxBlt_300;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_BGRA)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_289;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_293;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_297;
                                                }
                                                else {
                                                    return GfxBlt_301;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ARGB)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_290;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_294;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_298;
                                                    }
                                                    else {
                                                        return GfxBlt_302;
                                                    }

                                                }

                                            }

                                        }
                                        else {
                                            if (srcFormat==PixType_ABGR)
                                            {
                                                if (dstFormat==PixType_RGBA)
                                                {
                                                    return GfxBlt_291;
                                                }
                                                else {
                                                    if (dstFormat==PixType_BGRA)
                                                    {
                                                        return GfxBlt_295;
                                                    }
                                                    else {
                                                        if (dstFormat==PixType_ARGB)
                                                        {
                                                            return GfxBlt_299;
                                                        }
                                                        else {
                                                            return GfxBlt_303;
                                                        }

                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }
            else {
                if (stretchX==true)
                {
                    if (stretchY==true)
                    {
                        if (srcFormat==PixType_RGBA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_48;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_52;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_56;
                                    }
                                    else {
                                        return GfxBlt_60;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_BGRA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_49;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_53;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_57;
                                        }
                                        else {
                                            return GfxBlt_61;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ARGB)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_50;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_54;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_58;
                                            }
                                            else {
                                                return GfxBlt_62;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ABGR)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_51;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_55;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_59;
                                                }
                                                else {
                                                    return GfxBlt_63;
                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }
                    else {
                        if (stretchY==false)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_240;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_244;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_248;
                                        }
                                        else {
                                            return GfxBlt_252;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_241;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_245;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_249;
                                            }
                                            else {
                                                return GfxBlt_253;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_242;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_246;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_250;
                                                }
                                                else {
                                                    return GfxBlt_254;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_243;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_247;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_251;
                                                    }
                                                    else {
                                                        return GfxBlt_255;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }
                else {
                    if (stretchX==false)
                    {
                        if (stretchY==true)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_144;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_148;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_152;
                                        }
                                        else {
                                            return GfxBlt_156;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_145;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_149;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_153;
                                            }
                                            else {
                                                return GfxBlt_157;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_146;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_150;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_154;
                                                }
                                                else {
                                                    return GfxBlt_158;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_147;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_151;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_155;
                                                    }
                                                    else {
                                                        return GfxBlt_159;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }
                        else {
                            if (stretchY==false)
                            {
                                if (srcFormat==PixType_RGBA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_336;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_340;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_344;
                                            }
                                            else {
                                                return GfxBlt_348;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_BGRA)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_337;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_341;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_345;
                                                }
                                                else {
                                                    return GfxBlt_349;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ARGB)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_338;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_342;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_346;
                                                    }
                                                    else {
                                                        return GfxBlt_350;
                                                    }

                                                }

                                            }

                                        }
                                        else {
                                            if (srcFormat==PixType_ABGR)
                                            {
                                                if (dstFormat==PixType_RGBA)
                                                {
                                                    return GfxBlt_339;
                                                }
                                                else {
                                                    if (dstFormat==PixType_BGRA)
                                                    {
                                                        return GfxBlt_343;
                                                    }
                                                    else {
                                                        if (dstFormat==PixType_ARGB)
                                                        {
                                                            return GfxBlt_347;
                                                        }
                                                        else {
                                                            return GfxBlt_351;
                                                        }

                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }
        else {
            if (flip==false)
            {
                if (stretchX==true)
                {
                    if (stretchY==true)
                    {
                        if (srcFormat==PixType_RGBA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_16;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_20;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_24;
                                    }
                                    else {
                                        return GfxBlt_28;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_BGRA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_17;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_21;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_25;
                                        }
                                        else {
                                            return GfxBlt_29;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ARGB)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_18;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_22;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_26;
                                            }
                                            else {
                                                return GfxBlt_30;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ABGR)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_19;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_23;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_27;
                                                }
                                                else {
                                                    return GfxBlt_31;
                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }
                    else {
                        if (stretchY==false)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_208;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_212;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_216;
                                        }
                                        else {
                                            return GfxBlt_220;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_209;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_213;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_217;
                                            }
                                            else {
                                                return GfxBlt_221;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_210;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_214;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_218;
                                                }
                                                else {
                                                    return GfxBlt_222;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_211;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_215;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_219;
                                                    }
                                                    else {
                                                        return GfxBlt_223;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }
                else {
                    if (stretchX==false)
                    {
                        if (stretchY==true)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_112;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_116;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_120;
                                        }
                                        else {
                                            return GfxBlt_124;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_113;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_117;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_121;
                                            }
                                            else {
                                                return GfxBlt_125;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_114;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_118;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_122;
                                                }
                                                else {
                                                    return GfxBlt_126;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_115;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_119;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_123;
                                                    }
                                                    else {
                                                        return GfxBlt_127;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }
                        else {
                            if (stretchY==false)
                            {
                                if (srcFormat==PixType_RGBA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_304;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_308;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_312;
                                            }
                                            else {
                                                return GfxBlt_316;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_BGRA)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_305;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_309;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_313;
                                                }
                                                else {
                                                    return GfxBlt_317;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ARGB)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_306;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_310;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_314;
                                                    }
                                                    else {
                                                        return GfxBlt_318;
                                                    }

                                                }

                                            }

                                        }
                                        else {
                                            if (srcFormat==PixType_ABGR)
                                            {
                                                if (dstFormat==PixType_RGBA)
                                                {
                                                    return GfxBlt_307;
                                                }
                                                else {
                                                    if (dstFormat==PixType_BGRA)
                                                    {
                                                        return GfxBlt_311;
                                                    }
                                                    else {
                                                        if (dstFormat==PixType_ARGB)
                                                        {
                                                            return GfxBlt_315;
                                                        }
                                                        else {
                                                            return GfxBlt_319;
                                                        }

                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }
            else {
                if (stretchX==true)
                {
                    if (stretchY==true)
                    {
                        if (srcFormat==PixType_RGBA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_64;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_68;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_72;
                                    }
                                    else {
                                        return GfxBlt_76;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_BGRA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_65;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_69;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_73;
                                        }
                                        else {
                                            return GfxBlt_77;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ARGB)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_66;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_70;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_74;
                                            }
                                            else {
                                                return GfxBlt_78;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ABGR)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_67;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_71;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_75;
                                                }
                                                else {
                                                    return GfxBlt_79;
                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }
                    else {
                        if (stretchY==false)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_256;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_260;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_264;
                                        }
                                        else {
                                            return GfxBlt_268;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_257;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_261;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_265;
                                            }
                                            else {
                                                return GfxBlt_269;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_258;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_262;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_266;
                                                }
                                                else {
                                                    return GfxBlt_270;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_259;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_263;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_267;
                                                    }
                                                    else {
                                                        return GfxBlt_271;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }
                else {
                    if (stretchX==false)
                    {
                        if (stretchY==true)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_160;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_164;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_168;
                                        }
                                        else {
                                            return GfxBlt_172;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_161;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_165;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_169;
                                            }
                                            else {
                                                return GfxBlt_173;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_162;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_166;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_170;
                                                }
                                                else {
                                                    return GfxBlt_174;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_163;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_167;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_171;
                                                    }
                                                    else {
                                                        return GfxBlt_175;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }
                        else {
                            if (stretchY==false)
                            {
                                if (srcFormat==PixType_RGBA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_352;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_356;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_360;
                                            }
                                            else {
                                                return GfxBlt_364;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_BGRA)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_353;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_357;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_361;
                                                }
                                                else {
                                                    return GfxBlt_365;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ARGB)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_354;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_358;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_362;
                                                    }
                                                    else {
                                                        return GfxBlt_366;
                                                    }

                                                }

                                            }

                                        }
                                        else {
                                            if (srcFormat==PixType_ABGR)
                                            {
                                                if (dstFormat==PixType_RGBA)
                                                {
                                                    return GfxBlt_355;
                                                }
                                                else {
                                                    if (dstFormat==PixType_BGRA)
                                                    {
                                                        return GfxBlt_359;
                                                    }
                                                    else {
                                                        if (dstFormat==PixType_ARGB)
                                                        {
                                                            return GfxBlt_363;
                                                        }
                                                        else {
                                                            return GfxBlt_367;
                                                        }

                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }
    else {
        if (flip==false)
        {
            if (stretchX==true)
            {
                if (stretchY==true)
                {
                    if (srcFormat==PixType_RGBA)
                    {
                        if (dstFormat==PixType_RGBA)
                        {
                            return GfxBlt_32;
                        }
                        else {
                            if (dstFormat==PixType_BGRA)
                            {
                                return GfxBlt_36;
                            }
                            else {
                                if (dstFormat==PixType_ARGB)
                                {
                                    return GfxBlt_40;
                                }
                                else {
                                    return GfxBlt_44;
                                }

                            }

                        }

                    }
                    else {
                        if (srcFormat==PixType_BGRA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_33;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_37;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_41;
                                    }
                                    else {
                                        return GfxBlt_45;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_ARGB)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_34;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_38;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_42;
                                        }
                                        else {
                                            return GfxBlt_46;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ABGR)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_35;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_39;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_43;
                                            }
                                            else {
                                                return GfxBlt_47;
                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }
                else {
                    if (stretchY==false)
                    {
                        if (srcFormat==PixType_RGBA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_224;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_228;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_232;
                                    }
                                    else {
                                        return GfxBlt_236;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_BGRA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_225;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_229;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_233;
                                        }
                                        else {
                                            return GfxBlt_237;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ARGB)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_226;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_230;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_234;
                                            }
                                            else {
                                                return GfxBlt_238;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ABGR)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_227;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_231;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_235;
                                                }
                                                else {
                                                    return GfxBlt_239;
                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }
            else {
                if (stretchX==false)
                {
                    if (stretchY==true)
                    {
                        if (srcFormat==PixType_RGBA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_128;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_132;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_136;
                                    }
                                    else {
                                        return GfxBlt_140;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_BGRA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_129;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_133;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_137;
                                        }
                                        else {
                                            return GfxBlt_141;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ARGB)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_130;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_134;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_138;
                                            }
                                            else {
                                                return GfxBlt_142;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ABGR)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_131;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_135;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_139;
                                                }
                                                else {
                                                    return GfxBlt_143;
                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }
                    else {
                        if (stretchY==false)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_320;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_324;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_328;
                                        }
                                        else {
                                            return GfxBlt_332;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_321;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_325;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_329;
                                            }
                                            else {
                                                return GfxBlt_333;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_322;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_326;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_330;
                                                }
                                                else {
                                                    return GfxBlt_334;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_323;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_327;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_331;
                                                    }
                                                    else {
                                                        return GfxBlt_335;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }
        else {
            if (stretchX==true)
            {
                if (stretchY==true)
                {
                    if (srcFormat==PixType_RGBA)
                    {
                        if (dstFormat==PixType_RGBA)
                        {
                            return GfxBlt_80;
                        }
                        else {
                            if (dstFormat==PixType_BGRA)
                            {
                                return GfxBlt_84;
                            }
                            else {
                                if (dstFormat==PixType_ARGB)
                                {
                                    return GfxBlt_88;
                                }
                                else {
                                    return GfxBlt_92;
                                }

                            }

                        }

                    }
                    else {
                        if (srcFormat==PixType_BGRA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_81;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_85;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_89;
                                    }
                                    else {
                                        return GfxBlt_93;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_ARGB)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_82;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_86;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_90;
                                        }
                                        else {
                                            return GfxBlt_94;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ABGR)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_83;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_87;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_91;
                                            }
                                            else {
                                                return GfxBlt_95;
                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }
                else {
                    if (stretchY==false)
                    {
                        if (srcFormat==PixType_RGBA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_272;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_276;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_280;
                                    }
                                    else {
                                        return GfxBlt_284;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_BGRA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_273;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_277;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_281;
                                        }
                                        else {
                                            return GfxBlt_285;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ARGB)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_274;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_278;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_282;
                                            }
                                            else {
                                                return GfxBlt_286;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ABGR)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_275;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_279;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_283;
                                                }
                                                else {
                                                    return GfxBlt_287;
                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }
            else {
                if (stretchX==false)
                {
                    if (stretchY==true)
                    {
                        if (srcFormat==PixType_RGBA)
                        {
                            if (dstFormat==PixType_RGBA)
                            {
                                return GfxBlt_176;
                            }
                            else {
                                if (dstFormat==PixType_BGRA)
                                {
                                    return GfxBlt_180;
                                }
                                else {
                                    if (dstFormat==PixType_ARGB)
                                    {
                                        return GfxBlt_184;
                                    }
                                    else {
                                        return GfxBlt_188;
                                    }

                                }

                            }

                        }
                        else {
                            if (srcFormat==PixType_BGRA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_177;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_181;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_185;
                                        }
                                        else {
                                            return GfxBlt_189;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_ARGB)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_178;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_182;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_186;
                                            }
                                            else {
                                                return GfxBlt_190;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ABGR)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_179;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_183;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_187;
                                                }
                                                else {
                                                    return GfxBlt_191;
                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }
                    else {
                        if (stretchY==false)
                        {
                            if (srcFormat==PixType_RGBA)
                            {
                                if (dstFormat==PixType_RGBA)
                                {
                                    return GfxBlt_368;
                                }
                                else {
                                    if (dstFormat==PixType_BGRA)
                                    {
                                        return GfxBlt_372;
                                    }
                                    else {
                                        if (dstFormat==PixType_ARGB)
                                        {
                                            return GfxBlt_376;
                                        }
                                        else {
                                            return GfxBlt_380;
                                        }

                                    }

                                }

                            }
                            else {
                                if (srcFormat==PixType_BGRA)
                                {
                                    if (dstFormat==PixType_RGBA)
                                    {
                                        return GfxBlt_369;
                                    }
                                    else {
                                        if (dstFormat==PixType_BGRA)
                                        {
                                            return GfxBlt_373;
                                        }
                                        else {
                                            if (dstFormat==PixType_ARGB)
                                            {
                                                return GfxBlt_377;
                                            }
                                            else {
                                                return GfxBlt_381;
                                            }

                                        }

                                    }

                                }
                                else {
                                    if (srcFormat==PixType_ARGB)
                                    {
                                        if (dstFormat==PixType_RGBA)
                                        {
                                            return GfxBlt_370;
                                        }
                                        else {
                                            if (dstFormat==PixType_BGRA)
                                            {
                                                return GfxBlt_374;
                                            }
                                            else {
                                                if (dstFormat==PixType_ARGB)
                                                {
                                                    return GfxBlt_378;
                                                }
                                                else {
                                                    return GfxBlt_382;
                                                }

                                            }

                                        }

                                    }
                                    else {
                                        if (srcFormat==PixType_ABGR)
                                        {
                                            if (dstFormat==PixType_RGBA)
                                            {
                                                return GfxBlt_371;
                                            }
                                            else {
                                                if (dstFormat==PixType_BGRA)
                                                {
                                                    return GfxBlt_375;
                                                }
                                                else {
                                                    if (dstFormat==PixType_ARGB)
                                                    {
                                                        return GfxBlt_379;
                                                    }
                                                    else {
                                                        return GfxBlt_383;
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    return nullptr;
}

void GfxBlt(PixType srcFormat, void *src, int sx,int sy, int sw, int sh, int s_stride, PixType  dstFormat, void *dst, int dx, int dy, int dw, int dh, int d_stride) {
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    GfxBlt_Params params;

    bool flip = dh<0;
    if (flip) dh *= -1;

    bool stretchX = dw > sw;
    bool stretchY = dh > sh;

    GfxBlt_Proc proc = GfxBlt_Selector(srcFormat, src, sx, sy, sw, sh, s_stride, dstFormat, dst,dx,dy,dw,dh,d_stride, flip, stretchX, stretchY, &params);

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[16] = (void *) proc;
        w->p[17] = &params;

        w->WorkerProc = BltSlice;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);
}
