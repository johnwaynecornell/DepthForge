//
// Created by jwc on 2/8/19.
//
extern "C"
{
    #include <Threading/Sync.h>
}

#include <QtGui/QtGui>
#include "Image.h"

Image::Image(int Width, int Height)
{
    this->Width = Width;
    this->Height = Height;

    this->stride = Width;

    this->xLowBound = this->yLowBound = 0;
    this->xHighBound = Width; this->yHighBound = Height;

    this->_preservePath = 0;
    this->pathIndex = 0;

    pathMax = 1024;
    pathX = new int[pathMax];
    pathY = new int[pathMax];

    imageMemory = new ARGB[Width * Height];

    memset(imageMemory, 0, Width*Height);

    pix = new ARGB *[Height];

    zMemory = new float[Width*Height];
    z = new float *[Height];

    memset(zMemory,0,sizeof(float)*Width*Height);

    ARGB *d = imageMemory;
    float *d2 = zMemory;

    for (int y=0; y<Height; y++)
    {
        pix[y] = d; d+=stride;
        z[y] = d2; d2+=stride;
    }
}

void Image::PreservePath()
{
    _preservePath++;
}

void Image::ClearPath()
{
    _preservePath = 0;
    pathIndex = 0;

}

void Image::PathAdd(int x, int y)
{
    Q_ASSERT(pathIndex < pathMax);

    pathX[pathIndex] = x;
    pathY[pathIndex] = y;

    pathIndex++;

}

void Image::FillPath(PixOp pixOp, ARGB p, ZOp zOp, float z)
{

    for (int y=0; y<Height; y++) {
        for (int x = 0; x < Width; x++) {

            int incount = 0;
            int outcount = 0;

            double oth;

            int inlines = 0;

            for (int i = 1; i < pathIndex; i++) {
                double x1 = pathX[i - 1];
                double y1 = pathY[i - 1];

                double x2 = pathX[i];
                double y2 = pathY[i];

                double th = atan2(y2 - y1, x2 - x1);

                double rth;

                if (i != 1)
                {
                    rth = oth - th;

                    if (rth > M_2_PI) rth -= M_2_PI;
                    else if (rth < -M_2_PI) rth += M_2_PI;

                } else rth = 0;

                oth = th;

                double xx = x - x1;
                double yy = y - y1;

                double sn = sin(-th);
                double cs = cos(-th);

                double _x = xx * cs - yy * sn;
                double _y = yy * cs + xx * sn;

                if (rth < 0) {
                    inlines++;

                    if ((_y >= 0)) {
                        incount++;
                    } else outcount++;
                } else if (rth > 0)
                {
                    if ((_y >= 0)) {
                        outcount--;
                    } else incount--;

                }

            }

            bool ok;

            ok = (incount > 0) && (incount > (outcount));
            if (ok) ok = incount > 0 && (((incount % 2) != (inlines % 2)));
            //ok = outcount > 0 && outcount > (incount);

            ok = (incount>0)&&(outcount>=0);

            int q = incount-outcount;

            ok = (q > 0) && ((incount%2) == 1);

            //ok=true;
            //ok = (incount %2) == (pathIndex%2);

            int v = incount;

//            ok = incount > 0;

//            if (ok) ok = (incount %2) != ((incount + outcount) %2);

            if (ok)
            {
                if (pixOp == PixOp_SRC) {
                    //pix[y][x] = p;

                    pix[y][x].r += p.r * v;
                    pix[y][x].g = 0x80;
                    pix[y][x].b += p.b * v;
                    pix[y][x].a = 0xFF;



                } else if (pixOp == PixOp_SRC_ALPHA) {
                    ARGB dest = pix[y][x];
                    dest.r = valValAlpha(dest.r, p.r, p.a);
                    dest.g = valValAlpha(dest.g, p.g, p.a);
                    dest.b = valValAlpha(dest.b, p.b, p.a);
                    dest.a = valValAlpha(dest.a, p.a, p.a);
                    pix[y][x] = dest;
                }

                if (zOp == ZOp_SRC) {
                    this->z[y][x] = z;
                } else if (zOp == ZOp_SRC_ADD) {
                    this->z[y][x] += z;
                }
            }
        }
    }

    bool clear = _preservePath == 0;

    if (_preservePath > 0) _preservePath--;
    if (clear) ClearPath();
}

void Image::DrawPath(PixOp pixOp, ARGB p, ZOp zOp, float z) {
    for (int i = 1; i < pathIndex; i++) {
        int x1 = pathX[i - 1];
        int y1 = pathY[i - 1];

        int x2 = pathX[i];
        int y2 = pathY[i];

        Line(x1,y1,x2,y2, pixOp, p, p, zOp, z, z);
    }

    bool clear = _preservePath == 0;

    if (_preservePath > 0) _preservePath--;
    if (clear) ClearPath();
}


struct Rational
{
    int integer;
    int numerator;
    int denominator;
};

void Image::Line(int xA,int yA, int xB, int yB, PixOp pixOp, ARGB pA, ARGB pB,
                    ZOp zOp, float zA, float zB)
{
    /* TODO */ //boil up specialized code
    int xD = (xB-xA);
    int yD = (yB-yA);

    int xS = xD<0?-1:1;
    int yS = yD<0?-1:1;

    xD *= xS;
    yD *= yS;

    //xD++;
    //yD++;

    if (xD==0) xS=0;
    if (yD==0) yS=0;

    int rD = pB.r - pA.r;
    int gD = pB.g - pA.g;
    int bD = pB.b - pA.b;
    int aD = pB.a - pA.a;

    float zD = zB - zA;

    if (xD <= yD)
    {
        if (yD == 0)
        {
            if (pixOp == PixOp_SRC) {
                pix[yA][xA] = pA;
            } else if (pixOp == PixOp_SRC_ALPHA) {
                ARGB dest = pix[yA][xA];
                dest.r = valValAlpha(dest.r, pA.r, pA.a);
                dest.g = valValAlpha(dest.g, pA.g, pA.a);
                dest.b = valValAlpha(dest.b, pA.b, pA.a);
                dest.a = valValAlpha(dest.a, pA.a, pA.a);
                pix[yA][xA] = dest;
            }

            if (zOp == ZOp_SRC)
            {
                z[yA][xA] = zA;
            } else if (zOp == ZOp_SRC_ADD)
            {
                z[yA][xA] += zA;
            }
            return;
        }

        Rational r = {xA, 0, yD};
        Rational s = {xD / yD *xS, xD % yD, yD};

        int y = yA;
        for (int d=0; d <= yD; d++)
        {
            ARGB p = { (unsigned char) (pA.a + aD * d / yD),
                       (unsigned char) (pA.r + rD * d / yD),
                       (unsigned char) (pA.g + gD * d / yD),
                       (unsigned char) (pA.b + bD * d / yD)};

            if (pixOp == PixOp_SRC) {
                pix[y][r.integer] = p;
            } else if (pixOp == PixOp_SRC_ALPHA) {
                ARGB dest = pix[y][r.integer];
                dest.r = valValAlpha(dest.r, p.r, p.a);
                dest.g = valValAlpha(dest.g, p.g, p.a);
                dest.b = valValAlpha(dest.b, p.b, p.a);
                dest.a = valValAlpha(dest.a, p.a, p.a);
                pix[y][r.integer] = dest;
            }

            if (zOp == ZOp_SRC)
            {
                z[y][r.integer] = zA + zD * d / yD;
            } else if (zOp == ZOp_SRC_ADD)
            {
                z[y][r.integer] += zA + zD * d / yD;
            }

            r.integer += s.integer;
            if (r.numerator += s.numerator)
            {
                if (r.numerator >= r.denominator)
                {
                    r.numerator -= r.denominator;
                    r.integer += xS;
                }
            }

            y+=yS;
        }
    } else
    {
        /*
        if (yD == 0)
        {
            if (pixOp == PixOp_SRC) {
                pix[yA][xA] = pA;
            } else if (pixOp == PixOp_SRC_ALPHA) {
                ARGB dest = pix[yA][xA];
                dest.r = valValAlpha(dest.r, pA.r, pA.a);
                dest.g = valValAlpha(dest.g, pA.g, pA.a);
                dest.b = valValAlpha(dest.b, pA.b, pA.a);
                dest.a = valValAlpha(dest.a, pA.a, pA.a);
                pix[yA][xA] = dest;
            }

            if (zOp == ZOp_SRC)
            {
                z[yA][xA] = zA;
            } else if (zOp == ZOp_SRC_ADD)
            {
                z[yA][xA] += zA;
            }
            return;
        }*/


        Rational r = {yA, 0, xD};
        Rational s = {yD / xD *yS, yD % xD, xD};

        int x = xA;
        for (int d=0; d <= xD; d++)
        {
            ARGB p = { (unsigned char) (pA.a + aD * d / xD),
                       (unsigned char) (pA.r + rD * d / xD),
                       (unsigned char) (pA.g + gD * d / xD),
                       (unsigned char) (pA.b + bD * d / xD)};

            if (pixOp == PixOp_SRC) {
                pix[r.integer][x] = p;
            } else if (pixOp == PixOp_SRC_ALPHA) {
                ARGB dest = pix[r.integer][x];
                dest.r = valValAlpha(dest.r, p.r, p.a);
                dest.g = valValAlpha(dest.g, p.g, p.a);
                dest.b = valValAlpha(dest.b, p.b, p.a);
                dest.a = valValAlpha(dest.a, p.a, p.a);
                pix[r.integer][x] = dest;
            }

            if (zOp == ZOp_SRC)
            {
                z[r.integer][x] = zA + zD * d / xD;
            } else if (zOp == ZOp_SRC_ADD)
            {
                z[r.integer][x] += zA + zD * d / xD;
            }

            r.integer += s.integer;
            if (r.numerator += s.numerator)
            {
                if (r.numerator >= r.denominator)
                {
                    r.numerator -= r.denominator;
                    r.integer += yS;
                }
            }

            x+=xS;
        }
    }
}

struct FillRect_Params
{
    Image *image;
    int x1;
    int y1;
    int x2;
    int y2;

    PixOp pixOp;
    ARGB p;

    ZOp zOp;
    float z;
};

void FillRectProc_SRC_SRC(GfxThreadWorker *w, Image *image, int x1, int _y1, int x2, int _y2,
        PixOp pixOp, ARGB p, ZOp zop, float z)
{
    int t;
    if (x1>x2)
    {
        t=x1;
        x1=x2;
        x2 = t;
    }

    if (_y1>_y2)
    {
        t=_y1;
        _y1 =_y2;
        _y2 = t;
    }

    int h = (_y2-_y1);

    int y1 = _y1 + h * w->index / w->of;
    int y2 = _y1 + h * (w->index+1) / w->of;


    for (int x=x1; x<=x2; x++)
    {
        image->pix[y1][x] = p;
        image->z[y1][x] = z;
    }

    int _w = x2-x1+1;

    int pixb = ARGB::size * (_w);
    int zb = sizeof(float)*_w;

    for (int y=y1+1; y<y2; y++)
    {
        memcpy(image->pix[y]+x1, image->pix[y1]+x1, pixb);
        memcpy(image->z[y]+x1, image->z[y1]+x1, zb);
    }

}

void FillRectProc(GfxThreadWorker *w, Image *image, int x1, int _y1, int x2, int _y2,
                          PixOp pixOp, ARGB p, ZOp zOp, float z)
{
    int t;
    if (x1>x2)
    {
        t=x1;
        x1=x2;
        x2 = t;
    }

    if (_y1>_y2)
    {
        t=_y1;
        _y1 =_y2;
        _y2 = t;
    }

    int h = (_y2-_y1);

    int y1 = _y1 + h * w->index / w->of;
    int y2 = _y1 + h * (w->index+1) / w->of;

    for (int y=y1; y<y2; y++)
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

}


void *FillRectSlice_SRC_SRC(GfxThreadWorker *w)
{
    FillRect_Params *p = (FillRect_Params *)w->p[17];
    FillRectProc_SRC_SRC(w, p->image, p->x1, p->y1, p->x2, p->y2, p->pixOp, p->p, p->zOp, p->z);
    return nullptr;
}


void *FillRectSlice(GfxThreadWorker *w)
{
    FillRect_Params *p = (FillRect_Params *)w->p[17];
    FillRectProc(w, p->image, p->x1, p->y1, p->x2, p->y2, p->pixOp, p->p, p->zOp, p->z);
    return nullptr;
}


void Image::FillRect(int x1,int y1, int x2, int y2, PixOp pixOp, ARGB p, ZOp zOp, float z)
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    FillRect_Params params;

    params.image = this;
    params.x1 = x1;
    params.y1 = y1;
    params.x2 = x2;
    params.y2 = y2;
    params.pixOp = pixOp;
    params.p = p;
    params.zOp = zOp;
    params.z = z;

    GfxWorker_ProcType func;

    if (pixOp == PixOp_SRC && zOp == ZOp_SRC)
    {
        func = FillRectSlice_SRC_SRC;
    } else func = FillRectSlice;

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = func;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);
}


struct Anaglyph_Params
{
    Image *image;
    Image *left;
    Image *right;
};

void AnaglyphProc(GfxThreadWorker *w, Image *image, Image *left, Image *right)
{

    int h = image->Height;

    int y1 = h * w->index / w->of;
    int y2 = h * (w->index+1) / w->of;


    for (int y=y1; y<y2; y++)
    {
        for (int x=0; x<image->Width; x++) {
            ARGB p = right->pix[y][x];
            p.r = left->pix[y][x].r;

            image->pix[y][x] = p;
        }
    }

}

void *AnaglyphSlice(GfxThreadWorker *w)
{
    Anaglyph_Params *p = (Anaglyph_Params *)w->p[17];
    AnaglyphProc(w, p->image, p->left, p->right);
    return nullptr;
}


void Image::AnaglyphFrom(Image *L, Image *R)
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    Anaglyph_Params params;

    params.image = this;
    params.left = L;
    params.right = R;

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = AnaglyphSlice;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);

}



void *CalcZSlice(GfxThreadWorker *w)
{
    Image *image = (Image *)w->p[17];

    int h = image->Height;

    int y1 = h * w->index / w->of;
    int y2 = h * (w->index+1) / w->of;

    for (int y=y1; y<y2; y++) {
        for (int x = 0; x < image->Width; x++) {
            ARGB p = image->pix[y][x];
            image->z[y][x] = 1.0f - Rgb_v(p.r,p.g,p.b);
        }
    }

    return nullptr;
}


void Image::CalcZ()
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;


    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = this;

        w->WorkerProc = CalcZSlice;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);

}