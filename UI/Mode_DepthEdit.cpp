//
// Created by jwc on 4/2/19.
//

#include "Mode_DepthEdit.h"
#include "Forge.h"

Mode_DepthEdit::Mode_DepthEdit(MainUI *mainUI) : Mode(mainUI)
{
    previewLense = false;

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

    tools->height.set(256+12);
    tools->width.set(256+12);
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

    bottom->height.set(256+12);
    bottom->width.set(256+12);
    bottom->xPos.set(0);
    bottom->yPos.set(0);

    slideA = new Slider(bottom, "Size");
    slideA->width.setResp(Resp_Self);
    slideA->height.setResp(Resp_Self);
    slideA->xPos.setResp(Resp_Self);
    slideA->yPos.setResp(Resp_Self);

    slideA->height.set(256+12);
    slideA->width.set(32);
    slideA->xPos.set(256+12-32-6);
    slideA->yPos.set(0);


    slideB = new Slider(bottom, "Intensity");
    slideB->width.setResp(Resp_Self);
    slideB->height.setResp(Resp_Self);
    slideB->xPos.setResp(Resp_Self);
    slideB->yPos.setResp(Resp_Self);

    slideB->height.set(256+12);
    slideB->width.set(32);
    slideB->xPos.set(256+12-32-6-32-3);
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

    lense = nullptr;

    Lense *l = addLenseButton(0,0, LenseButton::Sphere)->lense;

    addLenseButton(128+6,0, LenseButton::Circle);
    addLenseButton(0,128+6, LenseButton::Pyramid);
    addLenseButton(128+6,128+6, LenseButton::Square);

    setLense(l);
}

struct LenseData
{
    float **map;
    Image *lenseImage[10];
};


void Mode_DepthEdit::drawForge(Forge *forge, Image *target, QImage *qImage)
{
    if (forge->hasMouse || previewLense)
    {
        double time = mainUI->getTimeInSeconds();
        time = time - trunc(time);

        int xx;
        int yy;

        if (forge->hasMouse)
        {
            xx = (int) (forge->mouseX * forge->_w + forge->_x);
            yy = (int) (forge->mouseY * forge->_h + forge->_y);
        } else
        {
            xx = (int) (.5 * forge->_w + forge->_x);
            yy = (int) (.5 * forge->_h + forge->_y);
        }

        Lense *lense = this->lense;

        int sz = (int) (lense->size * fmax(forge->_w,forge->_h));

        Lense::Cache * dta;

        LenseData *d;

        if (!lense->getData(0, sz, &dta))
        {
            if (dta->dta != nullptr)
            {
                d = (LenseData *)dta->dta;

                lense->freeMap(d->map, dta->s);

                for (int i =0; i<10; i++) {
                    if (d->lenseImage[i] != nullptr) {
                        delete d->lenseImage[i];
                        d->lenseImage[i] = nullptr;
                    }
                }
            } else
            {
                dta->dta = d = new LenseData();
                for (int i =0; i<10; i++)
                {
                    d->lenseImage[i] = nullptr;
                }
            }

            d->map = lense->map(sz);
            dta->s = sz;

            dta->needUpdate = true;
        }

        d = ((LenseData *)dta->dta);

        float **map = d->map;

        if (dta->needUpdate)
        {
            lense->updateMap(map, sz);

            for (int i=0; i<10; i++)
            {
                if (d->lenseImage[i] != nullptr)
                {
                    d->lenseImage[i]->needUpdate = true;
                }
            }

            dta->needUpdate = false;
        }

        int i = (int) (abs(time-.5)*2*9);

        int q = (sz << 1) + 1;

        if (d->lenseImage[i] == nullptr) {

            d->lenseImage[i] = new Image(q, q);
        }

        Image *img = d->lenseImage[i];

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


void Mode_DepthEdit::applyLense(Forge *forge)
{
    Image *src = forge->src;

    int xx = forge->mouseX * src->Width;
    int yy = forge->mouseY * src->Height;

    Lense *lense = this->lense;

    int sz = lense->size * fmax(src->Width,src->Height);

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

                    float l = lense->get(lx, ly);

                    src->z[y][x] += l * .01 * dir;

                }
            }

        }
    }

}

bool Mode_DepthEdit::mouseMoveForge(Forge *forge, int x, int y)
{
    applyLense(forge);
    return true;
}

bool Mode_DepthEdit::mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    applyLense(forge);
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

void Mode_DepthEdit::setLense(Lense *lense)
{
    bool retain = this->lense != nullptr;

    double v, s;

    if (retain)
    {
        v = this->lense->intensity;
        s = this->lense->size;
    } else { v = .5; s = .1; }

    lense->setIntensity(v);
    lense->setSize(s);

    this->lense = lense;

    slideA->setV(s*2.0);
    slideB->setV(v/2.0);

}

LenseButton * Mode_DepthEdit::addLenseButton(int x, int y, LenseProc proc)
{
    Frame *f = new Frame(tools);

    f->xPos.set(x);
    f->yPos.set(y);

    f->width.setResp(Resp_Child);
    f->height.setResp(Resp_Child);

    f->backgroundResp = Resp_Child;

    LenseButton *bt = new LenseButton(f, proc);
    return bt;
}

void Mode_DepthEdit::sizeEntered(UI *sender, void *arg)
{
    previewLense = true;
}

void Mode_DepthEdit::sizeLeave(UI *sender, void *arg)
{
    previewLense = false;
}

void Mode_DepthEdit::sizeChanged(UI *sender, double v, void *arg)
{
    lense->setSize(v / 2.0);
}

void Mode_DepthEdit::intensityChanged(UI *sender, double v, void *arg)
{
    lense->setIntensity(v * 2.0);
}


LenseButton::LenseButton(UI *parent, LenseProc proc) : Button_Image(parent)
{
    this->lense = new Lense();
    this->lense->proc = proc;

    Image * src = new Image(128,128);

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

            double d = lense->get(xx,yy);

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

LenseButton::~LenseButton()
{
    delete lense;
}

bool LenseButton::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    bool rc = Button_Image::mouseButtonPress(x,y,button);

    MainUI *r = ((MainUI *) rootElement());
    r->mode_DepthEdit->setLense(lense);

    return rc;
}

float LenseButton::Sphere(float x, float y)
{
    float d = 1 - sqrtf(x*x+y*y);
    if (d<0) d = 0;

    return sin(d*M_PI/2);
}
float LenseButton::Circle(float x, float y)
{
    float d = 1 - sqrtf(x*x+y*y);
    return (d>0) ? 1.0 : 0.0;
}

float LenseButton::Pyramid(float x, float y)
{
    x = 1.0 - abs(x);
    y = 1.0 - abs(y);

    if (x<0 || y<0) return 0;

    return fmin(x,y);
}

float LenseButton::Square(float x, float y)
{
    if (x>=-1&&x<=1 && y>=-1&&y<=1) return 1;
    return 0;

}
