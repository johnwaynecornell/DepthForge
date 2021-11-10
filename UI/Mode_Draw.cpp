//
// Created by jwc on 4/2/19.
//

#include "Mode_Draw.h"
#include "Forge.h"

Mode_Draw::Mode_Draw(MainUI *mainUI) : Mode(mainUI)
{
    previewBrush = false;

    tabCtl = new DepthForgeTabCtl(mainUI->tabs, QApplication::tr("Brush"));

    tabCtl->width.setResp(Resp_Child);
    tabCtl->height.setResp(Resp_Parent);
    tabCtl->xPos.setResp(Resp_Self);
    tabCtl->yPos.setResp(Resp_Self);

    tabCtl->xPos.set(0);
    tabCtl->yPos.set(0);
    tabCtl->width.set(1);

    tabCtl->myMode = this;

    tabCtl->tabPosition.set(mainUI->tabs->_tabPosition);
    mainUI->tabs->_tabPosition += 64 + 9;

    //tabCtl->open();

    basicTools = new Fixed(tabCtl);
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

    ancillaryFrame = new Frame(basicTools);

    ancillaryFrame->xPos.setResp(Resp_Self);
    ancillaryFrame->yPos.setResp(Resp_Parent);

    ancillaryFrame->width.setResp(Resp_Child);
    ancillaryFrame->height.setResp(Resp_Child);

    ancillaryFrame->xPos.set(0);
    ancillaryFrame->yPos.set(0);


    ancillaryFrame->backgroundResp = Resp_Child;


    ancillaryView = new Button_Image(ancillaryFrame);

    ancillaryView->width.setResp(Resp_Self);
    ancillaryView->height.setResp(Resp_Self);
    ancillaryView->xPos.setResp(Resp_Self);
    ancillaryView->yPos.setResp(Resp_Self);

    ancillaryView->height.set((lenssz+ border)*2);
    ancillaryView->width.set((lenssz+ border)*2);
    ancillaryView->xPos.set(0);
    ancillaryView->yPos.set(0);

    ancillaryImage = new Image(32, 32);
    ancillaryView->setSource(ancillaryImage, false);

    ancillaryView->onPress = {this,ancillaryView, &ancillary_press, nullptr};
    ancillaryView->onUpdateSrc = { this, ancillaryView, &ancillary_update, nullptr};

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


    slideB = new Slider(bottom, "Depth", false, false);
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
        void (Mode_Draw::*a)(UI *, void *);
        void (*b)(void *, UI *, void *);
    } test;

    test.a = &Mode_Draw::sizeEntered;

    slideA->setMouseEnterProc(test.b, this, nullptr);
    slideB->setMouseEnterProc(test.b, this, nullptr);

    test.a = &Mode_Draw::sizeLeave;

    slideA->setMouseLeaveProc(test.b, this, nullptr);
    slideB->setMouseLeaveProc(test.b, this, nullptr);

    union
    {
        void (Mode_Draw::*a)(UI *, double, void *);
        void (*b)(void *, UI *, double, void *);
    } testb;

    testb.a = &Mode_Draw::sizeChanged;

    slideA->setVCallvack(testb.b, this, nullptr);

    testb.a = &Mode_Draw::intensityChanged;

    slideB->setVCallvack(testb.b, this, nullptr);

    lens = nullptr;

    Brush *l = addBrushButton(0,0, BrushButton::Sphere, lenssz)->lens;
    addBrushButton(0,lenssz+ border, BrushButton::SphereC, lenssz);
    addBrushButton(0,(lenssz+ border)*2, BrushButton::Circle, lenssz);

    addBrushButton(lenssz+ border,0, BrushButton::Pyramid, lenssz);
    addBrushButton(lenssz+ border,lenssz+ border, BrushButton::PyramidC, lenssz);
    addBrushButton(lenssz+ border,(lenssz+ border)*2, BrushButton::Square, lenssz);

    setBrush(l);
}

struct BrushData
{
    float **map;
    Image *lensImage[10];
};


void Mode_Draw::drawForge(Forge *forge, Image *target, QImage *qImage)
{
    if (forge->hasMouse || previewBrush)
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

        Brush *lens = this->lens;

        int sz;// = (int)(lens->size * fmax(forge->src->Width,forge->src->Height)*forge->scale);

        if (forge->src->Height > forge->src->Width)
        {
            sz = (int) (lens->size * forge->src->Height * forge->_h / forge->_srcH);
        } else
        {
            sz = (int) (lens->size * forge->src->Width * forge->_w / forge->_srcW);
        }

        //int sz = (int) (lens->size * fmax(forge->_w,forge->_h)*forge->scale);

        Brush::Cache * dta;

        BrushData *d;

        if (!lens->getData(0, sz, &dta))
        {
            if (dta->dta != nullptr)
            {
                d = (BrushData *)dta->dta;

                lens->freeMap(d->map, dta->s);

                for (int i =0; i<10; i++) {
                    if (d->lensImage[i] != nullptr) {
                        delete d->lensImage[i];
                        d->lensImage[i] = nullptr;
                    }
                }
            } else
            {
                dta->dta = d = new BrushData();
                for (int i =0; i<10; i++)
                {
                    d->lensImage[i] = nullptr;
                }
            }

            d->map = lens->map(sz);
            dta->s = sz;

            dta->needUpdate = true;
        }

        d = ((BrushData *)dta->dta);

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

            //dta->needUpdate = false;
        }

        int i = (int) (abs(time-.5)*2*9);

        int q = (sz << 1) + 1;

        if (d->lensImage[i] == nullptr) {

            d->lensImage[i] = new Image(q, q);
        }

        Image *img = d->lensImage[i];

        int _x1 = forge->xReal;
        int _y1 = forge->yReal;

        int _w1 = forge->width.get();
        int _h1 = forge->height.get();

        //if (img->needUpdate)
        {

            for (int yp = -sz; yp <= sz; yp++) {
                int y = sz + yp;

                for (int xp = -sz; xp <= sz; xp++) {
                    int x = sz + xp;

                    float l = map[yp][xp];

                    //if (l>1.0) l = 1.0;

                    l *= 0x80;

                    if (l < 0) l = 0;
                    if (l > 0xFF) l = 0xFF;

                    unsigned char g = (unsigned char) (i * 0xFF / 9);

                    ARGB p = {(unsigned char) (l), 0xFF, g, 0xFF};

                    img->pix[y][x] = p;

                    l = lens->proc(xp / (double) sz, yp / (double) sz);

                    if (l != 0) {
                        //l = lens->get(xp / (double) sz, yp / (double) sz);
                        img->z[y][x] = (l*.05+lens->intensity-.5f)*2.0f;

                        int _x = xx + xp;
                        int _y = yy + yp;

                        if (_y - _y1 >=0 && _y - _y1 < _h1 && _x - _x1 >=0 && _x - _x1 < _w1)
                        {
                            ARGB p2 = target->pix[_y][_x];
                            p = p2.interpolate(p, p.a);
                            p.a = p2.a;

                            target->pix[_y][_x] = p;
                            target->z[_y][_x] = (l*.05+lens->intensity-.5f)*2.0f;

                        }
                    }

                }
            }
            img->needUpdate = false;
        }

/*

        target->DrawImage(_x1, _y1, _w1, _h1,
                          xx-sz, yy-sz, q, q, PixOp_SRC_ALPHA, ZOp_SRC,
                          img, 0,0, q, q);
*/
    }

}


void Mode_Draw::applyBrush(Forge *forge)
{
    Image *src = forge->src;

    int xx = forge->mouseX * forge->src->Width;
    int yy = forge->mouseY * forge->src->Height;

    Brush *lens= this->lens;

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

                    float l = lens->proc(lx,ly);
                    if (l != 0) {
                        l = (l*.05+lens->intensity-.5f)*2.0f;

                        src->z[y][x] = l;
                    }

                }
            }

        }
    }

}

bool Mode_Draw::mouseMoveForge(Forge *forge, int x, int y)
{
    applyBrush(forge);
    return true;
}

bool Mode_Draw::mouseButtonPressForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    applyBrush(forge);
    return true;
}

bool Mode_Draw::mouseButtonReleaseForge(Forge *forge, int x, int y, Qt::MouseButton button)
{
    return true;
}

void Mode_Draw::selfLayout()
{
    tabCtl->height.set(mainUI->height.get());
}

void Mode_Draw::doLayout()
{
    resizeAncillary(basicTools->width.get()-6);

    ancillaryFrame->xPos.set(0);
    ancillaryFrame->yPos.set(toolFrame->height.get());

    bottomFrame->xPos.set(0);
    bottomFrame->yPos.set(basicTools->height.get()-bottomFrame->height.get());
}

void Mode_Draw::setBrush(Brush *lens)
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

BrushButton * Mode_Draw::addBrushButton(int x, int y, BrushProc proc, int lenssz)
{
    Frame *f = new Frame(tools);

    f->xPos.set(x);
    f->yPos.set(y);

    f->width.setResp(Resp_Child);
    f->height.setResp(Resp_Child);

    f->backgroundResp = Resp_Child;

    BrushButton *bt = new BrushButton(f, proc, lenssz);
    return bt;
}

void Mode_Draw::sizeEntered(UI *sender, void *arg)
{
    previewBrush = true;
}

void Mode_Draw::sizeLeave(UI *sender, void *arg)
{
    previewBrush = false;
}

void Mode_Draw::sizeChanged(UI *sender, double v, void *arg)
{
    lens->setSize(v / 2.0);
}

void Mode_Draw::intensityChanged(UI *sender, double v, void *arg)
{
    lens->setIntensity(v);
}


BrushButton::BrushButton(UI *parent, BrushProc proc, int lenssz) : Button_Image(parent)
{
    this->lens = new Brush();
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

            double d = lens->proc(xx,yy);

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

BrushButton::~BrushButton()
{
    delete lens;
}

bool BrushButton::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    bool rc = Button_Image::mouseButtonPress(x,y,button);

    MainUI *r = ((MainUI *) rootElement());
    r->mode_Draw->setBrush(lens);

    return rc;
}

float BrushButton::Sphere(float x, float y)
{
    float d = 1 - sqrtf(x*x+y*y);
    if (d<0) d = 0;

    return sin(d*M_PI/2);
}

float BrushButton::SphereC(float x, float y)
{
    float d = 1 - sqrtf(x*x+y*y);
    if (d<0) return 0.0f;//d = 0;

    return 1.0f - sin(d*M_PI/2);
}



float BrushButton::Circle(float x, float y)
{
    float d = 1 - sqrtf(x*x+y*y);
    return (d>0) ? 1.0 : 0.0;
}

float BrushButton::Pyramid(float x, float y)
{
    x = 1.0 - abs(x);
    y = 1.0 - abs(y);

    if (x<0 || y<0) return 0;

    return fmin(x,y);
}

float BrushButton::PyramidC(float x, float y)
{
    x = 1.0 - abs(x);
    y = 1.0 - abs(y);

    if (x<0 || y<0) return 0;

    return 1.0-fmin(x,y);
}

float BrushButton::Square(float x, float y)
{
    if (x>=-1&&x<=1 && y>=-1&&y<=1) return 1;
    return 0;

}
