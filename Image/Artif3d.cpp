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


void Artif3dSliceold(GfxThreadWorker *w, Image *in, int sep, Image *left, Image *right)
{

    int Width = in->Width;
    int Height = in->Height;
    float *_depth = in->zMemory;

    int start = Height * w->index / w->of;
    int end   = Height * (w->index+1) / w->of;

    if (end > Height) end = Height;

    if (myData.Magic != 0x7A9F3F63 || myData.l < Width) initMyData(Width);

    float *depth = myData.depth;

    int *loff = myData.loff;
    int *roff = myData.roff;

    float *lzbuf = myData.lzbuf;
    float *rzbuf = myData.rzbuf;

    int x;

    for (int y=start; y < end; y++)
    {
        ARGB *inRow = in->pix[y];
        ARGB *outRowLeft = left->pix[y];
        ARGB *outRowRight = right->pix[y];

        int p = 3;
        float _s = 0;
        int d = 0;


        float *_depthRow = _depth + y * Width;

        //for (x=0; x<w; x++) _depthRow[x] = 1.0;

        for (x=0; x < p; x++)
        {	_s += _depthRow[x];
            d++;
        }

        for (x=0; x < Width; x++)
        {
            if (x-p-1>=0) {_s -= _depthRow[x-p-1]; d--; }

            depth[x] = _s / d;

            if (x+p < Width) { _s += _depthRow[x+p]; d ++; }

            loff[x] =  (int) (sep -depth[x]* sep);
            roff[x] = -loff[x];

            lzbuf[x] = rzbuf[x]= INFINITY;

        }

        for (int i=0; i < Width; i++)
        {
            outRowLeft[i] = outRowRight[i] = q;
        }


        int x1_L,x2_L=0;
        float z1_1,z2_1=0;

        ARGB pixa_1, pixb_1 = q;

        int x1_R,x2_R=0;

        for (x=0; x < Width; x++)
        {
            x1_L = x + loff[x];//lookup_x(x, inp.Width, sep, depth, loff);
            if (x1_L<0) x1_L = 0; else if (x1_L>=Width) x1_L = Width-1;

            z1_1 = depth[x];

            pixa_1 = inRow[x];

            x1_R = x + roff[x];//lookup_x(x, w, sep, depth, roff);
            if (x1_R<0) x1_R = 0; else if (x1_R>=Width) x1_R = Width-1;

            if (x != 0)
            {
                //drawline(0, x1_L, x2_L, pixa_1, pixb_1, z1_1, z2_1, outRow, lzbuf);
                //drawline(w, x1_R, x2_R, pixa_1, pixb_1, z1_1, z2_1, outRow, rzbuf);

                int xp;
                int x1,x2;
                ARGB pixa,pixb;
                float z2,z1;
                float *zbuf;

                xp = 0; x1 = x1_L; x2 = x2_L; pixa = pixa_1; pixb = pixb_1; z1 = z1_1; z2 = z2_1; zbuf = lzbuf;

                {

                    int d = x1 - x2;
                    if (d<0) d = -d;
                    if (d==0) d = 1;

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

                    for (int q=0; q<=d; q++)
                    {
                        double _q = q * dp;

                        int x = x1 + (x2_1) * q / d;
                        double z = z1 + (z2_1) * _q;

                        if (z<zbuf[x])
                        {
                            zbuf[x] = z;

                            ARGB pix;

                            pix.r = r + ro * q / d;
                            pix.g = g + go * q / d;
                            pix.b = b + bo * q / d;
                            pix.a = a + ao * q / d;

                            outRowLeft[x+xp] = pix;
                        }
                    }

                }

                xp = 0; x1 = x1_R; x2 = x2_R; zbuf = rzbuf;
                {

                    int d = x1 - x2;
                    if (d<0) d = -d;

                    if (d==0) d = 1;

                    int r = pixa.r;
                    int g = pixa.g;
                    int b = pixa.b;
                    int a = pixa.a;

                    int ro = pixb.r - r;
                    int go = pixb.g - g;
                    int bo = pixb.b - b;
                    int ao = pixb.a - a;

                    float dp = 1.0 / d;

                    int x2_1 = x2 - x1;
                    float z2_1 = z2 - z1;

                    for (int q=0; q<=d; q++)
                    {
                        float _q = q * dp;

                        int x = x1 + (x2_1) * q / d;
                        float  z = z1 + (z2_1) * _q;

                        if (z<zbuf[x])
                        {
                            zbuf[x] = z;

                            ARGB pix;

                            pix.r = r + ro * q / d;
                            pix.g = g + go * q / d;
                            pix.b = b + bo * q / d;
                            pix.a = a + ao * q / d;

                            outRowRight[x+xp] = pix;
                        }
                    }

                }



            }

            z2_1 = z1_1;

            pixb_1 = pixa_1;

            x2_L = x1_L;
            x2_R = x1_R;

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