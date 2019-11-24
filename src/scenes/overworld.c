#include "scenes/overworld.h"
#include "game.h"
#include "audio.h"
#include "save.h"
#include "tile.h"
#include "map.h"
#include "player.h"
#include "scenes/menu.h"

Overworld overworld;
extern Save save;
extern Player player;
extern Menu menu;

static void shutdown(void);
static void resume(void);
static void processEvent(sfEvent *event);
static void update(void);
static void draw(void);

void Overworld_init(void)
{
    /* define function pointers */
    overworld.scene.shutdown = &shutdown;
    overworld.scene.resume = &resume;
    overworld.scene.processEvent = &processEvent;
    overworld.scene.update = &update;
    overworld.scene.draw = &draw;

    /* create tiles */
    Tile_createTiles();

    /* create NPCs */
    //NPC_createNPCs();

    /* create maps */
    Map_createMaps();

    /* set map */
    overworld.map = Map_get(save.map);

    /* play music */
    Audio_playMusicFade(overworld.map->id);

    /* init player */
    Player_init();
}

static void shutdown(void)
{
    /* destroy tiles */
    Tile_destroyTiles();

    /* destroy NPCs */
    //NPC_destroyNPCs();

    /* shut down player */
    Player_shutdown();
}

static void resume(void)
{
}

static void processEvent(sfEvent *event)
{
    /* make sure player isn't moving */
    if (!player.moving)
    {
        /* which key? */
        switch (event->key.code)
        {
            /* ENTER key */
            case sfKeyReturn:

                /* push menu */
                Game_pushScene((Scene *) &menu);
                break;

            /* other */
            default:
                break;
        }
    }
}

static void update(void)
{
    /* update player */
    Player_update();
}

static void draw(void)
{
    /* draw map */
    Map_draw(overworld.map);

    /* draw player */
    Player_draw();
}
