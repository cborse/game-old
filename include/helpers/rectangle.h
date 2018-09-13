#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SFML/Graphics.h>

typedef struct
{
    sfRectangleShape *sfrect;
} Rectangle;

Rectangle *Rectangle_create(int x, int y, unsigned int w, unsigned int h);

void Rectangle_destroy(Rectangle *rect);

void Rectangle_draw(Rectangle *rect);

#endif
