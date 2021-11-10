//
// Created by jwc on 10/30/21.
//

#include "UI.h"
#include "Mode.h"
#include "common.h"
#include "Forge.h"

void ancillary_press(void *_This, Button*element, bool pressed, void *arg) {
    Mode *T = (Mode *) _This;

    if (pressed) {
        T->mainUI->forgeContainer->forge->swapViews = ! T->mainUI->forgeContainer->forge->swapViews;
    }
}

void ancillary_update(void *_This, Button_Image *E, void *arg)
{
    Mode *T = (Mode *) _This;

    Image *src;

    if (T->mainUI->forgeContainer->forge->swapViews)
    {
        src = T->mainUI->forgeContainer->forge->src;
    } else
    {
        src = T->mainUI->forgeContainer->forge->greyMap;
    }

    float scale = E->src_noToggle->Width / (float) src->Width;

    E->src_noToggle->DrawImage(0,0,E->src_noToggle->Width, E->src_noToggle->Height,0,0,E->src_noToggle->Width, E->src_noToggle->Height,
                               PixOp_SRC, ZOp_SRC, src, 0,0, src->Width, src->Height);

    E->src_noToggle->FillRect(0, 0, E->src_noToggle->Width, E->src_noToggle->Height, PixOp_SRC, ZOp_SRC, ForgeDrawPixFunc, &scale);
}
