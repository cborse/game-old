#include "common.h"

#define NATIVE_WIDTH 160
#define NATIVE_HEIGHT 144
#define TITLE "Game"
#define FLAGS sfResize|sfClose

Common common;

void Common_init(void)
{
    /* video mode */
    sfVideoMode mode = { NATIVE_WIDTH, NATIVE_HEIGHT, 32 };

    /* create window */
    common.window = sfRenderWindow_create(mode, TITLE, FLAGS, NULL);

    /* set framerate limit to 60 */
    sfRenderWindow_setFramerateLimit(common.window, 60);

    /* set key repeat disabled */
    sfRenderWindow_setKeyRepeatEnabled(common.window, sfFalse);
    
    /* create font */
    common.font = sfFont_createFromFile("assets/fonts/font.ttf");

    /* create clock */
    common.clock = sfClock_create();
}

void Common_shutdown(void)
{
    /* destroy clock */
    sfClock_destroy(common.clock);

    /* destroy font */
    sfFont_destroy(common.font);

    /* destroy window */
    sfRenderWindow_destroy(common.window);
}
