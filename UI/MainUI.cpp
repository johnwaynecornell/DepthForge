//
// Created by jwc on 2/16/19.
//

#include "MainUI.h"
#include "Forge.h"
#include "math.h"

MainUI::MainUI(DepthForgeWin *main) : Fixed(nullptr)
{
    owner = main;
    width.setResp(Resp_Self);
    height.setResp(Resp_Self);
    xPos.setResp(Resp_Self);
    yPos.setResp(Resp_Self);

    toolFrame = new Frame(this);
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

    lense = addLenseButton(0,0, LenseButton::Sphere)->lense;
    addLenseButton(128+6,0, LenseButton::Circle);
    addLenseButton(0,128+6, LenseButton::Pyramid);
    addLenseButton(128+6,128+6, LenseButton::Square);

    forge = new Forge(this);

    forge->width.setResp(Resp_Parent);
    forge->height.setResp(Resp_Parent);
    forge->xPos.setResp(Resp_Parent);
    forge->yPos.setResp(Resp_Parent);

    bottomFrame = new Frame(this);
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

}

void MainUI::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);
}

bool MainUI::selfLayout()
{
    toolFrame->height.set(height.get());

    Fixed::selfLayout();
}

bool MainUI::doLayout()
{
    Fixed::doLayout();

    int x = toolFrame->width.get();
    int w = width.get()-x;

    forge->xPos.set(x);
    forge->yPos.set(0);

    forge->width.set(w);

    forge->height.set(height.get());

    bottomFrame->xPos.set(0);
    bottomFrame->yPos.set(height.get()-bottomFrame->height.get());
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

bool LenseButton::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    bool rc = Button_Image::mouseButtonPress(x,y,button);

    ((MainUI *) rootElement())->lense = lense;

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
