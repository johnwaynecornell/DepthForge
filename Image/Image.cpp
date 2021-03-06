//
// Created by jwc on 2/8/19.
//
extern "C"
{
    #include <Threading/Sync.h>
}

#include <QtGui/QtGui>

#include "Image.h"
#include "TrigCache.h"
#include <math.h>

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

            if (Bound(r.integer, y)) pix[y][r.integer] = p;

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

            if (Bound(r.integer,x)) pix[r.integer][x] = p;

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
    path = new PathEntry[pathMax];

    imageMemory = new ARGB[Width * Height];

    //memset(imageMemory, 0, Width*Height* sizeof(ARGB));

    pix = new ARGB *[Height];

    zMemory = new float[Width*Height];
    z = new float *[Height];

    //memset(zMemory,0,sizeof(float)*Width*Height);

    ARGB *d = imageMemory;
    float *d2 = zMemory;

    for (int y=0; y<Height; y++)
    {
        pix[y] = d; d+=stride;
        z[y] = d2; d2+=stride;
    }

    needUpdate = true;

    resetBound();
    FillRect(0,0,Width,Height,PixOp_SRC, {0,0,0,0}, ZOp_SRC, 0.0f);
}

Image::~Image()
{
    delete []pix;
    delete []imageMemory;

    delete []z;
    delete []zMemory;

    delete []path;
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

void Image::MoveTo(int x1, int y1)
{
    pathLastX = x1;
    pathLastY = y1;
}
void Image::Circle(int r, bool Invert)
{
    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {pathLastX, pathLastY, pathLastX, pathLastY, r, true, Invert};
    pathIndex++;

}
void Image::Circle(int x, int y, int r, bool Invert)
{
    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {x, y, x, y, r, true, Invert};
    pathIndex++;

    pathLastX = x;
    pathLastY = y;
}

void Image::Line(int x1, int y1, int x2, int y2)
{
    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {x1, y1, x2, y2, 0, false, false};
    pathIndex++;

    pathLastX = x2;
    pathLastY = y2;

}
void Image::LineTo(int x2, int y2)
{
    Q_ASSERT(pathIndex < pathMax);

    path[pathIndex] = {pathLastX, pathLastY, x2, y2, 0, false, false};
    pathIndex++;

    pathLastX = x2;
    pathLastY = y2;

}


struct scanEntry {
    int cur;
    int low;
    int high;
    bool up = true;
    ARGB q;

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

/*
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

}*/

void Image::DrawPath(PixOp pixOp, ARGB p, ZOp zOp, float z) {
    for (int i = 0; i < pathIndex; i++) {
        PathEntry &pe = path[i];

        if (pe.point)
        {
            int x1 = pe.x1;
            int y1 = pe.y1;

            if (pe.r==0)
            {
                if (pixOp == PixOp_SRC) {
                    //pix[y][x] = p;
                    pix[y1][x1] = p;

                } else if (pixOp == PixOp_SRC_ALPHA) {
                    ARGB dest = pix[y1][x1];
                    dest.r = valValAlpha(dest.r, p.r, p.a);
                    dest.g = valValAlpha(dest.g, p.g, p.a);
                    dest.b = valValAlpha(dest.b, p.b, p.a);
                    dest.a = valValAlpha(dest.a, p.a, p.a);
                    pix[y1][x1] = dest;
                }

                if (zOp == ZOp_SRC) {
                    this->z[y1][x1] = z;
                } else if (zOp == ZOp_SRC_ADD) {
                    this->z[y1][x1] += z;
                }
            } else
            {
                int lx, ly;

                int x = (int) (x1 + cos(0.0)*pe.r);
                int y = (int) (y1 + sin(0.0)*pe.r);

                double thd =M_PI*2/16;

                for (double th = thd; th <= M_PI*2; th += M_PI*2/16)
                {
                    int nx =(int) (x1 + cos(th)*pe.r);
                    int ny = (int) (x1 + sin(th)*pe.r);

                    if (nx != x || ny != y)
                        Line(x, y, nx, ny, pixOp, p, p, zOp, z, z);

                    x = nx;
                    y = ny;

                }
            }

        } else{

            int x1 = pe.x1;
            int y1 = pe.y1;

            int x2 = pe.x2;
            int y2 = pe.y2;

            Line(x1, y1, x2, y2, pixOp, p, p, zOp, z, z);
        }
    }

    bool clear = _preservePath == 0;

    if (_preservePath > 0) _preservePath--;
    if (clear) ClearPath();
}

struct MyPixFuncArgs
{
    int I;
    double X;
    void *args;
    bool (*func)(int I, double X, int x, int xD, ARGB &P, float &Z, void *arg);
};

bool myPixFunc(int x, int y, int v, int Vd, ARGB &p, float &z, void *arg)
{
    MyPixFuncArgs *myArgs = (MyPixFuncArgs *) arg;

    return myArgs->func(myArgs->I, myArgs->X, v, Vd, p, z, myArgs->args );
}

void Image::DrawPathOutline(PixOp pixOp, ZOp zOp,
                     bool (*func)(int I, double X, int x, int xD, ARGB &P, float &Z, void *arg), void *arg)
{
//    double X;

    MyPixFuncArgs A;

    A.X = 0;
    A.args = arg;
    A.func = func;

    for (int i = 0; i < pathIndex; i++) {

        A.I = i;

        PathEntry &pe = path[i];

        if (pe.point)
        {
            int x1 = pe.x1;
            int y1 = pe.y1;


            if (pe.r==0)
            {
                if (Bound(x1,y1)) {
                    ARGB p;
                    float z;

                    if (func(i, A.X, 0, 0, p, z, arg)) {

                        if (pixOp == PixOp_SRC) {
                            //pix[y][x] = p;
                            pix[y1][x1] = p;

                        } else if (pixOp == PixOp_SRC_ALPHA) {
                            ARGB dest = pix[y1][x1];
                            dest.r = valValAlpha(dest.r, p.r, p.a);
                            dest.g = valValAlpha(dest.g, p.g, p.a);
                            dest.b = valValAlpha(dest.b, p.b, p.a);
                            dest.a = valValAlpha(dest.a, p.a, p.a);
                            pix[y1][x1] = dest;
                        }

                        if (zOp == ZOp_SRC) {
                            this->z[y1][x1] = z;
                        } else if (zOp == ZOp_SRC_ADD) {
                            this->z[y1][x1] += z;
                        }
                    }
                }
            } else
            {
                int lx, ly;

                int x = (int) (x1 + cos(0.0)*pe.r);
                int y = (int) (y1 + sin(0.0)*pe.r);

                double thd =M_PI*2/16;

                for (double th = thd; th <= M_PI*2; th += M_PI*2/16)
                {
                    int nx =(int) (x1 + cos(th)*pe.r);
                    int ny = (int) (x1 + sin(th)*pe.r);

                    if (nx != x || ny != y) {
                        A.X += Line(x, y, nx, ny, pixOp, zOp, myPixFunc, &A);
                    }

                    x = nx;
                    y = ny;

                }
            }

        } else{

            int x1 = pe.x1;
            int y1 = pe.y1;

            int x2 = pe.x2;
            int y2 = pe.y2;

            A.X += Line(x1, y1, x2, y2, pixOp, zOp, myPixFunc, &A);
        }
    }

    bool clear = _preservePath == 0;

    if (_preservePath > 0) _preservePath--;
    if (clear) ClearPath();
}


TrigCellCache cache;

struct PathProcParams
{
    Image *img;
    pdata *data;
    int i;

    TrigEntry *E;

};

double sinTab[65536];
double cosTab[65536];

void _pathApply(double v, double _x, pdata *d, int i)
{
    if (abs(abs(v) - abs(d->mv)) < .00001) {
        if (abs(_x) < abs(d->x)) {
            //if (v<d->mv)
            {
                d->mv = v;
                d->i = i;
                d->x = _x;
            }
        }
    } else if (abs(v) < abs(d->mv)) {
        d->mv = v;
        d->i = i;
        d->x = _x;
    }
}

#define pathApply(v, _x, d, i) \
{\
    if (abs(abs(v) - abs(d->mv)) < .00001) {\
        if (abs(_x) < abs(d->x)) {\
            {\
                d->mv = v;\
                d->i = i;\
                d->x = _x;\
            }\
        }\
    } else if (abs(v) < abs(d->mv)) {\
        d->mv = v;\
        d->i = i;\
        d->x = _x;\
    }\
}

void *pathProcSlice(GfxThreadWorker *worker) {
    PathProcParams *p = (PathProcParams *) worker->p[17];

    Image *img = p->img;
    pdata *data = p->data;

    int ly = img->Height * worker->index / worker->of;
    int hy = img->Height * (worker->index + 1) / worker->of;

    int Width = img->Width;

    int i = p->i;
    TrigEntry *E = p->E;

    PathEntry *pe = img->path + i;

    if (!pe->point) {

        int x1 = pe->x1;
        int y1 = pe->y1;

        int xd = pe->x2 - x1;
        int yd = pe->y2 - y1;

        double th = -atan2(yd, xd);

        if (th < 0) th += M_PI * 2;

        double cs = cos(th);
        double sn = sin(th);

//    int q = (int) ((th/(M_PI*2))*65536);

        double _sqrt = sqrt(xd*xd+yd*yd);

        for (int y = ly; y < hy; y++) {
            for (int x = 0; x < Width; x++) {

                pdata *d = data + y * Width + x;

                double xx = x - x1;
                double yy = y - y1;


                //if (absmvsqr +10> (xx*xx+yy*yy))
                {
                    //Q_ASSERT(E->x == xd && E->y == yd);

                    /*
                    double cs = E->rCos;
                    double sn = E->rSin;
                    double _sqrt = E->sqrt;
                    */


                    double __x = xx * cs - yy * sn;
                    double __y = yy * cs + xx * sn;

                    double _x = __x;
                    double _y = __y;

                    if ((_x >= 0) && (_x <= _sqrt)) {
                        _x = 0;
                    } else if (_x < 0) {
                        _x = _x;
                    } else if (_x > _sqrt) {
                        _x -= _sqrt;
                    }

                    //E = cache.get((int)_x, (int)_y);

                    //th = atan2(_y,_x);
                    //double v = (_x) * cos(-th) - (_y) * sin(-th);
                    double v = (_x == 0) ? abs(_y) : sqrt(_x * _x + _y * _y);

                    if (_y < 0) v *= -1;// else if (_x>0) v *= -1;

                    //th = atan2(_y,_x);
                    //if (th<=0) v *= -1;

                    //th = atan2(_y,_x);

                    pathApply(v,_x,d,i);
                }
            }
        }
    } else {
        int x1 = pe->x1;
        int y1 = pe->y1;

        for (int y = ly; y < hy; y++) {
            for (int x = 0; x < Width; x++) {

                pdata *d = data + y * Width + x;

                double xx = x - x1;
                double yy = y - y1;

                double v = (pe->r-sqrt(xx * xx + yy * yy)) * (pe->invert ? -1 : 1);

                double _x = 0.0;

                pathApply(v,_x,d,i);

                /*if (abs(abs(v) - abs(d->mv)) < .00001) {
                    if (abs(_x) < abs(d->x)) {
                        d->mv = v;
                        d->i = i;
                        d->x = _x;
                    }
                } else*/


            }
        }
    }

    return nullptr;
}

#undef pathApply

void *pathProc(Image *img, pdata *pathdata, int i, TrigEntry *E)
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    PathProcParams params;

    params.img= img;
    params.data = pathdata;
    params.i = i;
    params.E = E;

    GfxWorker_ProcType func;

    func = pathProcSlice;

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = func;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);

    return nullptr;
}


struct PathMergeParams
{
    Image *img;
    pdata *data;
    double yScale;
    PixOp pixOp;
    ZOp zOp;

    bool (*pixFunc)(int index, double y, ARGB &p, float &z, void *arg);
    void *arg;
};

void *pathMergeSlice(GfxThreadWorker *worker)
{
    PathMergeParams *p = (PathMergeParams *) worker->p[17];

    Image *img = p->img;
    double yScale = p->yScale;
    PixOp pixOp = p->pixOp;
    ZOp zOp = p->zOp;
    void *arg = p->arg;
    ARGB **pix = img->pix;
    bool (*pixFunc)(int index, double y, ARGB &p, float &z, void *arg) = p->pixFunc;

    int ly = img->Height * worker->index / worker->of;
    int hy = img->Height * (worker->index+1) / worker->of;

    for (int y=ly; y<hy; y++)
    {
        for (int x=0; x<img->Width; x++)
        {
            pdata *d = p->data + y*img->Width+x;

            ARGB p;
            float _z;

            d->mv *= yScale;

            if (pixFunc(d->i, d->mv, p, _z, arg))
            {
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
                    img->z[y][x] = _z;
                } else if (zOp == ZOp_SRC_ADD) {
                    img->z[y][x] += _z;
                }

            }

        }
    }

    return nullptr;
}

struct minMaxFuncParams
{
    pdata *data;
    double *min;
    double *max;

    double yScale;
    int Width;
    int Height;
};

void *pathMinMaxSlice(GfxThreadWorker *worker)
{
    minMaxFuncParams *p = (minMaxFuncParams *) worker->p[17];

    int ly = p->Height * worker->index / worker->of;
    int hy = p->Height * (worker->index+1) / worker->of;

    int t = worker->index;

    p->min[t] = INFINITY;
    p->max[t] = -INFINITY;

    for (int y=ly; y<hy; y++)
    {
        for (int x=0; x<p->Width; x++)
        {
            pdata *d = p->data + y*p->Width+x;

            double mv = d->mv * p->yScale;

            if (mv<p->min[t]) p->min[t] = mv;
            if (mv>p->max[t]) p->max[t] = mv;
        }
    }

    return nullptr;
}

void *pathMerge(Image *img, pdata *pathdata, double yScale, PixOp pixOp, ZOp zOp,
                bool (*pixFunc)(int index, double y, ARGB &p, float &z, void *arg), void *arg) {

    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    PathMergeParams params;

    params.img= img;
    params.data = pathdata;
    params.yScale = yScale;
    params.pixOp = pixOp;
    params.zOp = zOp;

    params.pixFunc = pixFunc;
    params.arg = arg;

    GfxWorker_ProcType func;

    func = pathMergeSlice;

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = func;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);

    return nullptr;
}

pdata* Image::ComputePath(void)
{
    pdata *data = new pdata[Width*Height];

    for (int y=0; y<Height; y++) {
        for (int x = 0; x < Width; x++) {
            data[y*Width+x] = {-1,INFINITY, 0};
        }
    }

    for (int i = 0; i < pathIndex; i++) {

        TrigEntry *E = nullptr;
        pathProc(this, data,i, E);
    }

    bool clearPath = _preservePath == 0;
    if (!clearPath) _preservePath--; else ClearPath();

    return data;
}

void Image::DrawPath(PixOp pixOp, ZOp zOp, double yScale,
              bool (*pixFunc)(int index, double y, ARGB &p, float &z, void *arg), void *arg)
{
    pdata *data = new pdata[Width*Height];

    for (int y=0; y<Height; y++) {
        for (int x = 0; x < Width; x++) {
            data[y*Width+x] = {-1,INFINITY, 0};
        }
    }

    for (int i = 0; i < pathIndex; i++) {

        TrigEntry *E = nullptr;
        pathProc(this, data,i, E);
    }

    pathMerge(this, data,yScale,pixOp,zOp,pixFunc, arg);
    delete []data;

    bool clearPath = _preservePath == 0;
    if (!clearPath) _preservePath--; else ClearPath();
}

void Image::DrawPath(PixOp pixOp, ZOp zOp, double yScale,
                     double *min, double *max,
                     bool (*pixFunc)(int index, double y, ARGB &p, float &z, void *arg), void *arg)
{
    pdata *data = new pdata[Width*Height];

    for (int y=0; y<Height; y++) {
        for (int x = 0; x < Width; x++) {
            data[y*Width+x] = {-1,INFINITY, 0};
        }
    }

    for (int i = 0; i < pathIndex; i++) {

        TrigEntry *E = nullptr;

        pathProc(this, data,i, E);
    }

    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    minMaxFuncParams params;

    params.data = data;

    params.Width = Width;
    params.Height = Height;

    params.yScale = yScale;

    params.min = new double[count];
    params.max = new double[count];

    GfxWorker_ProcType func;

    func = pathMinMaxSlice;

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = func;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);

    double _min = params.min[0];
    double _max = params.max[0];

    for (int i = 1; i<count; i++)
    {
        if (params.min[i]<_min) _min = params.min[i];
        if (params.max[i]>_max) _max = params.max[i];
    }

    delete [] params.min;
    delete [] params.max;

    *min = _min;
    *max = _max;

    pathMerge(this, data,yScale,pixOp,zOp,pixFunc, arg);
    delete []data;

    bool clearPath = _preservePath == 0;
    if (!clearPath) _preservePath--; else ClearPath();
}


int Image::Line(int xA,int yA, int xB, int yB, PixOp pixOp, ZOp zOp,
          bool (*pixFunc)(int x, int y, int v, int Vd, ARGB &p, float &z, void *arg), void *arg)
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

    ARGB P;
    float Z;

    int Vd = (int)sqrt(xD*xD+yD*yD);

    if (xD <= yD)
    {
        if (yD == 0)
        {
            if (Bound(xA,yA)) {
                if (pixFunc(xA, yA, 0, 0, P, Z, arg)) {

                    if (pixOp == PixOp_SRC) {
                        pix[yA][xA] = P;
                    } else if (pixOp == PixOp_SRC_ALPHA) {
                        ARGB dest = pix[yA][xA];
                        dest.r = valValAlpha(dest.r, P.r, P.a);
                        dest.g = valValAlpha(dest.g, P.g, P.a);
                        dest.b = valValAlpha(dest.b, P.b, P.a);
                        dest.a = valValAlpha(dest.a, P.a, P.a);
                        pix[yA][xA] = dest;
                    }

                    if (zOp == ZOp_SRC) {
                        z[yA][xA] = Z;
                    } else if (zOp == ZOp_SRC_ADD) {
                        z[yA][xA] += Z;
                    }
                }
            }
            return Vd;
        }

        Rational r = {xA, 0, yD};
        Rational s = {xD / yD *xS, xD % yD, yD};

        Rational _d = {0, 0, yD};
        Rational _ds = {Vd / yD, Vd % yD, yD};

        int y = yA;
        for (int d=0; d <= yD; d++)
        {
            if (Bound(r.integer, y)) {
                if (pixFunc(r.integer, y, _d.integer, Vd, P, Z, arg)) {
                    ARGB p = P;;

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

                    if (zOp == ZOp_SRC) {
                        z[y][r.integer] = Z;
                    } else if (zOp == ZOp_SRC_ADD) {
                        z[y][r.integer] += Z;
                    }
                }
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

            _d.integer += _ds.integer;
            if (_d.numerator += _ds.numerator)
            {
                if (_d.numerator >= _ds.denominator)
                {
                    _d.numerator -= _d.denominator;
                    _d.integer += 1;
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

        Rational _d = {0, 0, xD};
        Rational _ds = {Vd / xD, Vd % xD, xD};

        int x = xA;
        for (int d=0; d <= xD; d++)
        {
            if (Bound(x, r.integer)) {
                if (pixFunc(x, r.integer, _d.integer, Vd, P, Z, arg)) {
                    ARGB p = P;

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

                    if (zOp == ZOp_SRC) {
                        z[r.integer][x] = Z;
                    } else if (zOp == ZOp_SRC_ADD) {
                        z[r.integer][x] += Z;
                    }
                }
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

            _d.integer += _ds.integer;
            if (_d.numerator += _ds.numerator)
            {
                if (_d.numerator >= _ds.denominator)
                {
                    _d.numerator -= _d.denominator;
                    _d.integer += 1;
                }
            }

            x+=xS;
        }
    }
    return Vd;
}


void Image::Line(int xA,int yA, int xB, int yB, PixOp pixOp, ARGB pA, ARGB pB,
                    ZOp zOp, float zA, float zB)
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

    int rD = pB.r - pA.r;
    int gD = pB.g - pA.g;
    int bD = pB.b - pA.b;
    int aD = pB.a - pA.a;

    float zD = zB - zA;

    if (xD <= yD)
    {
        if (yD == 0)
        {
            if (Bound(xA,yA)) {
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

                if (zOp == ZOp_SRC) {
                    z[yA][xA] = zA;
                } else if (zOp == ZOp_SRC_ADD) {
                    z[yA][xA] += zA;
                }
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

            if (Bound(r.integer, y)) {
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

                if (zOp == ZOp_SRC) {
                    z[y][r.integer] = zA + zD * d / yD;
                } else if (zOp == ZOp_SRC_ADD) {
                    z[y][r.integer] += zA + zD * d / yD;
                }
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

            if (Bound(x, r.integer)) {
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

                if (zOp == ZOp_SRC) {
                    z[r.integer][x] = zA + zD * d / xD;
                } else if (zOp == ZOp_SRC_ADD) {
                    z[r.integer][x] += zA + zD * d / xD;
                }
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

ImageMask *Image::FloodFill(int x1, int y1, bool (*pred)(Image *I, int x, int y))
{
    ImageMask *R = new ImageMask(Width, Height);
    unsigned char **m = R->pix;

    std::list<scanEntry> se;

    int _x = x1;
    int _y = y1;

    //ARGB Q = pix[_y][_x];

    do {
        int sx = _x;
        int sy = _y;

        bool f;

        f = true;

        while ((_x >= 0) && f && (!m[_y][_x]) && (pred(this, _x, _y))) {
            m[_y][_x] = 1;
            //Q = pix[_y][_x];
            _x--;
        }

        int lx = _x;

        _x = sx + 1;
        f = true;

        while ((_x < Width) && f && (!m[_y][_x]) && pred(this, _x, _y)) {
            m[_y][_x] = 1;
            //Q = pix[_y][_x];
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

        bool r = false;
        while ((!r) && (se.empty() == false)) {

            scanEntry *s = &se.front();

            s->cur++;
            _x = s->cur;
            _y = s->y + (s->up ? -1 : 1);

            r = (_y >= 0 && _y < Height) && _x < s->high;

            if (!r) {
                if (!se.front().up) se.pop_front();
                else {
                    s->up = false;
                    s->cur = s->low;
                }
            } else
            {
                r = (Bound(_x, _y) && (!m[_y][_x]) && pred(this, _x, _y));
                if (r)
                {
                    //m[_y][_x] = true;
                    //Q = pix[_y][_x];
                }
            }
        }

    } while (se.empty() == false);

    return R;
}


struct FillRect_Params
{
    Image *image;
    int x;
    int y;
    int width;
    int height;

    PixOp pixOp;
    ARGB p;

    ZOp zOp;
    float z;

    bool (*pixFunc)(Image *_this, int x, int y, ARGB &p, float &z, void *param);
    void *param;
};

void FillRectProc_SRC_SRC(GfxThreadWorker *w, Image *image, int _x, int _y,
        int width, int height,
        PixOp pixOp, ARGB p, ZOp zop, float z)
{
    int x2 = _x + width;

    int y1 = _y + height * w->index / w->of;
    int y2 = _y + height * (w->index+1) / w->of;

    int _w = width;

    int pixb = ARGB::size * (_w);
    int zb = sizeof(float)*_w;

    for (int x=_x; x<x2; x++)
    {
        image->pix[y1][x] = p;
        image->z[y1][x] = z;
    }

    for (int y=y1+1; y<y2; y++)
    {
        memcpy(image->pix[y]+_x, image->pix[y1]+_x, pixb);
        memcpy(image->z[y]+_x, image->z[y1]+_x, zb);
    }

}

void FillRectProc(GfxThreadWorker *w, Image *image, int x, int y, int width, int height,
                          PixOp pixOp, ARGB p, ZOp zOp, float z)
{
    /*
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
*/
    int y1 = y + height * w->index / w->of;
    int y2 = y + height * (w->index+1) / w->of;

    int x2 = x+width;

    for (int _y=y1; _y<y2; _y++)
    {
        for (int _x=x; _x<x2; _x++) {
            if (pixOp == PixOp_SRC) {
                image->pix[_y][_x] = p;
            } else if (pixOp == PixOp_SRC_ALPHA) {
                ARGB dest = image->pix[_y][_x];
                dest.r = valValAlpha(dest.r, p.r, p.a);
                dest.g = valValAlpha(dest.g, p.g, p.a);
                dest.b = valValAlpha(dest.b, p.b, p.a);
                dest.a = valValAlpha(dest.a, p.a, p.a);
                image->pix[_y][_x] = dest;
            }

            if (zOp == ZOp_SRC)
            {
                image->z[_y][_x] = z;
            } else if (zOp == ZOp_SRC_ADD)
            {
                image->z[_y][_x] += z;
            }
        }
    }

}


void *FillRectSlice_SRC_SRC(GfxThreadWorker *w)
{
    FillRect_Params *p = (FillRect_Params *)w->p[17];
    FillRectProc_SRC_SRC(w, p->image, p->x, p->y, p->width, p->height, p->pixOp, p->p, p->zOp, p->z);
    return nullptr;
}


void *FillRectSlice(GfxThreadWorker *w)
{
    FillRect_Params *p = (FillRect_Params *)w->p[17];
    FillRectProc(w, p->image, p->x, p->y, p->width, p->height,
            p->pixOp, p->p, p->zOp, p->z);
    return nullptr;
}

void FillRectPixFuncProc(GfxThreadWorker *w, Image *image, int x, int y, int width, int height,
                  PixOp pixOp, ZOp zOp, bool (*pixFunc)(Image *_this, int x, int y, ARGB &p, float &z, void *param), void *param)
{
    int y1 = y + height * w->index / w->of;
    int y2 = y + height * (w->index+1) / w->of;

    int x2 = x+width;

    for (int _y=y1; _y<y2; _y++)
    {
        for (int _x=x; _x<x2; _x++) {
            ARGB p;
            float z;

            if (pixFunc(image, _x, _y, p, z, param)) {

                if (pixOp == PixOp_SRC) {
                    image->pix[_y][_x] = p;
                } else if (pixOp == PixOp_SRC_ALPHA) {
                    ARGB dest = image->pix[_y][_x];
                    dest.r = valValAlpha(dest.r, p.r, p.a);
                    dest.g = valValAlpha(dest.g, p.g, p.a);
                    dest.b = valValAlpha(dest.b, p.b, p.a);
                    dest.a = valValAlpha(dest.a, p.a, p.a);
                    image->pix[_y][_x] = dest;
                }

                if (zOp == ZOp_SRC) {
                    image->z[_y][_x] = z;
                } else if (zOp == ZOp_SRC_ADD) {
                    image->z[_y][_x] += z;
                }
            }
        }
    }

}

void *FillRectPixFuncSlice(GfxThreadWorker *w)
{
    FillRect_Params *p = (FillRect_Params *)w->p[17];
    FillRectPixFuncProc(w, p->image, p->x, p->y, p->width, p->height,
                 p->pixOp, p->zOp, p->pixFunc, p->param);
    return nullptr;
}


void Image::FillRect(int x,int y, int w, int h, PixOp pixOp, ZOp zOp, bool (*pixFunc)(Image *_this, int x, int y, ARGB &p, float &z, void *param), void *param)
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    FillRect_Params params;

    params.image = this;
    params.x = x;
    params.y = y;
    params.width = w;
    params.height = h;
    params.pixOp = pixOp;
    params.zOp = zOp;
    params.pixFunc = pixFunc;
    params.param = param;

    GfxWorker_ProcType func;

    func = FillRectPixFuncSlice;

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = func;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);
}

void Image::FillRect(int x,int y, int width, int height,
        PixOp pixOp, ARGB p, ZOp zOp, float z)
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    FillRect_Params params;

    params.image = this;
    params.x = x;
    params.y = y;
    params.width = width;
    params.height = height;
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

void Image::Tile(int dx,int dy, int dw, int dh,
          PixOp pixOp, ZOp zOp, Image *src, int sxo, int syo, int sx, int sy, int sw, int sh)
{
    if (dw==0 || dh == 0 || sw == 0 || sh==0) return;

    int x1 = dx;
    int x2 = x1 + dw-1;

    int y1 = dy;
    int y2 = y1 + dh-1;

    Image *image = this;

    for (int y=y1; y<y2; y++)
    {
        int yy = sy + ((y-dy+syo) % sh);

        for (int x=x1; x<=x2; x++) {
            int xx = sx + ((x-dx+sxo) % sw);

            ARGB p = src->pix[yy][xx];
            float z = src->z[yy][xx];

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

void Image::setBound(int boundX, int boundY, int boundW, int boundH)
{
    this->boundX = boundX;
    this->boundY = boundY;
    this->boundW = boundW;
    this->boundH = boundH;
}
void Image::resetBound()
{
    this->boundX = 0;
    this->boundY = 0;
    this->boundW = Width;
    this->boundH = Height;
}
