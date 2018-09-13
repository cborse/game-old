#ifndef MENU_H
#define MENU_H

#include "scenes/scene.h"
#include "helpers/sprite.h"
#include "helpers/frame.h"
#include "helpers/text.h"

typedef struct
{
    Scene scene;
    unsigned int index, maxIndex;
    Frame *frame;
    Sprite *cursor;
    Text *texts[8];
    Text *text_info[8];
    Rectangle *bg_info;
} Menu;

void Menu_init(void);

#endif
