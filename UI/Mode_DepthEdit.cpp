//
// Created by jwc on 4/2/19.
//

#include "Mode_DepthEdit.h"
#include "Forge.h"

Mode_DepthEdit::Mode_DepthEdit(MainUI *mainUI) : Mode(mainUI)
{
    previewLens = false;

    basicToolsCtl = new DepthForgeTabCtl(mainUI->tabs, QApplication::tr("Lens"));

    basicToolsCtl->width.setResp(Resp_Child);
    basicToolsCtl->height.setResp(Resp_Parent);
    basicToolsCtl->xPos.setResp(Resp_Self);
    basicToolsCtl->yPos.setResp(Resp_Self);

    basicToolsCtl->xPos.set(0);
    basicToolsCtl->yPos.set(0);

    basicToolsCtl->myMode = this;

    basicToolsCtl->tabPosition.set(mainUI->tabs->_tabPosition);
    mainUI->tabs->_tabPosition += 64 + 9;

    //basicToolsCtl->open();

    basicTools = new Fixed(basicToolsCtl);
    basicTools->width.setResp(Resp_Child);
    basicTools->height.setResp(Resp_Parent);
    basicTools->xPos.setResp(Resp_Self);
    basicTools->yPos.setResp(Resp_Self);

    basicTools->xPos.set(0);
    basicTools->yPos.set(0);

    toolFrame = new Frame(basicTools);
    toolFrame->width.setResp(Resp_Child);
    toolFrame->height.setResp(Resp_Child);
    toolFrame->xPos.setResp(Resp_Self);
    toolFrame->yPos.setResp(Resp_Self);

    toolFrame->xPos.set(0);
    toolFrame->yPos.set(0);

    tools = new Fixed(toolFrame);

    tools->width.setResp(Resp_Self);
    tools->height.setResp(Resp_Self);
    tools->xPos.setResp(Resp_Self);
    tools->yPos.setResp(Resp_Self);

    int lenssz = 64;
    int border = 6;
    
    tools->height.set((lenssz+ border)*3);
    tools->width.set((lenssz+ border)*2);
    tools->xPos.set(0);
    tools->yPos.set(0);

    bottomFrame = new Frame(basicTools);
    bottomFrame->width.setResp(Resp_Child);
    bottomFrame->height.setResp(Resp_Child);
    bottomFrame->xPos.setResp(Resp_Self);
    bottomFrame->yPos.setResp(Resp_Self);

    bottomFrame->xPos.set(0);
    bottomFrame->yPos.set(0);

    bottom = new Fixed(bottomFrame);
    bottom->width.setResp(Resp_Self);
    bottom->height.setResp(Resp_Self);
    bottom->xPos.setResp(Resp_Self);
    bottom->yPos.setResp(Resp_Self);

    bottom->height.set((lenssz+ border)*4);
    bottom->width.set((lenssz+ border)*2);
    bottom->xPos.set(0);
    bottom->yPos.set(0);

    slideA = new Slider(bottom, "Size", false, false);
    slideA->width.setResp(Resp_Self);
    slideA->height.setResp(Resp_Self);
    slideA->xPos.setResp(Resp_Self);
    slideA->yPos.setResp(Resp_Self);

    slideA->height.set((lenssz+ border)*4);
    slideA->width.set(32);
    slideA->xPos.set((lenssz+ border)*2-32-6);
    slideA->yPos.set(0);


    slideB = new Slider(bottom, "Intensity", false, false);
    slideB->width.setResp(Resp_Self);
    slideB->height.setResp(Resp_Self);
    slideB->xPos.setResp(Resp_Self);
    slideB->yPos.setResp(Resp_Self);

    slideB->height.set((lenssz+ border)*4);
    slideB->width.set(32);
    slideB->xPos.set((lenssz+ border)*2-32-6-32-3);
    slideB->yPos.set(0);

    union
    {
        void (Mode_DepthEdit::*a)(UI *, void *);
        void (*b)(void *, UI *, void *);
    } test;

    test.a = &Mode_DepthEdit::sizeEntered;

    slideA->setMouseEnterProc(test.b, this, nullptr);
    slideB->setMouseEnterProc(test.b, this, nullptr);

    test.a = &Mode_DepthEdit::sizeLeave;

    slideA->setMouseLeaveProc(test.b, this, nullptr);
    slideB->setMouseLeaveProc(test.b, this, nullptr);

    union
    {
        void (Mode_DepthEdit::*a)(UI *, double, void *);
        void (*b)(void *, UI *, double, void *);
    } testb;

    testb.a = &Mode_DepthEdit::sizeChanged;

    slideA->setVCallvack(testb.b, this, nullptr);

    testb.a = &Mode_DepthEdit::intensityChanged;

    slideB->setVCallvack(testb.b, this, nullptr);

    lens = nullptr;

    Lens *l = addLensButton(0,0, LensButton::Sphere, lenssz)->lens;
    addLensButton(0,lenssz+ border, LensButton::SphereC, lenssz);
    addLensButton(0,(lenssz+ border)*2, LensButton::Circle, lenssz);

    addLensButton(lenssz+ border,0, LensButton::Pyramid, lenssz);
    addLensButton(lenssz+ border,lenssz+ border, LensButton::PyramidC, lenssz);
    addLensButton(lenssz+ border,(lenssz+ border)*2, LensButton::Square, lenssz);

    setLens(l);
}

struct LensData
{
    float **map;
    Image *lensImage[10];
};


void Mode_DepthEdit::drawForge(Forge *forge, Image *target, QImage *qImage)
{
    if (forge->hasMouse || previewLens)
    {
        double time = mainUI->getTimeInSeconds();
        time = time - trunc(time);

        int xx;
        int yy;

        if (forge->hasMouse)
        {
            //xx = (int) (forge->mouseX * forge->_w + forge->_x);
            //yy = (int) (forge->mouseY * forge->_h + forge->_y);

            xx = forge->_x + (int) (((forge->mouseX * forge->src->Width) - forge->_srcX) * forge->_w / forge->_srcW);
            yy = forge->_y + (int) (((forge->mouseY * forge->src->Height) - forge->_srcY) * forge->_h / forge->_srcH);

            //xx = forge->_x + ((forge->mouseX * forge->src->Width) * forge->_w / (double) forge->src->Width);
            //yy = forge->_y + ((forge->mouseY * forge->src->Height) * forge->_h / (double) forge->src->Height);

        } else
        {
            xx = (int) (.5 * forge->_w + forge->_x);
            yy = (int) (.5 * forge->_h + forge->_y);
        }

        Lens *lens = this->lens;

        int sz;// = (int)(lens->size * fmax(forge->src->Width,forge->src->Height)*forge->scale);

        if (forge->src->Height > forge->src->Width)
        {
            sz = (int) (lens->size * forge->src->Height * forge->_h / forge->_srcH);
        } else
        {
            sz = (int) (lens->size * forge->src->Width * forge->_w / forge->_srcW);
        }

        //int sz = (int) (lens->size * fmax(forge->_w,forge->_h)*forge->scale);

        Lens::Cache * dta;

        LensData *d;

        if (!lens->getData(0, sz, &dta))
        {
            if (dta->dta != nullptr)
            {
                d = (LensData *)dta->dta;

                lens->freeMap(d->map, dta->s);

                for (int i =0; i<10; i++) {
                    if (d->lensImage[i] != nullptr) {
                        delete d->lensImage[i];
                        d->lensImage[i] = nullptr;
                    }
                }
            } else
            {
                dta->dta = d = new LensData();
                for (int i =0; i<10; i++)
                {
                    d->lensImage[i] = nullptr;
                }
            }

            d->map = lens->map(sz);
            dta->s = sz;

            dta->needUpdate = true;
        }

        d = ((LensData *)dta->dta);

        float **map = d->map;

        if (dta->needUpdate)
        {
            lens->updateMap(map, sz);

            for (int i=0; i<10; i++)
            {
                if (d->lensImage[i] != nullptr)
                {
                    d->lensImage[i]->needUpdate = true;
                }
            }

            dta->needUpdate = false;
        }

        int i = (int) (abs(time-.5)*2*9);

        int q = (sz << 1) + 1;

        if (d->lensImage[i] == nullptr) {

            d->lensImage[i] = new Image(q, q);
        }

        Image *img = d->lensImage[i];

        if (img->needUpdate)
        {

            for (int yp = -sz; yp <= sz; yp++) {
                int y = sz + yp;

                for (int xp = -sz; xp <= sz; xp++) {
                    int x = sz + xp;

                    float l = map[yp][xp];

                    unsigned char g = (unsigned char) (i * 0xFF / 9);

                    ARGB p = {(unsigned char) (0x80 * l), 0xFF, g, 0xFF};

                    img->pix[y][x] = p;
                }
            }
            img->needUpdate = false;
        }


        int _x1 = forge->xReal;
        int _y1 = forge->yReal;

        int _w1 = forge->width.get();
        int _h1 = forge->height.get();

        target->DrawImage(_x1, _y1, _w1, _h1,
                          xx-sz, yy-sz, q, q, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                          img, 0,0, q, q);


    }

}


void Mode_DepthEdit::applyLens(Forge *forge)
{
    Image *src = forge->src;

    int xx = forge->mouseX * forge->src->Width;
    int yy = forge->mouseY * forge->src->Height;

    Lens *lense= this->lens;

    int sz = (int)(lens->size * fmax(src->Width,src->Height));

    Qt::MouseButtons l;
    l.setFlag(Qt::MouseButton::LeftButton);

    Qt::MouseButtons r;
    r.setFlag(Qt::MouseButton::RightButton);

    double dir;

    if (forge->mouseDown == l) dir = -1;
    else if (forge->mouseDown == r) dir = 1;
    else return;

    for (int y=yy-sz; y<yy+sz; y++) {
        for (int x = xx - sz; x < xx + sz; x++) {
            if (y >= 0 && y < (src->Height)) {
                if (x >= 0 && x < (src->Width)) {
                    double lx = (y - yy) / (double) sz;
                    double ly = (x - xx) / (double) sz;

                    float l = lens->get(lx, ly);

                    src->z[y][x] += l * .01 * dir;

                }
            }

        }
    }

}

bool Mode_DepthEdit::mouseMoveForge(Forge *forge, int x, int y)
{
    applyLens(forge);
    return true;
}

bool Mode_DepthEdit::mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    applyLens(forge);
    return true;
}

bool Mode_DepthEdit::mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    return true;
}

void Mode_DepthEdit::selfLayout()
{
    basicToolsCtl->height.set(mainUI->height.get());
}

void Mode_DepthEdit::doLayout()
{
    bottomFrame->xPos.set(0);
    bottomFrame->yPos.set(basicTools->height.get()-bottomFrame->height.get());
}

void Mode_DepthEdit::setLens(Lens *lens)
{
    bool retain = this->lens != nullptr;

    double v, s;

    if (retain)
    {
        v = this->lens->intensity;
        s = this->lens->size;
    } else { v = .5; s = .1; }

    lens->setIntensity(v);
    lens->setSize(s);

    this->lens = lens;

    slideA->setV(s*2.0);
    slideB->setV(v/2.0);

}

LensButton * Mode_DepthEdit::addLensButton(int x, int y, LensProc proc, int lenssz)
{
    Frame *f = new Frame(tools);

    f->xPos.set(x);
    f->yPos.set(y);

    f->width.setResp(Resp_Child);
    f->height.setResp(Resp_Child);

    f->backgroundResp = Resp_Child;

    LensButton *bt = new LensButton(f, proc, lenssz);
    return bt;
}

void Mode_DepthEdit::sizeEntered(UI *sender, void *arg)
{
    previewLens = true;
}

void Mode_DepthEdit::sizeLeave(UI *sender, void *arg)
{
    previewLens = false;
}

void Mode_DepthEdit::sizeChanged(UI *sender, double v, void *arg)
{
    lens->setSize(v / 2.0);
}

void Mode_DepthEdit::intensityChanged(UI *sender, double v, void *arg)
{
    lens->setIntensity(v * 2.0);
}


LensButton::LensButton(UI *parent, LensProc proc, int lenssz) : Button_Image(parent)
{
    this->lens = new Lens();
    this->lens->proc = proc;

    Image * src = new Image(lenssz,lenssz);

    setSource(src, false);

    xPos.setResp(Resp_Self);
    yPos.setResp(Resp_Self);

    width.setResp(Resp_Self);
    height.setResp(Resp_Self);

    xPos.set(0);
    yPos.set(0);

    z = -0;
    backColor = {0xFF, 0x40,0x00,0x80, .25};

    backgroundResp = Resp_Self;


    Image *Q = src;

    int xc = Q->Height/2;
    int yc = Q->Width/2;

    for (int y=0; y<Q->Height; y++)
    {
        for (int x=0; x<Q->Width; x++)
        {
            unsigned char v;

            //          v = (unsigned char) (rand()%80);

            //          _bg->pix[y][x]={0xFF,
            //                         (unsigned char) (v+rand()%0x80), (unsigned char)(v+rand()%0x80),0};

            double xx = (x-xc) / (double) xc;
            double yy = (y-yc) / (double) yc;

            xx /= .9;
            yy /= .9;

            double d = lens->get(xx,yy);

//d=0;
            unsigned char r;
            unsigned char b;

            if (x%0x10 == 0 || y%0x10 == 0)
            {
                b=0x80;
                r=0x80;
            } else {
                b=0xFF;
                r=0xFF;
            }

            v = (unsigned char) (d*0xFF);
            Q->pix[y][x] = {v,r,b,b};
            Q->z[y][x] = -d * .25;

        }
    }
}

LensButton::~LensButton()
{
    delete lens;
}

bool LensButton::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    bool rc = Button_Image::mouseButtonPress(x,y,button);

    MainUI *r = ((MainUI *) rootElement());
    r->mode_DepthEdit->setLens(lens);

    return rc;
}

float LensButton::Sphere(float x, float y)
{
    float d = 1 - sqrtf(x*x+y*y);
    if (d<0) d = 0;

    return sin(d*M_PI/2);
}

float LensButton::SphereC(float x, float y)
{
    float d = 1 - sqrtf(x*x+y*y);
    if (d<0) return 0.0f;//d = 0;

    return 1.0f - sin(d*M_PI/2);
}



float LensButton::Circle(float x, float y)
{
    float d = 1 - sqrtf(x*x+y*y);
    return (d>0) ? 1.0 : 0.0;
}

float LensButton::Pyramid(float x, float y)
{
    x = 1.0 - abs(x);
    y = 1.0 - abs(y);

    if (x<0 || y<0) return 0;

    return fmin(x,y);
}

float LensButton::PyramidC(float x, float y)
{
    x = 1.0 - abs(x);
    y = 1.0 - abs(y);

    if (x<0 || y<0) return 0;

    return 1.0-fmin(x,y);
}

float LensButton::Square(float x, float y)
{
    if (x>=-1&&x<=1 && y>=-1&&y<=1) return 1;
    return 0;

}
