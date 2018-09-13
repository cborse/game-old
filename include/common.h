#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.h>

typedef struct
{
    sfRenderWindow *window;
    sfFont *font;
    sfClock *clock;
} Common;

void Common_init(void);

void Common_shutdown(void);

#endif
