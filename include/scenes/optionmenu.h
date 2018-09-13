#ifndef OPTION_MENU_H
#define OPTION_MENU_H

#include "scenes/scene.h"
#include "helpers/sprite.h"
#include "helpers/frame.h"
#include "helpers/text.h"

typedef struct
{
    Scene scene;
    unsigned index, maxIndex;
    unsigned subIndex[2], maxSubIndex[2];
    Frame *frame;
    Sprite *cursor;
    Text *texts[3];
    Text *textspeeds[3];
    Text *frametypes[9];
} OptionMenu;

void OptionMenu_init(void);

#endif
