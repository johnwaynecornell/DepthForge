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

    //pathToolsCtl->open();

    forge = new Forge(this);

    forge->width.setResp(Resp_Parent);
    forge->height.setResp(Resp_Parent);
    forge->xPos.setResp(Resp_Parent);
    forge->yPos.setResp(Resp_Parent);

    mode_Current = nullptr;
    mode_DepthEdit = new Mode_DepthEdit(this);
    mode_Path = new Mode_Path(this);

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
        mode_Path->pathToolsCtl->open();
        finalLayout();
        firstDraw = false;
    }

    UI::draw(target, qImage);
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
