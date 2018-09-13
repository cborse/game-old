#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "scenes/scene.h"
#include "helpers/sprite.h"
#include "helpers/frame.h"
#include "helpers/text.h"

typedef struct
{
    Scene scene;
    unsigned index, maxIndex;
    Sprite *cursor;
    Frame *frame;
    Text *texts[3];
} MainMenu;

void MainMenu_init(void);

#endif
