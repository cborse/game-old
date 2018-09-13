#include <stdio.h>
#include "scenes/playerinfo.h"
#include "common.h"
#include "save.h"

PlayerInfo playerinfo;
extern Common common;
extern Save save;

static void shutdown(void);
static void resume(void);
static void processEvent(sfEvent *event);
static void update(void);
static void draw(void); 

void PlayerInfo_init(void)
{
    /* define function pointers */
    playerinfo.scene.shutdown = &shutdown;
    playerinfo.scene.resume = &resume;
    playerinfo.scene.processEvent = &processEvent;
    playerinfo.scene.update = &update;
    playerinfo.scene.draw = &draw;

    /* create frame */
    playerinfo.frame = Frame_create(32, 0, 128, 80);

    /* create texts */
    playerinfo.texts[0] = Text_create(40, 15, "PLAYER");
    playerinfo.texts[1] = Text_create(40, 31, "BADGES");
    playerinfo.texts[2] = Text_create(40, 47, "POKeDEX");
    playerinfo.texts[3] = Text_create(40, 63, "TIME");

    /* create player text */
    playerinfo.text_info[0] = Text_create(96, 15, save.name);
    
    /* create badges text */
    char badges[3];
    sprintf(badges, "%2u", save.badges);
    badges[2] = '\0';
    playerinfo.text_info[1] = Text_create(136, 31, badges);
    
    /* create pokedex text */
    char pokedex[4];
    sprintf(pokedex, "%3u", save.pokedex);
    pokedex[3] = '\0';
    playerinfo.text_info[2] = Text_create(128, 47, pokedex);

    /* determine play hours and minutes */
    unsigned int hours = save.time / 60;
    unsigned int mins = save.time - hours * 60;
    char game_time[7];
    sprintf(game_time, "%3u:%02u", hours, mins);
    game_time[6] = '\0';

    /* create play time text */
    playerinfo.text_info[3] = Text_create(104, 63, game_time);
}

static void shutdown(void)
{
}

static void resume(void)
{
}

static void processEvent(sfEvent *event)
{
}

static void update(void)
{
}

static void draw(void)
{
    /* draw frame */
    Frame_draw(playerinfo.frame);

    /* draw texts */
    Text_draw(playerinfo.texts[0]);
    Text_draw(playerinfo.texts[1]);
    Text_draw(playerinfo.texts[3]);

    /* draw info texts */
    Text_draw(playerinfo.text_info[0]);
    Text_draw(playerinfo.text_info[1]);
    Text_draw(playerinfo.text_info[3]);

    /* only show pokedex if the player has a pokemon */
    if (save.pokedex > 0)
    {
        Text_draw(playerinfo.texts[2]);
        Text_draw(playerinfo.text_info[2]);
    }
}
