//
// Created by jwc on 2/12/19.
//
extern "C"
{
#include <Threading/Sync.h>
}

#include <cmath>
#include "Image.h"

struct ArtifData
{
    int Magic;

    int l;
    float *depth;
    int *loff, *roff;
    float *lzbuf, *rzbuf;
};

thread_local ArtifData myData = {0x7A9F3F63, 0};

void freeMyData()
{
    delete [] myData.depth;
    delete [] myData.loff;
    delete [] myData.roff;
    delete [] myData.lzbuf;
    delete [] myData.rzbuf;

    myData.depth = NULL;
    myData.loff = NULL;
    myData.roff = NULL;
    myData.lzbuf = NULL;
    myData.rzbuf = NULL;

    myData.l = 0;

    //printf("[%p]->freeMyData()\n", (void *) pthread_self()); fflush(stdout);
}

void initMyData(int Width)
{
    if (myData.Magic == 0x7A9F3F63 && myData.l != 0) freeMyData();

    myData.depth = new float[Width];
    myData.loff = new int[Width];
    myData.roff = new int[Width];
    myData.lzbuf = new float[Width];
    myData.rzbuf = new float[Width];

    myData.l = Width;

    myData.Magic = 0x7A9F3F63;

    //printf("[%p]->thread data init width:%d\n", (void *)pthread_self(), Width); fflush(stdout);
}

ARGB q = {0xFF,0xFF,0xFF,0xFF};

static void drawline(int xp, int x1, int x2, ARGB pixa, ARGB pixb, double z1, double z2, ARGB *outRow, double * zbuf)
{
    int d = x1 - x2;
    if (d<0) d = -d;

    int r = pixa.r;
    int g = pixa.g;
    int b = pixa.b;
    int a = pixa.a;

    int ro = pixb.r - r;
    int go = pixb.g - g;
    int bo = pixb.b - b;
    int ao = pixb.a - a;

    double dp = 1.0 / d;

    int x2_1 = x2 - x1;
    double z2_1 = z2 - z1;

    for (int q=0; q<d; q++)
    {
        double _q = q * dp;

        int x = x1 + (x2_1) * q / d;
        double z = z1 + (z2_1) * _q;

        if (z>zbuf[x])
        {
            zbuf[x] = z;

            ARGB pix;

            pix.r = r + ro * q / d;
            pix.g = g + go * q / d;
            pix.b = b + bo * q / d;
            pix.a = a + ao * q / d;

            outRow[x+xp] = pix;
        }
    }
}

void Artif3dSlice(GfxThreadWorker *w, Image *in, int sep, Image *left, Image *right) {

    sep >>= 1;

    int Width = in->Width;
    int Height = in->Height;
    float *_depth = in->zMemory;

    int start = Height * w->index / w->of;
    int end = Height * (w->index + 1) / w->of;

    for (int y=start; y<end; y++)
    {
        for (int x=0; x<Width; x++) {
            left->z[y][x] = right->z[y][x] = INFINITY;
        }

        for (int x=0; x<Width-1; x++)
        {
            Image *O;

            float z1 = in->z[y][x];
            float z2 = in->z[y][x+1];

            int x1;
            int x2;

            ARGB A = in->pix[y][x];
            ARGB B = in->pix[y][x+1];

            int d;

            x1 = (int) (x - sep * z1);
            x2 = (int) (x - sep * z2);
            O = left;

            d = (x1-x2);
            if (d<0) d = -d;

            if (d == 0)
            {
                if (x1>=0 && x1<Width && z1 < O->z[y][x1])
                {
                    O->pix[y][x1] = A;
                    O->z[y][x1] = z1;
                }
            } else for (int q=0; q<=d; q++)
            {
                int _x = x1 + (x2-x1)*q/d;
                float _z = z1 + (z2-z1)*q/d;

                ARGB C ={
                        (unsigned char) (A.a + ((int)B.a - A.a) * q / d),
                        (unsigned char) (A.r + ((int)B.r - A.r) * q / d),
                        (unsigned char) (A.g + ((int)B.g - A.g) * q / d),
                        (unsigned char) (A.b + ((int)B.b - A.b) * q / d),
                };

                if (_x>=0 && _x<Width && _z < O->z[y][_x])
                {
                    O->pix[y][_x] = C;
                    O->z[y][_x] = _z;
                }
            }

            x1 = (int) (x + sep * z1);
            x2 = (int) (x + sep * z2);
            O = right;

            d = (x1-x2);
            if (d<0) d = -d;

            if (d == 0)
            {
                if (x1>=0 && x1<Width && z1 < O->z[y][x1])
                {
                    O->pix[y][x1] = A;
                    O->z[y][x1] = z1;
                }
            } else for (int q=0; q<=d; q++)
                {
                    int _x = x1 + (x2-x1)*q/d;
                    float _z = z1 + (z2-z1)*q/d;

                    ARGB C ={
                            (unsigned char) (A.a + ((int)B.a - A.a) * q / d),
                            (unsigned char) (A.r + ((int)B.r - A.r) * q / d),
                            (unsigned char) (A.g + ((int)B.g - A.g) * q / d),
                            (unsigned char) (A.b + ((int)B.b - A.b) * q / d),
                    };

                    if (_x>=0 && _x<Width && _z < O->z[y][_x])
                    {
                        O->pix[y][_x] = C;
                        O->z[y][_x] = _z;
                    }
                }


        }
    }



}

struct Artif3d_Params
{
    Image *image;
    Image *left;
    Image *right;

    int sep;

};


void *Artif3dProc(GfxThreadWorker *w)
{
    Artif3d_Params *p = (Artif3d_Params *)w->p[17];
    Artif3dSlice(w, p->image, p->sep, p->left, p->right);
    return nullptr;
}

void Image::Artif3d(int sep, Image *left, Image *right)
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    Artif3d_Params params;

    params.image = this;
    params.left = left;
    params.right = right;
    params.sep = sep;

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = Artif3dProc;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);

}

void InferDepthSlice_NoFilter(GfxThreadWorker *w, Image *in, float scale, float offset, int filter) {

    int Width = in->Width;
    int Height = in->Height;

    int start = Height * w->index / w->of;
    int end = Height * (w->index + 1) / w->of;

    for (int y=start; y<end; y++)
    {
        for (int x=0; x<Width; x++) {
            ARGB p = in->pix[y][x];
            float z = 1.0f - Rgb_v(p.r,p.g,p.b);
            z *= z;

            in->z[y][x] = z * scale + offset;
        }
    }
}

void InferDepthSlice(GfxThreadWorker *w, Image *in, float scale, float offset, int filter) {

    int Width = in->Width;
    int Height = in->Height;

    int start = Height * w->index / w->of;
    int end = Height * (w->index + 1) / w->of;

    ARGB p;
    float z;

    int x;

    int e = in->Width - filter;

    for (int y=start; y<end; y++)
    {
        float Z = 0;
        int D = 0;

        for (x=0; x<filter && x<in->Width; x++)
        {
            p = in->pix[y][x];
            z = 1.0f - Rgb_v(p.r,p.g,p.b);
            z *= z;

            Z += z;
            D++;
        }

        for (x=0; x<=filter && x<e; x++) {
            p = in->pix[y][x+filter];
            z = 1.0f - Rgb_v(p.r,p.g,p.b);
            z *= z;

            Z += z;
            D++;

            in->z[y][x] = Z / D;
        }

        for (; x < e; x++)
        {
            p = in->pix[y][x+filter];
            z = 1.0f - Rgb_v(p.r,p.g,p.b);
            z *= z;

            Z += z;
            Z-=in->z[y][x-filter];


            in->z[y][x] = Z / D;

        }

        for (; x < in->Width; x++)
        {
            Z-=in->z[y][x-filter];
            D--;

            in->z[y][x] = Z / D;

        }
    }
}

struct InferDepth_Params
{
    Image *image;

    float scale;
    float offset;
    int filter;

};


void *InferDepthProc(GfxThreadWorker *w)
{
    InferDepth_Params *p = (InferDepth_Params *)w->p[17];
    if (p->filter == 0) InferDepthSlice_NoFilter(w, p->image, p->scale, p->offset, p->filter);
    else InferDepthSlice(w, p->image, p->scale, p->offset, p->filter);
    return nullptr;
}

void Image::InferDepth(float scale, float offset, float filter)
{
    int count = gfxThreadWorkerCount;
    GfxThreadWorker **workers = gfxThreadWorkers;

    InferDepth_Params params;

    params.image = this;
    params.scale = scale;
    params.offset = offset;
    params.filter = (int) (filter*Width);

    for (int i = 0; i < count; i++) {
        GfxThreadWorker *w = gfxThreadWorkers[i];

        w->p[17] = &params;

        w->WorkerProc = InferDepthProc;
    }

    Barrier_wait(gfxThreadWorkerBarrier);
    Barrier_wait(gfxThreadWorkerBarrier);


}