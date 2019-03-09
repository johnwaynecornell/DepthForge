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

typedef void (*procDrawImage)(GfxThreadWorker *worker,
                                           Image *dst,int dx,int dy,int dw,int dh,
                                           PixOp pixOp,ZOp zOp,
                                           Image *src,int sx,int sy,int sw,int sh);


void DrawImageProc(GfxThreadWorker *worker,
        Image *dst,int dx,int dy,int dw,int dh,
        PixOp pixOp,ZOp zOp,
        Image *src,int sx,int sy,int sw,int sh)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(sh*worker->index)/worker->of;
        int yerr=(sh*worker->index)%worker->of;
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

}

void BltImageProc(GfxThreadWorker *worker,
                   Image *dst,int dx,int dy,int dw,int dh,
                   PixOp pixOp,ZOp zOp,
                   Image *src,int sx,int sy, int dummy1, int dummy2)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(dh*worker->index)/worker->of;
        
        float zv;
        ARGB sp;

        int s = lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            ARGB *srcPix = src->pix[s];
            float *srcZ = src->z[s];

            int xx = sx;

            for (int x=0;x<dw;x=x+1)
            {
                sp= srcPix[xx];
                zv = srcZ[xx];

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

                xx++;
            }


            s++;
        }

    }

}

void DrawImageProc_PixOp_SRC_ZOp_SRC(GfxThreadWorker *worker,
                   Image *dst,int dx,int dy,int dw,int dh,
                   PixOp pixOp,ZOp zOp,
                   Image *src,int sx,int sy,int sw,int sh)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(sh*worker->index)/worker->of;
        int yerr=(sh*worker->index)%worker->of;
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
                dst->pix[y][dx+x]=sp;
                dst->z[y][dx+x] = zv;

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

}

void BltImageProc_PixOp_SRC_ZOp_SRC(GfxThreadWorker *worker,
                  Image *dst,int dx,int dy,int dw,int dh,
                  PixOp pixOp,ZOp zOp,
                  Image *src,int sx,int sy, int dummy1, int dummy2)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(dh*worker->index)/worker->of;

        float zv;
        ARGB sp;

        int s = lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            ARGB *srcPix = src->pix[s];
            float *srcZ = src->z[s];

            int xx = sx;

            for (int x=0;x<dw;x=x+1)
            {
                sp= srcPix[xx];
                zv = srcZ[xx];

                dst->pix[y][dx+x]=sp;
                dst->z[y][dx+x] = zv;

                xx++;
            }


            s++;
        }

    }

}


void DrawImageProc_PixOp_SRC_ZOp_SRC_ADD(GfxThreadWorker *worker,
                   Image *dst,int dx,int dy,int dw,int dh,
                   PixOp pixOp,ZOp zOp,
                   Image *src,int sx,int sy,int sw,int sh)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(sh*worker->index)/worker->of;
        int yerr=(sh*worker->index)%worker->of;
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
                dst->pix[y][dx+x]=sp;
                dst->z[y][dx+x] += zv;

                xx=cols[x];


                if (xx!=ox)
                {
                    {

                        {
                            sp=src->pix[s][xx];
                            zv += src->z[s][xx];
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
}

void BltImageProc_PixOp_SRC_ZOp_SRC_ADD(GfxThreadWorker *worker,
                  Image *dst,int dx,int dy,int dw,int dh,
                  PixOp pixOp,ZOp zOp,
                  Image *src,int sx,int sy, int dummy1, int dummy2)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(dh*worker->index)/worker->of;

        float zv;
        ARGB sp;

        int s = lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            ARGB *srcPix = src->pix[s];
            float *srcZ = src->z[s];

            int xx = sx;

            for (int x=0;x<dw;x=x+1)
            {
                sp= srcPix[xx];
                zv = srcZ[xx];

                dst->pix[y][dx+x]=sp;
                dst->z[y][dx+x] += zv;

                xx++;
            }


            s++;
        }

    }

}



void DrawImageProc_PixOp_SRC_ALPHA_ZOp_SRC(GfxThreadWorker *worker,
                   Image *dst,int dx,int dy,int dw,int dh,
                   PixOp pixOp,ZOp zOp,
                   Image *src,int sx,int sy,int sw,int sh)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(sh*worker->index)/worker->of;
        int yerr=(sh*worker->index)%worker->of;
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
                ARGB dest = dst->pix[y][dx+x];
                dest.r = valValAlpha(dest.r, sp.r, sp.a);
                dest.g = valValAlpha(dest.g, sp.g, sp.a);
                dest.b = valValAlpha(dest.b, sp.b, sp.a);
                dest.a = valValAlpha(dest.a, sp.a, sp.a);
                dst->pix[y][dx+x] = dest;
                dst->z[y][dx+x] = zv;


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

}

void BltImageProc_PixOp_SRC_ALPHA_ZOp_SRC(GfxThreadWorker *worker,
                  Image *dst,int dx,int dy,int dw,int dh,
                  PixOp pixOp,ZOp zOp,
                  Image *src,int sx,int sy, int dummy1, int dummy2)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(dh*worker->index)/worker->of;

        float zv;
        ARGB sp;

        int s = lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            ARGB *srcPix = src->pix[s];
            float *srcZ = src->z[s];

            int xx = sx;

            for (int x=0;x<dw;x=x+1)
            {
                sp= srcPix[xx];
                zv = srcZ[xx];

                ARGB dest = dst->pix[y][dx+x];
                dest.r = valValAlpha(dest.r, sp.r, sp.a);
                dest.g = valValAlpha(dest.g, sp.g, sp.a);
                dest.b = valValAlpha(dest.b, sp.b, sp.a);
                dest.a = valValAlpha(dest.a, sp.a, sp.a);
                dst->pix[y][dx+x] = dest;
                dst->z[y][dx+x] = zv;

                xx++;
            }


            s++;
        }

    }

}


void DrawImageProc_PixOp_SRC_ALPHA_ZOp_SRC_ADD(GfxThreadWorker *worker,
                   Image *dst,int dx,int dy,int dw,int dh,
                   PixOp pixOp,ZOp zOp,
                   Image *src,int sx,int sy,int sw,int sh)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(sh*worker->index)/worker->of;
        int yerr=(sh*worker->index)%worker->of;
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
                ARGB dest = dst->pix[y][dx+x];
                dest.r = valValAlpha(dest.r, sp.r, sp.a);
                dest.g = valValAlpha(dest.g, sp.g, sp.a);
                dest.b = valValAlpha(dest.b, sp.b, sp.a);
                dest.a = valValAlpha(dest.a, sp.a, sp.a);
                dst->pix[y][dx+x] = dest;

                dst->z[y][dx+x] += zv;



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

}

void BltImageProc_PixOp_SRC_ALPHA_ZOp_SRC_ADD(GfxThreadWorker *worker,
                  Image *dst,int dx,int dy,int dw,int dh,
                  PixOp pixOp,ZOp zOp,
                  Image *src,int sx,int sy, int dummy1, int dummy2)
{

    int ly=dy+dh*worker->index/worker->of;
    int hy=dy+dh*(worker->index+1)/worker->of;
    {
        int lyy=sy+(dh*worker->index)/worker->of;

        float zv;
        ARGB sp;

        int s = lyy;

        for (int y=ly;y<hy;y=y+1)
        {
            ARGB *srcPix = src->pix[s];
            float *srcZ = src->z[s];

            int xx = sx;

            for (int x=0;x<dw;x=x+1)
            {
                sp= srcPix[xx];
                zv = srcZ[xx];

                ARGB dest = dst->pix[y][dx+x];
                dest.r = valValAlpha(dest.r, sp.r, sp.a);
                dest.g = valValAlpha(dest.g, sp.g, sp.a);
                dest.b = valValAlpha(dest.b, sp.b, sp.a);
                dest.a = valValAlpha(dest.a, sp.a, sp.a);
                dst->pix[y][dx+x] = dest;
                dst->z[y][dx+x] += zv;

                xx++;
            }


            s++;
        }

    }

}

void *DrawImageSlice(GfxThreadWorker *w)
{
    DrawImage_Params *p = (DrawImage_Params *)w->p[17];
    procDrawImage fptr = (procDrawImage)w->p[18];
    fptr(w, p->dst, p->dx,p->dy, p->dw, p->dh, p->pixOp, p->zOp,
                  p->src, p->sx,p->sy, p->sw, p->sh);
    return nullptr;
}

void Image::DrawImage(int dx,int dy, int dw, int dh, PixOp pixOp, ZOp zOp,
               Image *src, int sx,int sy, int sw, int sh) {

    if (dw==0 || dh == 0 || sw == 0 || sh==0) return;

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
    params.sh = sh;
    GfxWorker_ProcType func;

    func = DrawImageSlice;

    procDrawImage fptr;

    if (sw == dw && sh == dh) {

        if (pixOp == PixOp_SRC) {
            if (zOp == ZOp_SRC) {
                fptr = BltImageProc_PixOp_SRC_ZOp_SRC;
            } else if (zOp == ZOp_SRC_ADD) {
                fptr = BltImageProc_PixOp_SRC_ZOp_SRC_ADD;
            } else fptr = BltImageProc;
        } else if (pixOp == PixOp_SRC_ALPHA) {
            if (zOp == ZOp_SRC) {
                fptr = BltImageProc_PixOp_SRC_ALPHA_ZOp_SRC;
            } else if (zOp == ZOp_SRC_ADD) {
                fptr = BltImageProc_PixOp_SRC_ALPHA_ZOp_SRC_ADD;
            } else fptr = BltImageProc;
        } else fptr = BltImageProc;
    } else {

        if (pixOp == PixOp_SRC) {
            if (zOp == ZOp_SRC) {
                fptr = DrawImageProc_PixOp_SRC_ZOp_SRC;
            } else if (zOp == ZOp_SRC_ADD) {
                fptr = DrawImageProc_PixOp_SRC_ZOp_SRC_ADD;
            } else fptr = DrawImageProc;
        } else if (pixOp == PixOp_SRC_ALPHA) {
            if (zOp == ZOp_SRC) {
                fptr = DrawImageProc_PixOp_SRC_ALPHA_ZOp_SRC;
            } else if (zOp == ZOp_SRC_ADD) {
                fptr = DrawImageProc_PixOp_SRC_ALPHA_ZOp_SRC_ADD;
            } else fptr = DrawImageProc;
        } else fptr = DrawImageProc;
    }

    //fptr = DrawImageProc;
    
    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;
        w->p[18] = (void *) fptr;

        w->WorkerProc = func;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);
}

void Image::DrawImage(int boundX, int boundY, int boundW, int boundH,
               int dx,int dy, int dw, int dh,
               PixOp pixOp, ZOp zOp,
               Image *src, int sx,int sy, int sw, int sh)
{
    if (dw==0 || dh == 0 || sw == 0 || sh==0) return;

    if (dy >= boundY +boundH) return;
    if (dy + dh <= boundY) return;

    if (dx >= boundX +boundW) return;
    if (dx + dw <= boundX) return;

    int x1;
    int y1;

    int ndx = dx;
    int ndy = dy;
    int ndw = dw;
    int ndh = dh;

    int nsx = sx;
    int nsy = sy;
    int nsw = sw;
    int nsh = sh;

    x1 = dx - boundX;
    y1 = dy - boundY;

    if (x1<0)
    {
        int adj = -x1;
        int sadj = adj * sw / dw;

        ndx+=adj;
        ndw-=adj;

        nsx+=sadj;
        nsw-=sadj;
    }

    if (y1<0)
    {
        int adj = -y1;
        int sadj = adj * sh / dh;

        ndy+=adj;
        ndh-=adj;

        nsy+=sadj;
        nsh-=sadj;
    }

    x1 = (dx+dw)-(boundX+boundW);
    y1 = (dy+dh)-(boundY+boundH);

    if (x1>=0)
    {
        int adj = x1;
        int sadj = adj * sw / dw;

        ndw-=adj;
        nsw-=sadj;
    }

    if (y1>0)
    {
        int adj = y1;
        int sadj = adj * sh / dh;

        ndh-=adj;
        nsh-=sadj;
    }

    DrawImage(ndx,ndy, ndw,ndh, pixOp, zOp, src, nsx,nsy,nsw,nsh);
}
