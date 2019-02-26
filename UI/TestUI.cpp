//
// Created by jwc on 2/20/19.
//

#include <cmath>
#include "TestUI.h"
#include <QApplication>

TestUI::TestUI(DepthForgeWin *win) : UI(nullptr)
{
    mouseX = 0;
    mouseY = 0;

    timeUp = clk.now();
}

bool TestUI::mouseMove(int x, int y)
{
    mouseX = x;
    mouseY = y;

    return true;
}

bool pixFunc(int index, double y, ARGB &p, float &z, void *arg)
{
    //y=-y;
    if (y>=0)
    {
        if (index == 0) p = {0xFF,0xFF,0x00,0x00};
        else if (index == 1) p = {0xFF,0x00,0xFF,0x00};
        else p = {0xFF,0xFF,0xFF,0xFF};
        z = 0;

        return true;
    }

    y = abs(y);

    if (y>=0 && y<10)
    {
        z = 1.0 - abs((y) / 10.0);

        unsigned char v = (unsigned char) (z * 0xFF);

        z = 1.0 - sin((1.0-z)*M_PI/2);

        z *= .125;

        p = {0xFF, v , v , 0};

        return true;
    }


    y -= 10;

    if (y>=0 && y<20)
    {
        z = 1.0 - abs((y-10) / 10.0);

        unsigned char v = (unsigned char) (z * 0xFF);
        z = 1.0 - sin((1.0-z)*M_PI/2);

        z *= .125;
        z += .125;

        p = {0xFF, v , v , v};

        return true;
    }

    y -= 20;

    if (y>=0 && y<20)
    {
        z = 1.0 - abs((y-10) / 10.0);

        unsigned char v = (unsigned char) (z * 0xFF);
        z = 1.0 - sin((1.0-z)*M_PI/2);

        z *= .125;

        z += .25;

        p = {0xFF, v , 0 , v};

        return true;
    }

    y -= 20;

    if (y>=0 && y<20)
    {
        z = 1.0 - abs((y-10) / 10.0);

        unsigned char v = (unsigned char) (z * 0xFF);
        z = 1.0 - sin((1.0-z)*M_PI/2);

        z *= .125;

        z += .375;

        p = {0xFF, v , (unsigned char)(v>>1) , (unsigned char)(v>>1)};

        return true;
    }


    return false;
}

void TestUI::draw(Image *target, QImage *qImage)
{
    target->FillRect(xReal, yReal, xReal+width.get(), yReal+height.get(),
            PixOp_SRC, {0xFF,0x00,0x00,0x00}, ZOp_SRC, 0);

    target->ClearPath();
    target->MoveTo(100,100);

    target->LineTo(200,150);

    target->LineTo(300,50);

    target->LineTo(400,100);
    target->LineTo(400,200);
    target->LineTo(200,200);
    target->LineTo(150,200);

    target->LineTo(125,225);


    target->LineTo(150,250);
    target->LineTo(200,250);
    target->LineTo(200,400);
    target->LineTo(100,400);
    target->LineTo(100,100);

    target->Circle(145,300, 40, true);

    target->Circle(500,200, 10, false);

    target->PreservePath();

    //target->FillPath(50,101,PixOp_SRC, {0xFF,0xFF,0x00,0xFF}, ZOp_SRC, 0);
    //target->PreservePath();

    target->DrawPath(PixOp_SRC, ZOp_SRC, 1, &pixFunc, nullptr);


/*
    int incount = 0;
    int outcount = 0;

    int in_a = 0;
    int in_b = 0;

    double oth;

    int inlines = 0;

    int lines = 0;

    bool clock=true;
    bool oldclock=true;

    int score = 0;

    for (int i = 1; i < target->pathIndex; i++) {
        double x1 = target->pathX[i - 1];
        double y1 = target->pathY[i - 1];

        double x2 = target->pathX[i];
        double y2 = target->pathY[i];

        double th = atan2(y2 - y1, x2 - x1);

        if (th<0) th+=M_PI*2;

        double rth;

        if (i != 1)
        {
            rth = th - oth;

            if (rth > M_PI) rth -= M_PI * 2;
            else if (rth < -M_PI) rth += M_PI * 2;

        } else rth = 0;

        oth = th;

        double xx = mouseX - x1;
        double yy = mouseY - y1;

        double sn = sin(-th);
        double cs = cos(-th);

        double _x = xx * cs - yy * sn;
        double _y = yy * cs + xx * sn;

        ARGB c;

        if ((_y >= 0)) { score++; } else {score--;}

            if (rth != 0 || i==1)
        {
            lines++;

            if ((rth<0))
            {
                clock = !clock;
            }

            if (clock) {
                c = {0xFF,0xFF,0x00,0x00};
                inlines++;

                if ((_y >= 0)) {
                    incount++;
                    in_a++;
                } else outcount++;
            } else
            {
                c = {0xFF,0x00,0x00,0xFF};

                if ((_y >= 0)) {
                    in_b++;
                    outcount--;
                } else incount--;
            }

        } else c = {0xFF,0xFF,0x00,0x00};

        target->Line((int)x1,(int)y1,(int)x2,(int)y2, PixOp_SRC, c,{0xFF,0xFF,0xFF,0xFF},ZOp_SRC, 0.0f, 0.0f);

    }

    char showBuf[1024];

    sprintf(showBuf, "score:=%d lines:=%d inlines:=%d in_a:=%d in_b:=%d", score, lines, inlines, in_a, in_b);

    QPainter *paint = new QPainter(qImage);

    paint->setPen(QColor(0xFF,0xFF,0xFF));
    paint->drawText(16,16, QApplication::tr(showBuf));

    paint->end();

    delete paint;
*/


    target->ClearPath();
}

double TestUI::getTimeInSeconds()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> time = clk.now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(time-timeUp).count()
           / 1000000000.0;
}
