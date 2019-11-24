#include "scenes/optionmenu.h"
#include "game.h"
#include "audio.h"
#include "options.h"

OptionMenu optionmenu;
extern Options options;

static void shutdown(void);
static void resume(void);
static void processEvent(sfEvent *event);
static void update(void);
static void draw(void);

void OptionMenu_init(void)
{
    /* define function pointers */
    optionmenu.scene.shutdown = &shutdown;
    optionmenu.scene.resume = &resume;
    optionmenu.scene.processEvent = &processEvent;
    optionmenu.scene.update = &update;
    optionmenu.scene.draw = &draw;

    /* set index and maximum index */
    optionmenu.index = 0;
    optionmenu.maxIndex = 2;

    /* set text speed index and maximum index */
    optionmenu.subIndex[0] = options.textspeed;
    optionmenu.maxSubIndex[0] = 2;

    /* set frame type index and maximum index */
    optionmenu.subIndex[1] = options.frametype;
    optionmenu.maxSubIndex[1] = 8;

    /* create frame */
    optionmenu.frame = Frame_create( 0, 0, 160, 144 );

    /* create cursor */
    optionmenu.cursor = Sprite_create( 8, 15, "assets/textures/cursor.png" );

    /* create main texts */
    optionmenu.texts[0] = Text_create( 16, 15, "TEXT SPEED" );
    optionmenu.texts[1] = Text_create( 16, 31, "FRAME" );
    optionmenu.texts[2] = Text_create( 16, 47, "CONFIRM" );

    /* create text speed texts */
    optionmenu.textspeeds[0] = Text_create(80, 23, ":SLOW");
    optionmenu.textspeeds[1] = Text_create(80, 23, ":MID");
    optionmenu.textspeeds[2] = Text_create(80, 23, ":FAST");

    /* create frame type texts */
    optionmenu.frametypes[0] = Text_create(80, 39, ":TYPE 1");
    optionmenu.frametypes[1] = Text_create(80, 39, ":TYPE 2");
    optionmenu.frametypes[2] = Text_create(80, 39, ":TYPE 3");
    optionmenu.frametypes[3] = Text_create(80, 39, ":TYPE 4");
    optionmenu.frametypes[4] = Text_create(80, 39, ":TYPE 5");
    optionmenu.frametypes[5] = Text_create(80, 39, ":TYPE 6");
    optionmenu.frametypes[6] = Text_create(80, 39, ":TYPE 7");
    optionmenu.frametypes[7] = Text_create(80, 39, ":TYPE 8");
    optionmenu.frametypes[8] = Text_create(80, 39, ":TYPE 9");
}

static void shutdown(void)
{
    /* destroy main texts */
    for (unsigned i = 0; i <= optionmenu.maxIndex; i++)
    {
        Text_destroy(optionmenu.texts[i]);
    }

    /* destroy text speed texts */
    for (unsigned i = 0; i <= optionmenu.maxSubIndex[0]; i++)
    {
        Text_destroy(optionmenu.textspeeds[i]);
    }

    /* destroy frame type texts */
    for (unsigned i = 0; i <= optionmenu.maxSubIndex[1]; i++)
    {
        Text_destroy(optionmenu.frametypes[i]);
    }

    /* destroy cursor */
    Sprite_destroy(optionmenu.cursor);

    /* destroy frame */
    Frame_destroy(optionmenu.frame);
}

static void resume(void)
{
}

static void processEvent(sfEvent *event)
{
    /* which key? */
    switch (event->key.code)
    {
        /* UP arrow */
        case sfKeyUp:

            /* decrement index or loop around */
            (optionmenu.index > 0) ? (optionmenu.index--) : (optionmenu.index = optionmenu.maxIndex);

            /* update cursor position */
            Sprite_setPosition(optionmenu.cursor, 8, 15 + 16 * optionmenu.index);
            break;

        /* DOWN arrow */
        case sfKeyDown:

            /* increment index or loop around */
            (optionmenu.index < optionmenu.maxIndex) ? (optionmenu.index++) : (optionmenu.index = 0);

            /* update cursor position */
            Sprite_setPosition(optionmenu.cursor, 8, 15 + 16 * optionmenu.index);
            break;

        /* LEFT arrow */
        case sfKeyLeft:

            /* decrement sub index or loop around */
            if (optionmenu.subIndex[optionmenu.index] > 0)
            {
                optionmenu.subIndex[optionmenu.index]--;
            }

            else
            {
                optionmenu.subIndex[optionmenu.index] = optionmenu.maxSubIndex[optionmenu.index];
            }

            break;

        /* RIGHT arrow */
        case sfKeyRight:

            /* increment sub index or loop around */
            if (optionmenu.subIndex[optionmenu.index] < optionmenu.maxSubIndex[optionmenu.index])
            {
                optionmenu.subIndex[optionmenu.index]++;
            }

            else
            {
                optionmenu.subIndex[optionmenu.index] = 0;
            }

            break;

        /* C key */
        case sfKeyC:

            /* confirm */
            if (optionmenu.index == 2)
            {
                /* play sound effect */
                Audio_playSound(SND_SAVE);

                /* write options */
                Options_write();

                /* pop option menu */
                Game_popScene();
            }
            break;

        /* X key */
        case sfKeyX:

            /* play sound effect */
            Audio_playSound(SND_SAVE);

            /* write options */
            Options_write();

            /* pop option menu */
            Game_popScene();

        /* other */
        default:
            break;
    }
}

static void update(void)
{
    /* update options */
    options.textspeed = optionmenu.subIndex[0];
    options.frametype = optionmenu.subIndex[1];

    /* recreate frame */
    Frame_destroy(optionmenu.frame);
    optionmenu.frame = Frame_create(0, 0, 160, 144);
}

static void draw(void)
{
    /* draw frame */
    Frame_draw(optionmenu.frame);

    /* draw cursor */
    Sprite_draw(optionmenu.cursor);

    /* draw main texts */
    for (unsigned i = 0; i <= optionmenu.maxIndex; i++)
    {
        Text_draw(optionmenu.texts[i]);
    }

    /* draw text speed text */
    Text_draw(optionmenu.textspeeds[optionmenu.subIndex[0]]);

    /* draw frame type text */
    Text_draw(optionmenu.frametypes[optionmenu.subIndex[1]]);
}
