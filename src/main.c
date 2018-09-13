#include "game.h"
#include "common.h"
#include "audio.h"
#include "options.h"
#include "save.h"

extern Game game;

int main(void)
{
    /* read data */
    Options_read();
    Save_read();
    
    /* init components */
    Common_init();
    Game_init();
    Audio_init();

    /* game loop */
    while (game.running)
    {
        Game_processEvent();
        Game_update();
        Game_draw();
        Audio_update();
    }

    /* shut down components */
    Audio_shutdown();
    Game_shutdown();
    Common_shutdown();

    return 0;
}
