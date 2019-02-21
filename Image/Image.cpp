//
// Created by jwc on 2/8/19.
//
extern "C"
{
    #include <Threading/Sync.h>
}

#include <QtGui/QtGui>
#include "Image.h"

struct Rational
{
    int integer;
    int numerator;
    int denominator;
};

ImageMask::ImageMask(int Width, int Height)
{
    this->Width = Width;
    this->Height = Height;

    stride = Width;

    imageMemory = new unsigned char[Width * Height];

    memset(imageMemory, 0, Width*Height);

    pix = new unsigned char *[Height];

    unsigned char *d = imageMemory;

    for (int y=0; y<Height; y++)
    {
        pix[y] = d; d+=stride;
        //memset(pix[y], 0, Width);
    }
}

ImageMask::~ImageMask()
{
    delete pix;
    delete imageMemory;
}

void ImageMask::Line(int xA,int yA, int xB, int yB,unsigned char pA, unsigned char pB)
{
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

    int D = pB - pA;

    if (xD <= yD)
    {
        if (yD == 0) {
            pix[yA][xA] = pA;
            return;
        }

        Rational r = {xA, 0, yD};
        Rational s = {xD / yD *xS, xD % yD, yD};

        int y = yA;
        for (int d=0; d <= yD; d++)
        {
            unsigned char p = (unsigned char) (pA + D * d / yD);

            pix[y][r.integer] = p;

            r.integer += s.integer;
            r.numerator += s.numerator;

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
            unsigned char p = (unsigned char) (pA + D * d / xD);

            pix[r.integer][x] = p;

            r.integer += s.integer;
            r.numerator += s.numerator;

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


struct scanEntry {
    int cur;
    int low;
    int high;
    bool up = true;

    int y;
};

void ImageMask::FloodFill(int x, int y) {

    ImageMask *_this = this;

    unsigned char **m = _this->pix;

    std::list<scanEntry> se;

    int _x = x;
    int _y = y;

    do {
        int sx = _x;
        int sy = _y;

        bool f;

        f = true;

        while ((_x >= 0) && f && (m[_y][_x] == 0)) {
            m[_y][_x] = 1;
            _x--;
        }

        int lx = _x;

        _x = sx + 1;
        f = true;

        while ((_x < _this->Width) && f && (m[_y][_x] == 0)) {
            m[_y][_x] = 1;
            _x++;
        }

        int hx = _x;

        if (lx + 1 < hx) {
            scanEntry s;
            memset(&s,0,sizeof(s));
            s.low = lx;
            s.high = hx;
            s.cur = lx;
            s.y = _y;
            s.up = true;

            se.push_back(s);
        }

        bool r;
        do {

            scanEntry *s = &se.front();

            s->cur++;
            _x = s->cur;
            _y = s->y + (s->up ? -1 : 1);

            r = (_y >= 0 && _y < _this->Height) && _x < s->high;

            if (!r) {
                if (!se.front().up) se.pop_front();
                else {
                    s->up = false;
                    s->cur = s->low;
                }
            } else r = (_this->Bound(_x, _y) && m[_y][_x] == 0);
        } while ((!r) && (se.empty() == false));

    } while (se.empty() == false);
}


void Image::FillPath(int x, int y, PixOp pixOp, ARGB p, ZOp zOp, float z)
{

    ImageMask *m = new ImageMask(Width,Height);

    for (int i = 1; i < pathIndex; i++) {
        int x1 = pathX[i - 1];
        int y1 = pathY[i - 1];

        int x2 = pathX[i];
        int y2 = pathY[i];

        m->Line(x1,y1,x2,y2, 1, 1);
    }

    m->FloodFill(x,y);

    for (int y=0; y<Height; y++) {
        for (int x = 0; x < Width; x++) {
            if (m->pix[y][x]) {
                if (pixOp == PixOp_SRC) {
                    //pix[y][x] = p;
                    pix[y][x] = p;

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

    delete m;

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