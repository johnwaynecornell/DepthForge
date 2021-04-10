//
// Created by jwc on 4/9/21.
//

#ifndef DEPTHFORGE_FORGECONTAINER_H
#define DEPTHFORGE_FORGECONTAINER_H

#include "UI.h"
#include "Slider.h"
#include "Forge.h"

class ForgeContainer : public Fixed{
public:

    Slider *scrollH;
    Slider *scrollV;
    Slider *scrollZ;
    Forge *forge;

    ForgeContainer(UI *parent);

    //virtual void draw(Image *target, QImage *qImage);
    //virtual void drawOverlay(Image *target, QImage *qImage);

    virtual bool selfLayout();
    virtual bool doLayout();

};


#endif //DEPTHFORGE_FORGECONTAINER_H
