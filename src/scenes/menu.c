#include "scenes/menu.h"
#include "game.h"
#include "audio.h"
#include "common.h"
#include "save.h"
#include "player.h"
#include "message.h"
#include "scenes/optionmenu.h"
#include "scenes/overworld.h"
#include "scenes/playerinfo.h"

Menu menu;
extern Common common;
extern Save save;
extern Player player;
extern OptionMenu optionmenu;
extern Overworld overworld;
extern PlayerInfo playerinfo;

static void shutdown(void);
static void resume(void);
static void processEvent(sfEvent *event);
static void update(void);
static void draw(void);
static void trySaving(_Bool overwrite);

void Menu_init(void)
{
    /* define function pointers */
    menu.scene.shutdown = &shutdown;
    menu.scene.resume = &resume;
    menu.scene.processEvent = &processEvent;
    menu.scene.update = &update;
    menu.scene.draw = &draw;

    /* set initial index and maxIndex */
    menu.index = 0;
    menu.maxIndex = 7;

    /* create frame */
    menu.frame = Frame_create(80, 0, 80, 144);

    /* create cursor */
    menu.cursor = Sprite_create(88, 15, "assets/textures/cursor.png");

    /* create texts */
    menu.texts[0] = Text_create(96, 15, "POKeDEX");
    menu.texts[1] = Text_create(96, 31, "POKeMON");
    menu.texts[2] = Text_create(96, 47, "PACK");
    menu.texts[3] = Text_create(96, 63, "GEAR");
    menu.texts[4] = Text_create(96, 79, save.name);
    menu.texts[5] = Text_create(96, 95, "SAVE");
    menu.texts[6] = Text_create(96, 111, "OPTIONS");
    menu.texts[7] = Text_create(96, 127, "EXIT");

    /* create info background */
    menu.bg_info = Rectangle_create(0, 104, 80, 40);

    /* create info texts */
    menu.text_info[0] = Text_create(0, 111, "POKeMON\n\ndatabase");
    menu.text_info[1] = Text_create(0, 111, "POKeMON\n\nstatus");
    menu.text_info[2] = Text_create(0, 111, "Contains\n\nitems");
    menu.text_info[3] = Text_create(0, 111, "Trainer's\n\nkey device");
    menu.text_info[4] = Text_create(0, 111, "Your own\n\nstatus");
    menu.text_info[5] = Text_create(0, 111, "Save your\n\nprogress");
    menu.text_info[6] = Text_create(0, 111, "Change\n\nsettings");
    menu.text_info[7] = Text_create(0, 111, "Close this\n\nmenu");
}

static void shutdown(void)
{
    /* destroy info background */
    Rectangle_destroy(menu.bg_info);

    /* destroy texts */
    for (unsigned int i = 0; i <= menu.maxIndex; i++)
    {
        Text_destroy(menu.texts[i]);
    }

    /* destroy info texts */
    for (unsigned int i = 0; i <= menu.maxIndex; i++)
    {
        Text_destroy(menu.text_info[i]);
    }

    /* destroy cursor */
    Sprite_destroy(menu.cursor);

    /* destroy frame */
    Frame_destroy(menu.frame);
}

static void resume(void)
{
    /* recreate frame */
    Frame_destroy(menu.frame);
    menu.frame = Frame_create(80, 0, 80, 144);
}

static void processEvent(sfEvent *event)
{
    /* which key? */
    switch (event->key.code)
    {
        /* UP arrow */
        case sfKeyUp:

            /* decrement index or loop around */
            (menu.index > 0) ? (menu.index--) : (menu.index = menu.maxIndex);

            /* update cursor position */
            Sprite_setPosition(menu.cursor, 88, 15 + 16 * menu.index);
            break;

        /* DOWN arrow */
        case sfKeyDown:

            /* increment index or loop around */
            (menu.index < menu.maxIndex) ? (menu.index++) : (menu.index = 0);

            /* update cursor position */
            Sprite_setPosition(menu.cursor, 88, 15 + 16 * menu.index);
            break;

        /* C key */
        case sfKeyC:
            
            /* play sound effect */
            Audio_playSound(SND_SELECT);
            
            /* which index? */
            switch (menu.index)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    break;
                
                /* save */
                case 5:
                    /* warn about overwriting */
                    if (save.status != 0)
                    {
                        trySaving(1);
                    }

                    else
                    {
                        trySaving(0);
                    }
                    break;
            
                /* option */
                case 6:

                    /* push option menu */
                    Game_pushScene((Scene *) &optionmenu);
                    break;

                /* exit */
                case 7:
                
                    /* close menu */
                    Game_popScene();
                break;
            }
            break;
        
        /* X/Enter key */
        case sfKeyX:
        case sfKeyReturn:
            
            /* close menu */
            Game_popScene();
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
    Frame_draw(menu.frame);

    /* draw cursor */
    Sprite_draw(menu.cursor);

    /* draw texts */
    for (unsigned int i = 0; i <= menu.maxIndex; i++)
    {
        Text_draw(menu.texts[i]);
    }

    /* draw info background */
    Rectangle_draw(menu.bg_info);

    /* draw info text */
    Text_draw(menu.text_info[menu.index]);
}

static void trySaving(_Bool overwrite)
{
    /* push player info */
    Game_pushScene((Scene *) &playerinfo);

    /* start message */
    Message_start();
    Message_line("Would you like to");
    Message_next("save the game?");
    
    /* yes */
    if (Message_yesno(0))
    {
        /* save file exists */
        if (save.status != 0)
        {
            Message_line("There is already a");
            Message_next("save file. Is it");
            Message_prompt(1);
            Message_continue("OK to overwrite?");

            /* yes */
            if (Message_yesno(0))
            {
                Message_line("SAVING. DON'T TURN");
                Message_next("OFF THE POWER.");

                /* save */
                save.x = player.x;
                save.y = player.y;
                save.map = overworld.map->id;
                Save_write();

                Message_line(save.name);
                Message_next("saved the game.");

                /* play sound effect */
                Audio_playSound(SND_SAVE);
            }
        }
    }

    Message_end();

    /* pop player info */
    Game_popScene();
}
