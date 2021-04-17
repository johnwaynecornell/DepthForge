//
// Created by jwc on 4/2/19.
//

#include "Mode.h"
#include "MainUI.h"


Mode::Mode(MainUI *mainUI)
{
    this->mainUI = mainUI;
    ancillaryImage = nullptr;
}

void Mode::updateSrc(Forge *forge)
{
}

void Mode::resizeAncillary(int width)
{
    int height = width * mainUI->forgeContainer->forge->src->Height / mainUI->forgeContainer->forge->src->Width;

    if (ancillaryImage->Width != width || ancillaryImage->Height != height)
    {
        if (ancillaryImage != nullptr) delete ancillaryImage;

        ancillaryImage = new Image(width, height);
        ancillaryView->setSource(ancillaryImage, false);
    }
}