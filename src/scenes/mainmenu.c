#include "scenes/mainmenu.h"
#include "game.h"
#include "audio.h"
#include "save.h"
#include "scenes/optionmenu.h"
#include "scenes/overworld.h"

MainMenu mainmenu;
extern Save save;
extern OptionMenu optionmenu;
extern Overworld overworld;

static void shutdown(void);
static void resume(void);
static void processEvent(sfEvent *event);
static void update(void);
static void draw(void);

void MainMenu_init(void)
{
    /* define function pointers */
    mainmenu.scene.shutdown = &shutdown;
    mainmenu.scene.resume = &resume;
    mainmenu.scene.processEvent = &processEvent;
    mainmenu.scene.update = &update;
    mainmenu.scene.draw = &draw;

    /* set initial index */
    mainmenu.index = 0;
    
    /* create cursor */
    mainmenu.cursor = Sprite_create(8, 15, "assets/textures/cursor.png");

    /* max index, texts and frame size depend on save file */
    if (save.status == 1)
    {
        /* set maximum index */
        mainmenu.maxIndex = 2;

        /* create frame */
        mainmenu.frame = Frame_create(0, 0, 88, 64);
    
        /* create texts */
        mainmenu.texts[0] = Text_create(16, 15, "CONTINUE");
        mainmenu.texts[1] = Text_create(16, 31, "NEW GAME");
        mainmenu.texts[2] = Text_create(16, 47, "OPTION");
    }

    else if (save.status == 0)
    {
        /* set maximum index */
        mainmenu.maxIndex = 1;

        /* create frame */
        mainmenu.frame = Frame_create(0, 0, 88, 48);

        /* create texts */
        mainmenu.texts[0] = Text_create(16, 15, "NEW GAME");
        mainmenu.texts[1] = Text_create(16, 31, "OPTION");
    }
}

static void shutdown(void)
{
}

static void resume(void)
{
    /* restart menu */
    Game_changeScene((Scene *) &mainmenu);
}

static void processEvent(sfEvent *event)
{
    /* which key? */
    switch (event->key.code)
    {
        /* UP arrow */
        case sfKeyUp:
            
            /* decrement index or loop around */
            (mainmenu.index > 0) ? (mainmenu.index--) : (mainmenu.index = mainmenu.maxIndex);
            
            /* update cursor position */
            Sprite_setPosition(mainmenu.cursor, 8, 15 + 16 * mainmenu.index);
            break;

        /* DOWN arrow */
        case sfKeyDown:

            /* increment index or loop around */
            (mainmenu.index < mainmenu.maxIndex) ? (mainmenu.index++) : (mainmenu.index = 0);
            
            /* update cursor position */
            Sprite_setPosition(mainmenu.cursor, 8, 15 + 16 * mainmenu.index);
            break;

        /* C key */
        case sfKeyC:
            
            /* play sound effect */
            Audio_playSound(SND_SELECT);

            /* which index? */
            switch (mainmenu.index)
            {
                case 0:
                    
                    /* continue */
                    if (save.status == 1)
                    {
                        Game_changeScene((Scene *) &overworld);
                    }

                    /* new game */
                    else if (save.status == 0)
                    {
                    }
                    break;

                case 1:

                    /* new game */
                    if (save.status == 1)
                    {
                    }

                    /* option */
                    else if (save.status == 0)
                    {
                        Game_pushScene((Scene *) &optionmenu);
                    }
                    break;

                case 2:
                    
                    /* option */
                    Game_pushScene((Scene *) &optionmenu);
                    break;
            }
            break;
        
        /* other */
        default:
            break;
    }
}

static void update(void)
{
}

static void draw(void)
{
    /* draw frame */
    Frame_draw(mainmenu.frame);
    
    /* draw cursor */
    Sprite_draw(mainmenu.cursor);

    /* draw texts */
    for (unsigned i = 0; i <= mainmenu.maxIndex; i++)
    {
        Text_draw(mainmenu.texts[i]);
    }
}
