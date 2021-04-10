//
// Created by jwc on 4/9/21.
//

#include "ForgeContainer.h"

void setScrollX(void *_This, UI *Element, double V, void *arg);
void setScrollY(void *_This, UI *Element, double V, void *arg);
void setScrollZ(void *_This, UI *Element, double V, void *arg);

ForgeContainer::ForgeContainer(UI *parent) : Fixed(parent)
{
    forge = new Forge(this);

    forge->width.setResp(Resp_Parent);
    forge->height.setResp(Resp_Parent);
    forge->xPos.setResp(Resp_Parent);
    forge->yPos.setResp(Resp_Parent);

    scrollH = new Slider(this, nullptr, true, true);
    scrollV = new Slider(this, nullptr, true, false);
    scrollZ = new Slider(this, nullptr, false, false);

    scrollH->width.setResp(Resp_Parent);
    scrollH->height.setResp(Resp_Self);
    scrollH->xPos.setResp(Resp_Parent);
    scrollH->yPos.setResp(Resp_Parent);

    scrollV->width.setResp(Resp_Self);
    scrollV->height.setResp(Resp_Parent);
    scrollV->xPos.setResp(Resp_Parent);
    scrollV->yPos.setResp(Resp_Parent);

    scrollZ->width.setResp(Resp_Parent);
    scrollZ->height.setResp(Resp_Self);
    scrollZ->xPos.setResp(Resp_Parent);
    scrollZ->yPos.setResp(Resp_Parent);

    scrollH->height.set(32);
    scrollV->width.set(32);
    scrollZ->width.set(32);

    scrollH->setVCallvack(setScrollX, this, nullptr);
    scrollV->setVCallvack(setScrollY, this, nullptr);
    scrollZ->setVCallvack(setScrollZ, this, nullptr);
}

void setScrollX(void *_This, UI *Element, double V, void *arg)
{
    ((ForgeContainer *)_This)->forge->scrollX = (-V+1.0)/2.0;
}

void setScrollY(void *_This, UI *Element, double V, void *arg)
{
    ((ForgeContainer *)_This)->forge->scrollY = (-V+1.0)/2.0;
}

void setScrollZ(void *_This, UI *Element, double V, void *arg)
{
    ((ForgeContainer *)_This)->forge->scale = (float) pow(1.1, V*30);
}



//virtual void draw(Image *target, QImage *qImage);
//virtual void drawOverlay(Image *target, QImage *qImage);

bool ForgeContainer::selfLayout()
{
    UI::selfLayout();

    return true;
}

bool ForgeContainer::doLayout()
{
    int scrollZWidth = scrollZ->width.get();

    scrollH->xPos.set(scrollZWidth);
    scrollH->yPos.set(height.get() - scrollH->height.get());
    scrollH->width.set(width.get() - scrollV->width.get() - scrollZWidth);
    //scrollH->height.set(height.get());

    scrollV->xPos.set(width.get()-scrollV->width.get());
    scrollV->yPos.set(0);
    //scrollV->width.set(width.get());
    scrollV->height.set(height.get() - scrollH->height.get());


    scrollZ->xPos.set(0);
    scrollZ->yPos.set(0);
    scrollZ->height.set(height.get() - scrollH->height.get());

    forge->xPos.set(scrollZWidth);
    forge->yPos.set(0);
    forge->width.set(width.get() - scrollV->width.get() - scrollZWidth);
    forge->height.set(height.get() - scrollH->height.get());

    UI::doLayout();

    return true;
}