#include <stdio.h>
#include <stdlib.h>
#include "helpers/frame.h"
#include "options.h"

extern Options options;

Frame *Frame_create(int x, int y, unsigned int w, unsigned int h)
{
    /* create new Frame */
    Frame *frame = (Frame *) malloc(sizeof(Frame));

    if (frame == NULL)
    {
        fprintf(stderr, "Frame_create: failed to allocate memory!\n");
        exit(1);
    }

    /* create background rectangle */
    frame->bg = Rectangle_create(x, y, w, h);

    /* frame file based on options */
    char filepath[29];
    sprintf(filepath, "assets/textures/frames/%u.png", options.frametype);

    /* create sprites */
    frame->spTL = Sprite_createSub(x, y, 0, 0, 8, 8, filepath);
    frame->spTR = Sprite_createSub(x + w - 8, y, 0, 8, 8, 8, filepath);
    frame->spBL = Sprite_createSub(x, y + h - 8, 0, 16, 8, 8, filepath);
    frame->spBR = Sprite_createSub(x + w - 8, y + h - 8, 8, 16, 8, 8, filepath);
    frame->spT = Sprite_createSubExt(x + 8, y, 8, 0, 8, 8, (w - 16) / 8, 1, filepath);
    frame->spB = Sprite_createSubExt(x + 8, y + h - 8, 8, 0, 8, 8, (w - 16) / 8, 1, filepath);
    frame->spL = Sprite_createSubExt(x, y + 8, 8, 8, 8, 8, 1, (h - 16) / 8, filepath);
    frame->spR = Sprite_createSubExt(x + w - 8, y + 8, 8, 8, 8, 8, 1, (h - 16) / 8, filepath);

    /* return it */
    return frame;
}

void Frame_destroy(Frame *frame)
{
    /* destroy background rectangle */
    Rectangle_destroy(frame->bg);

    /* destroy sprites */
    Sprite_destroy(frame->spTL);
    Sprite_destroy(frame->spTR);
    Sprite_destroy(frame->spBL);
    Sprite_destroy(frame->spBR);
    Sprite_destroy(frame->spT);
    Sprite_destroy(frame->spB);
    Sprite_destroy(frame->spL);
    Sprite_destroy(frame->spR);

    /* free memory */
    free(frame);
}

void Frame_draw(Frame *frame)
{
    /* draw background rectangle */
    Rectangle_draw(frame->bg);

    /* draw sprites */
    Sprite_draw(frame->spTL);
    Sprite_draw(frame->spTR);
    Sprite_draw(frame->spBL);
    Sprite_draw(frame->spBR);
    Sprite_draw(frame->spT);
    Sprite_draw(frame->spB);
    Sprite_draw(frame->spL);
    Sprite_draw(frame->spR);
}
