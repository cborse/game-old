#include <stdio.h>
#include <stdlib.h>
#include "helpers/rectangle.h"
#include "common.h"

extern Common common;

Rectangle *Rectangle_create(int x, int y, unsigned int w, unsigned int h)
{
    /* create new Rectangle */
    Rectangle *rect = (Rectangle *) malloc(sizeof(Rectangle));

    if (rect == NULL)
    {
        fprintf(stderr, "Rectangle_create: failed to allocate memory!\n");
        exit(1);
    }

    /* create sfRectangleShape */
    rect->sfrect = sfRectangleShape_create();

    /* position and size */
    sfVector2f pos = { x, y };
    sfVector2f size = { w, h };

    /* set position and size */
    sfRectangleShape_setPosition(rect->sfrect, pos);
    sfRectangleShape_setSize(rect->sfrect, size);

    /* return it */
    return rect;
}

void Rectangle_destroy(Rectangle *rect)
{
    /* destroy sfRectangleShape */
    sfRectangleShape_destroy(rect->sfrect);

    /* free memory */
    free(rect);
}

void Rectangle_draw(Rectangle *rect)
{
    /* draw sfRectangleShape */
    sfRenderWindow_drawRectangleShape(common.window, rect->sfrect, NULL);
}
