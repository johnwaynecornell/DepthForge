//
// Created by jwc on 2/16/19.
//

#include "MainUI.h"
#include "Forge.h"
#include "math.h"

#include <QBitmap>

void MainUIMouseEnter(void *_This, UI *Elem, void *arg);
void MainUIMouseLeave(void *_This, UI *Elem, void *arg);

bool drawArrow(int index, double y, ARGB &p, float &z, void *arg)
{
    z = 0;

    y = abs(y);

    double q = 1.5;

    if (y>q)
    {
        p = {0,0,0,0};
    } else
    {
        ARGB a{0xFF,0xFF,0xFF,0xFF};
        ARGB b{0,0,0,0};

        p = a.interpolate(b, y / q);
    }
}

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

    //pathToolsCtl->open();

    forge = new Forge(this);

    forge->width.setResp(Resp_Parent);
    forge->height.setResp(Resp_Parent);
    forge->xPos.setResp(Resp_Parent);
    forge->yPos.setResp(Resp_Parent);

    mode_Current = nullptr;
    mode_DepthEdit = new Mode_DepthEdit(this);
    mode_Path = new Mode_Path(this);

    setMouseEnterProc(MainUIMouseEnter, this, nullptr);
    setMouseLeaveProc(MainUIMouseLeave, this, nullptr);

    ArrowCursor = new Image(16, 32);

    PathAdapter *pa = new PathAdapter();

    pa->outputMatrix = dMatrix2D::Scale(dPnt2D{12,12}) * dMatrix2D::Translate(dPnt2D{2,2});

    pa->MoveTo(dPnt2D{0, 0});
    pa->LineTo(dPnt2D{1, 1});
    pa->LineTo(dPnt2D{0.55, 1});
    pa->LineTo(dPnt2D{0.903553390593274, 1.85355339059327});
    pa->LineTo(dPnt2D{0.67175144212722, 1.94956890143242});
    pa->LineTo(dPnt2D{0.318198051533946, 1.09601551083915});
    pa->LineTo(dPnt2D{-1.11022302462516E-16, 1.41421356237309});
    pa->LineTo(dPnt2D{0, 0});

    pa->Apply(ArrowCursor);

    ArrowCursor->DrawPath(PixOp_SRC, ZOp_SRC, 1, drawArrow, nullptr);

    delete pa;

}

bool MainUI::mouseMove(int x, int y)
{
    mouseX = x;
    mouseY = y;

    return UI::mouseMove(x,y);
}

void MainUIMouseEnter(void *_This, UI *Elem, void *arg)
{
    MainUI *This = (MainUI *)_This;
    This->owner->setCursor(Qt::BlankCursor);
}
void MainUIMouseLeave(void *_This, UI *Elem, void *arg)
{
    MainUI *This = (MainUI *)_This;
    This->owner->setCursor(Qt::ArrowCursor);
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
    if (firstDraw)
    {
        mode_DepthEdit->basicToolsCtl->open();
        //mode_Path->pathToolsCtl->open();
        finalLayout();
        firstDraw = false;
    }

    UI::draw(target, qImage);

    //target->DrawImage(mouseX-2,mouseY-2, ArrowCursor->Width, ArrowCursor->Height, PixOp_SRC_ALPHA, ZOp_SRC_ADD, ArrowCursor, 0,0, ArrowCursor->Width,ArrowCursor->Height);
}

void MainUI::drawOverlay(Image *target, QImage *qImage)
{
    UI::drawOverlay(target, qImage);

    for (int y=0; y<ArrowCursor->Height; y++) {
        int yy = mouseY-2+y;

        for (int x = 0; x < ArrowCursor->Width; x++)
        {
            int xx = mouseX-2+x;

            if (target->Bound(xx,yy))
            {
                //int o = yy * target->Width + xx;
                target->pix[yy][xx] = target->pix[yy][xx].interpolate(ArrowCursor->pix[y][x], ArrowCursor->pix[y][x].a);
            }
        }
    }
}

bool MainUI::selfLayout()
{
    forge->height.set(height.get());
    forge->yPos.set(0);

    if (mode_Current != nullptr) mode_Current->selfLayout();

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

    if (mode_Current != nullptr) mode_Current->doLayout();

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
