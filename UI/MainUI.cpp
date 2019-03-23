//
// Created by jwc on 2/16/19.
//

#include "MainUI.h"
#include "Forge.h"
#include "math.h"

MainUI::MainUI(DepthForgeWin *main) : Fixed(nullptr)
{
    timeUp = clk.now();

    owner = main;
    width.setResp(Resp_Self);
    height.setResp(Resp_Self);
    xPos.setResp(Resp_Self);
    yPos.setResp(Resp_Self);

    tabs = new TabFolder(this);

    tabs->width.setResp(Resp_Child);
    tabs->height.setResp(Resp_Parent);
    tabs->xPos.setResp(Resp_Self);
    tabs->yPos.setResp(Resp_Self);

    tabs->xPos.set(0);
    tabs->yPos.set(0);

    basicToolsCtl = new TabCtl(tabs);

    basicToolsCtl->width.setResp(Resp_Child);
    basicToolsCtl->height.setResp(Resp_Parent);
    basicToolsCtl->xPos.setResp(Resp_Self);
    basicToolsCtl->yPos.setResp(Resp_Self);

    basicToolsCtl->xPos.set(0);
    basicToolsCtl->yPos.set(0);

    //basicToolsCtl->open();

    basicTools = new Fixed(basicToolsCtl);
    basicTools->width.setResp(Resp_Child);
    basicTools->height.setResp(Resp_Parent);
    basicTools->xPos.setResp(Resp_Self);
    basicTools->yPos.setResp(Resp_Self);

    basicTools->xPos.set(0);
    basicTools->yPos.set(0);

    pathToolsCtl = new TabCtl(tabs);

    pathToolsCtl->width.setResp(Resp_Child);
    pathToolsCtl->height.setResp(Resp_Parent);
    pathToolsCtl->xPos.setResp(Resp_Self);
    pathToolsCtl->yPos.setResp(Resp_Self);

    pathToolsCtl->xPos.set(0);
    pathToolsCtl->yPos.set(0);

    pathToolsCtl->tabPosition.set(basicToolsCtl->tabPosition.get() + 64 +9);

    pathTools = new Fixed(pathToolsCtl);
    pathTools->width.setResp(Resp_Self);
    pathTools->height.setResp(Resp_Parent);
    pathTools->xPos.setResp(Resp_Self);
    pathTools->yPos.setResp(Resp_Self);

    pathTools->xPos.set(0);
    pathTools->yPos.set(0);

    pathTools->width.set(256+12);

    //pathToolsCtl->open();

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

    lense = nullptr;

    Lense *l = addLenseButton(0,0, LenseButton::Sphere)->lense;

    addLenseButton(128+6,0, LenseButton::Circle);
    addLenseButton(0,128+6, LenseButton::Pyramid);
    addLenseButton(128+6,128+6, LenseButton::Square);

    forge = new Forge(this);

    forge->width.setResp(Resp_Parent);
    forge->height.setResp(Resp_Parent);
    forge->xPos.setResp(Resp_Parent);
    forge->yPos.setResp(Resp_Parent);

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
        void (MainUI::*a)(UI *, void *);
        void (*b)(void *, UI *, void *);
    } test;

    test.a = &MainUI::sizeEntered;

    slideA->setMouseEnterProc(test.b, this, nullptr);
    slideB->setMouseEnterProc(test.b, this, nullptr);

    test.a = &MainUI::sizeLeave;

    slideA->setMouseLeaveProc(test.b, this, nullptr);
    slideB->setMouseLeaveProc(test.b, this, nullptr);

    union
    {
        void (MainUI::*a)(UI *, double, void *);
        void (*b)(void *, UI *, double, void *);
    } testb;

    testb.a = &MainUI::sizeChanged;
    
    slideA->setVCallvack(testb.b, this, nullptr);

    testb.a = &MainUI::intensityChanged;

    slideB->setVCallvack(testb.b, this, nullptr);

    setLense(l);

}

double MainUI::getTimeInSeconds()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> time = clk.now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(time-timeUp).count()
                / 1000000000.0;
}


/*
void cycle(void *_This, TabCtl *ctl, TabCtl::State state, void *arg)
{
    if (state == TabCtl::State_open) ctl->close();
    else if (state == TabCtl::State_closed) ctl->open();
}*/

void MainUI::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);

    if (firstDraw)
    {
//        basicToolsCtl->setStateChangeCallback(nullptr, cycle, nullptr);
        //basicToolsCtl->open();
        firstDraw = false;
    }
}

bool MainUI::selfLayout()
{
    forge->height.set(height.get());
    forge->yPos.set(0);

    basicToolsCtl->height.set(height.get());

    Fixed::selfLayout();

    return true;
}

bool MainUI::doLayout()
{

    Fixed::doLayout();

    int x = tabs->width.get();
    int w = width.get()-x;


    forge->xPos.set(x);
    forge->width.set(w);

    bottomFrame->xPos.set(0);
    bottomFrame->yPos.set(basicTools->height.get()-bottomFrame->height.get());

    return true;
}

void MainUI::giveMouse(UI *element)
{
    owner->giveMouse(element);
}

void MainUI::freeMouse(UI *element)
{
    owner->freeMouse(element);
}

void MainUI::sizeEntered(UI *sender, void *arg)
{
    forge->previewLense = true;
}

void MainUI::sizeLeave(UI *sender, void *arg)
{
    forge->previewLense = false;
}

void MainUI::sizeChanged(UI *sender, double v, void *arg)
{
    lense->setSize(v / 2.0);
}

void MainUI::intensityChanged(UI *sender, double v, void *arg)
{
    lense->setIntensity(v * 2.0);
}


void MainUI::setLense(Lense *lense)
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

LenseButton * MainUI::addLenseButton(int x, int y, LenseProc proc)
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

LenseButton::LenseButton(UI *parent, LenseProc proc) : Button_Image(parent)
{
    this->lense = new Lense();
    this->lense->proc = proc;

    src = new Image(128,128);

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
    delete src;
    delete lense;
}

bool LenseButton::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    bool rc = Button_Image::mouseButtonPress(x,y,button);

    MainUI *r = ((MainUI *) rootElement());
    r->setLense(lense);

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
