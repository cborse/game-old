#ifndef FRAME_H
#define FRAME_H

#include "helpers/sprite.h"
#include "helpers/rectangle.h"

typedef struct
{
    Rectangle *bg;
    Sprite *spTL;
    Sprite *spTR;
    Sprite *spBL;
    Sprite *spBR;
    Sprite *spT;
    Sprite *spB;
    Sprite *spL;
    Sprite *spR;
} Frame;

Frame *Frame_create(int x, int y, unsigned int w, unsigned int h);

void Frame_destroy(Frame *frame);

void Frame_draw(Frame *frame);

#endif
