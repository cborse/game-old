#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers/text.h"
#include "common.h"

extern Common common;

Text *Text_create(int x, int y, const char *string)
{
    /* create new Text */
    Text *text = (Text *) malloc(sizeof(Text));

    if (text == NULL)
    {
        fprintf(stderr, "Text_create: failed to allocate memory!\n");
        exit(1);
    }

    /* save string */
    text->string = string;
    
    /* create sfText */
    text->sftext = sfText_create();

    /* scale and position */
    sfVector2f scale = { 0.1, 0.1 };
    sfVector2f pos = { x, y };

    /* set sfText attributes */
    sfText_setFont(text->sftext, common.font);
    sfText_setCharacterSize(text->sftext, 80);
    sfText_setScale(text->sftext, scale);
    sfText_setFillColor(text->sftext, sfBlack);
    sfText_setPosition(text->sftext, pos);
    sfText_setString(text->sftext, string);
    
    /* return it */
    return text;
}

void Text_destroy(Text *text)
{
    /* destroy sfText */
    sfText_destroy(text->sftext);

    /* free memory */
    free(text);
}

void Text_draw(Text *text)
{
    /* draw sfText */
    sfRenderWindow_drawText(common.window, text->sftext, NULL);
}

void Text_drawSub(Text *text, unsigned int upto)
{
    /* substring */
    char substring[upto + 1];
    strncpy(substring, text->string, upto);
    substring[upto] = '\0';

    /* get position of text */
    sfVector2f pos = sfText_getPosition(text->sftext);

    /* create new text */
    Text *new_text = Text_create(pos.x, pos.y, substring);

    /* draw it */
    Text_draw(new_text);

    /* destroy it */
    Text_destroy(new_text);
}

void Text_setPosition(Text *text, int x, int y)
{
    /* new position */
    sfVector2f pos = { x, y };

    /* change position */
    sfText_setPosition(text->sftext, pos);
}

unsigned int Text_length(Text *text)
{
    return strlen(text->string);
}
