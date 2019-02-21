//
// Created by jwc on 2/14/19.
//

extern "C"
{
#include <Threading/Sync.h>
}
#include "Image.h"

struct DrawImage_Params
{
    Image *dst;
    int dx;
    int dy;
    int dw;
    int dh;
    PixOp pixOp;
    ZOp zOp;
    Image *src;
    int sx;
    int sy;
    int sw;
    int sh;
};


void DrawImageProc(GfxThreadWorker *worker,
        Image *dst,int dx,int dy,int dw,int dh,
        PixOp pixOp,ZOp zOp,
        Image *src,int sx,int sy,int sw,int sh)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=(sy+sh*worker->index)/worker->of;
        int yerr=(sy+sh*worker->index)%worker->of;
        int yy_plus=sh/dh;
        int ye_plus=sh%dh;

        int* cols;
        cols=new int[dw];
        int xx=0;
        int ox=0;
        int xerr=0;
        int xe=xerr;
        int xx_plus = sw / dw;
        int xe_plus=sw % dw;

        float zv;
        ARGB sp;

        for (int x=0;x<dw;x=x+1)
        {
            cols[x]=xx + sx;
            xx+=xx_plus;
            xe=xe+xe_plus;
            if (xe>=dw)
            {
                xx=xx+1;
                xe=xe-dw;
            }

        }

        int s = lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            {

                {
                    sp= src->pix[s][cols[0]];
                    zv = src->z[s][cols[0]];
                }

            }

            for (int x=0;x<dw;x=x+1)
            {
                if (pixOp == PixOp_SRC) {
                    dst->pix[y][dx+x]=sp;
                } else if (pixOp == PixOp_SRC_ALPHA) {
                    ARGB dest = dst->pix[y][dx+x];
                    dest.r = valValAlpha(dest.r, sp.r, sp.a);
                    dest.g = valValAlpha(dest.g, sp.g, sp.a);
                    dest.b = valValAlpha(dest.b, sp.b, sp.a);
                    dest.a = valValAlpha(dest.a, sp.a, sp.a);
                    dst->pix[y][dx+x] = dest;
                }

                if (zOp == ZOp_SRC)
                {
                    dst->z[y][dx+x] = zv;
                } else if (zOp == ZOp_SRC_ADD)
                {
                    dst->z[y][dx+x] += zv;
                }



                xx=cols[x];


                if (xx!=ox)
                {
                    {

                        {
                            sp=src->pix[s][xx];
                            zv = src->z[s][xx];
                        }

                    }

                    ox=xx;
                }

            }


            yerr=yerr+ye_plus;
            s=s+yy_plus;
            if (yerr>=dh)
            {
                s++;
                yerr=yerr-dh;
            }
        }

        delete []cols;

    }







/*
    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++) {
            if (pixOp == PixOp_SRC) {
                image->pix[y][x] = p;
            } else if (pixOp == PixOp_SRC_ALPHA) {
                ARGB dest = image->pix[y][x];
                dest.r = valValAlpha(dest.r, p.r, p.a);
                dest.g = valValAlpha(dest.g, p.g, p.a);
                dest.b = valValAlpha(dest.b, p.b, p.a);
                dest.a = valValAlpha(dest.a, p.a, p.a);
                image->pix[y][x] = dest;
            }

            if (zOp == ZOp_SRC)
            {
                image->z[y][x] = z;
            } else if (zOp == ZOp_SRC_ADD)
            {
                image->z[y][x] += z;
            }
        }
    }
*/
}

void *DrawImageSlice(GfxThreadWorker *w)
{
    DrawImage_Params *p = (DrawImage_Params *)w->p[17];
    DrawImageProc(w, p->dst, p->dx,p->dy, p->dw, p->dh, p->pixOp, p->zOp,
                  p->src, p->sx,p->sy, p->sw, p->sh);
    return nullptr;
}

void Image::DrawImage(int dx,int dy, int dw, int dh, PixOp pixOp, ZOp zOp,
               Image *src, int sx,int sy, int sw, int sh)
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    DrawImage_Params params;

    params.dst = this;
    params.dx = dx;
    params.dy = dy;
    params.dw = dw;
    params.dh = dh;
    params.pixOp = pixOp;
    params.zOp = zOp;
    params.src = src;
    params.sx = sx;
    params.sy = sy;
    params.sw = sw;
    params.sh= sh;
    GfxWorker_ProcType func;

    func = DrawImageSlice;

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = func;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);


}