//
// Created by jwc on 10/30/21.
//

#ifndef DEPTHFORGE_COMMON_H
#define DEPTHFORGE_COMMON_H

bool ForgeDrawPixFunc(Image *image, int x, int y, ARGB &p, float &z, void *arg);
void ancillary_press(void *_This, Button*element, bool pressed, void *arg);
void ancillary_update(void *_This, Button_Image *E, void *arg);

#endif //DEPTHFORGE_COMMON_H
