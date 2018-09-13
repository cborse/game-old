#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "common.h"
#include "save.h"
#include "scenes/mainmenu.h"
#include "scenes/optionmenu.h"
#include "scenes/overworld.h"
#include "scenes/menu.h"
#include "scenes/playerinfo.h"

Game game;
extern Common common;
extern Save save;
extern MainMenu mainmenu;
extern OptionMenu optionmenu;
extern Overworld overworld;
extern Menu menu;
extern PlayerInfo playerinfo;


void Game_init(void)
{
    /* set scenes size to 0 initially */
    game.scenes_size = 0;

    /* define scene's init pointers */
    mainmenu.scene.init = &MainMenu_init;
    optionmenu.scene.init = &OptionMenu_init;
    overworld.scene.init = &Overworld_init;
    menu.scene.init = &Menu_init;
    playerinfo.scene.init = &PlayerInfo_init;

    /* push first scene */
    Game_pushScene((Scene *) &mainmenu);

    /* set game to running */
    game.running = 1;
}

void Game_shutdown(void)
{
    /* clear scenes */
    Game_clearScenes();
}

void Game_processEvent(void)
{
    /* event */
    sfEvent event;

    /* poll */
    while (sfRenderWindow_pollEvent(common.window, &event))
    {
        /* window closed */
        if (event.type == sfEvtClosed)
        {
            game.running = 0;
        }

        /* send event to scene if it's a key press */
        else if (event.type == sfEvtKeyPressed && game.scenes_size > 0)
        {
            game.scenes[game.scenes_size - 1]->processEvent(&event);
        }
    }
}

void Game_update(void)
{
    /* update scene */
    if (game.scenes_size > 0)
    {
        game.scenes[game.scenes_size - 1]->update();
    }

    /* update clock */
    sfTime time = sfClock_getElapsedTime(common.clock);

    if (sfTime_asSeconds(time) >= 60)
    {
        sfClock_restart(common.clock);
        save.time++;
    }
}

void Game_draw(void)
{
    /* clear window to white */
    sfRenderWindow_clear(common.window, sfWhite);

    /* draw scenes */
    for (unsigned i = 0; i < game.scenes_size; i++)
    {
        game.scenes[i]->draw();
    }

    /* redraw window */
    sfRenderWindow_display(common.window);
}

void Game_pushScene(Scene *scene)
{
    /* make sure there's room */
    if (game.scenes_size < MAX_SCENES)
    {
        game.scenes[game.scenes_size] = scene;
        game.scenes[game.scenes_size]->init();
        game.scenes_size++;
    }

    else
    {
        fprintf(stderr, "Game_pushScene: there's no room!\n");
        exit(1);
    }
}

void Game_popScene(void)
{
    /* make sure there's a scene to pop */
    if (game.scenes_size > 0)
    {
        game.scenes_size--;
        game.scenes[game.scenes_size]->shutdown();

        /* resume previous scene if it exists */
        if (game.scenes_size > 0)
        {
            game.scenes[game.scenes_size - 1]->resume();
        }
    }

    else
    {
        fprintf(stderr, "Game_popScene: scenes is empty!\n");
        exit(1);
    }
}

void Game_changeScene(Scene *scene)
{
    /* pop then push scene */
    Game_popScene();
    Game_pushScene(scene);
}

void Game_clearScenes(void)
{
    /* pop all scenes */
    while (game.scenes_size > 0)
    {
        Game_popScene();
    }
}
