#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.h>

typedef struct
{
    const char *string;
    sfText *sftext;
} Text;

Text *Text_create(int x, int y, const char *string);

void Text_destroy(Text *text);

void Text_draw(Text *text);

void Text_drawSub(Text *text, unsigned int upto);

void Text_setPosition(Text *text, int x, int y);

unsigned int Text_length(Text *text);

#endif
