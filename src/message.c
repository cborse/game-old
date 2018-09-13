#include "message.h"
#include "game.h"
#include "common.h"
#include "audio.h"
#include "options.h"
#include "helpers/frame.h"
#include "helpers/text.h"

#define MAX_LINES 5

typedef struct
{
    _Bool done, prompt, vprompt, anim;
    _Bool yesno, yesno_index;
    unsigned ch, line;
    Frame *frame;
    Frame *frame_yesno;
    Sprite *cursor;
    Sprite *cursor_yesno;
    Text *texts[MAX_LINES];
    Text *texts_yesno[2];
    sfClock *clock;
} Message;

static Message msg;
extern Game game;
extern Common common;
extern Options options;

static void enterLoop(void);
static void processEvent(void);
static void update(void);
static void draw(void);

void Message_start(void)
{
    /* initial attributes */
    msg.done = 0;
    msg.prompt = 0;
    msg.vprompt = 0;
    msg.anim = 0;
    msg.yesno = 0;
    msg.yesno_index = 1;
    msg.ch = 0;
    msg.line = 0;

    /* create frame */
    msg.frame = Frame_create(0, 96, 160, 48);

    /* create clock */
    msg.clock = sfClock_create();

    /* set everything else to NULL - will be created when/if needed */
    msg.frame_yesno = NULL;
    msg.cursor = NULL;
    msg.cursor_yesno = NULL;

    for (unsigned i = 0; i < MAX_LINES; i++)
    {
        msg.texts[i] = NULL;
    }

    msg.texts_yesno[0] = NULL;
    msg.texts_yesno[1] = NULL;
}

void Message_line(const char *string)
{
    /* reset attributes */
    msg.done = 0;
    msg.prompt = 0;
    msg.yesno = 0;
    msg.ch = 0;
    msg.line = 0;

    /* create text */
    if (msg.texts[0] != NULL)
    {
        Text_destroy(msg.texts[0]);
    }

    msg.texts[0] = Text_create(8, 111, string);

    /* enter loop */
    enterLoop();
}

void Message_next(const char *string)
{
    /* reset attributes */
    msg.done = 0;
    msg.prompt = 0;
    msg.yesno = 0;
    msg.ch = 0;
    msg.line = 1;

    /* create text */
    if (msg.texts[1] != NULL)
    {
        Text_destroy(msg.texts[1]);
    }

    msg.texts[1] = Text_create(8, 127, string);

    /* loop */
    enterLoop();
}

void Message_continue(const char *string)
{
    /* reset attributes */
    msg.done = 0;
    msg.prompt = 0;
    msg.yesno = 0;
    msg.ch = 0;
    msg.line++;

    /* scroll text */
    if (msg.texts[msg.line - 1] != NULL)
    {
        Text_setPosition(msg.texts[msg.line - 1], 8, 111);
    }

    /* create text */
    if (msg.texts[msg.line] != NULL)
    {
        Text_destroy(msg.texts[msg.line]);
    }

    msg.texts[msg.line] = Text_create(8, 127, string);

    /* loop */
    enterLoop();
}

_Bool Message_yesno(_Bool right_side)
{
    /* initial attributes */
    msg.done = 0;
    msg.prompt = 0;
    msg.yesno = 1;
    msg.yesno_index = 1;

    /* create yes/no frame */
    if (msg.frame_yesno != NULL)
    {
        Frame_destroy(msg.frame_yesno);
    }

    msg.frame_yesno = Frame_create(right_side * 112, 48, 48, 48);

    /* create yes/no cursor */
    if (msg.cursor_yesno != NULL)
    {
        Sprite_destroy(msg.cursor_yesno);
    }
    
    msg.cursor_yesno = Sprite_create(8 + right_side * 112, 63, "assets/textures/cursor.png");
    
    /* create yes/no texts */
    for (unsigned i = 0; i < 2; i++)
    {
        if (msg.texts_yesno[i] != NULL)
            Text_destroy(msg.texts_yesno[i]);
    }

    msg.texts_yesno[0] = Text_create(16 + right_side * 112, 63, "YES");
    msg.texts_yesno[1] = Text_create(16 + right_side * 112, 79, "NO");
    
    /* enter loop */
    enterLoop();

    /* return yes/no index */
    return msg.yesno_index;
}

void Message_prompt(_Bool visual)
{
    /* reset attributes */
    msg.done = 0;
    msg.prompt = 1;
    msg.yesno = 0;
    msg.vprompt = visual;

    /* create cursor if visual prompt */
    if (visual)
    {
        msg.cursor = Sprite_create(152, 134, "assets/textures/cursor.png");
        Sprite_rotate(msg.cursor, 90);
    }

    /* enter loop */
    enterLoop();
}

void Message_end(void)
{
    /* destroy text */
    for (unsigned i = 0; i < MAX_LINES; i++)
    {
        if (msg.texts[i] != NULL)
            Text_destroy(msg.texts[i]);
    }

    /* destroy text */
    for (unsigned i = 0; i < 2; i++)
    {
        if (msg.texts_yesno[i] != NULL)
            Text_destroy(msg.texts_yesno[i]);
    }

    /* destroy clock */
    sfClock_destroy(msg.clock);

    /* destroy frames */
    Frame_destroy(msg.frame);

    if (msg.frame_yesno != NULL)
        Frame_destroy(msg.frame_yesno);

    /* destroy cursors */
    if (msg.cursor != NULL)
        Sprite_destroy(msg.cursor);

    if (msg.cursor_yesno != NULL)
        Sprite_destroy(msg.cursor_yesno);
}

static void enterLoop(void)
{
    /* simulate game loop */
    while (!msg.done && game.running)
    {
        processEvent();
        update();
        draw();
        Audio_update();
    }
}

static void processEvent(void)
{
    /* get event */
    sfEvent event;

    /* poll */
    while (sfRenderWindow_pollEvent(common.window, &event))
    {
        /* window closed */
        if (event.type == sfEvtClosed)
        {
            game.running = 0;
        }

        /* key pressed */
        else if (event.type == sfEvtKeyPressed)
        {
            /* which key? */
            switch (event.key.code)
            {
                /* UP arrow */
                case sfKeyUp:

                    /* yes/no box */
                    if (msg.yesno)
                    {
                        msg.yesno_index = !msg.yesno_index;
                        Sprite_setPosition(msg.cursor_yesno, msg.cursor_yesno->x, 79 - msg.yesno_index * 16);
                    }
                    break;

                /* DOWN arrow */
                case sfKeyDown:

                    /* yes/no box */
                    if (msg.yesno)
                    {
                        msg.yesno_index = !msg.yesno_index;
                        Sprite_setPosition(msg.cursor_yesno, msg.cursor_yesno->x, 79 - msg.yesno_index * 16);
                    }
                    break;

                /* C key */
                case sfKeyC:

                    /* not a prompt and not a yes/no box */
                    if (!msg.prompt && !msg.yesno)
                    {
                        /* increase character to text length */
                        msg.ch = Text_length(msg.texts[msg.line]) - 1;
                    }

                    /* prompt or yes/no */
                    else
                    {
                        Audio_playSound(SND_SELECT);
                        msg.done = 1;
                    }
                    break;

                /* X key */
                case sfKeyX:

                    /* (same as C) not a prompt and not a yes/no box */
                    if (!msg.prompt && !msg.yesno)
                    {
                        /* increase character to text length */
                        msg.ch = Text_length(msg.texts[msg.line]) - 1;
                    }

                    /* prompt or yes/no */
                    else
                    {
                        Audio_playSound(SND_SELECT);
                        msg.yesno_index = 0;
                        msg.done = 1;
                    }

                /* other */
                default:
                    break;
            }
        }
    }
}

static void update(void)
{
    /* not a prompt and not a yes/no */
    if (!msg.prompt && !msg.yesno)
    {
        /* not done writing */
        if (msg.ch < Text_length(msg.texts[msg.line]))
        {
            /* get clock time */
            sfTime time = sfClock_getElapsedTime(msg.clock);

            /* time threshold passed */
            if (sfTime_asMilliseconds(time) > 90 / (options.textspeed + 1))
            {
                /* restart clock */
                sfClock_restart(msg.clock);

                /* increment character */
                msg.ch++;
            }
        }

        /* done writing */
        else
        {
            /* done */
            msg.done = 1;
        }
    }

    /* visual prompt */
    else if (msg.prompt && msg.vprompt)
    {
        /* get clock time */
        sfTime time = sfClock_getElapsedTime(msg.clock);

        /* time threshold passed */
        if (sfTime_asMilliseconds(time) > 250)
        {
            /* restart clock */
            sfClock_restart(msg.clock);

            /* change animation frame */
            msg.anim = !msg.anim;

            /* change position */
            Sprite_setPosition(msg.cursor, 152, 134 + msg.anim * 4);
        }
    }
}

static void draw(void)
{
    /* clear window to white */
    sfRenderWindow_clear(common.window, sfWhite);

    /* draw scenes */
    for (unsigned i = 0; i < game.scenes_size; i ++)
    {
        game.scenes[i]->draw();
    }

    /* draw frame */
    Frame_draw(msg.frame);

    /* draw text */
    if (msg.line == 0)
    {
        Text_drawSub(msg.texts[msg.line], msg.ch);
    }

    else
    {
        Text_draw(msg.texts[msg.line - 1]);
        Text_drawSub(msg.texts[msg.line], msg.ch);
    }

    /* draw yes/no choices */
    if (msg.yesno)
    {
        Frame_draw(msg.frame_yesno);
        Sprite_draw(msg.cursor_yesno);
        Text_draw(msg.texts_yesno[0]);
        Text_draw(msg.texts_yesno[1]);
    }

    /* draw prompt animation */
    if (msg.prompt && msg.vprompt)
    {
        Sprite_draw(msg.cursor);
    }

    /* redraw */
    sfRenderWindow_display(common.window);
}
