#include <stdio.h>
#include <stdlib.h>
#include "helpers/sprite.h"
#include "common.h"

extern Common common;

Sprite *Sprite_create(int x, int y, const char *file)
{
    /* create new Sprite */
    Sprite *sprite = (Sprite *) malloc(sizeof(Sprite));

    if (sprite == NULL)
    {
        fprintf(stderr, "Sprite_create: failed to allocate memory!\n");
        exit(1);
    }

    /* save position */
    sprite->x = x;
    sprite->y = y;
    
    /* create sfTexture */
    sprite->sftexture = sfTexture_createFromFile(file, NULL);

    /* create sfSprite */
    sprite->sfsprite = sfSprite_create();

    /* set sfTexture to sfSprite */
    sfSprite_setTexture(sprite->sfsprite, sprite->sftexture, sfFalse);

    /* set position */
    sfVector2f pos = { x, y };
    sfSprite_setPosition(sprite->sfsprite, pos);

    /* return it */
    return sprite;
}

Sprite *Sprite_createSub(int x, int y, unsigned tx_x, unsigned tx_y, unsigned w, unsigned h, const char *file)
{
    /* create sprite */
    Sprite *sprite = (Sprite *) malloc(sizeof(Sprite));

    if (sprite == NULL)
    {
        fprintf(stderr, "Sprite_create: failed to create sprite!\n");
        exit(1);
    }

    /* create sfTexture */
    sfIntRect area = { tx_x, tx_y, w, h };
    sprite->sftexture = sfTexture_createFromFile(file, &area);

    /* create sfSprite */
    sprite->sfsprite = sfSprite_create();

    /* set texture */
    sfSprite_setTexture(sprite->sfsprite, sprite->sftexture, sfFalse);

    /* set position */
    sfVector2f pos = { x, y };
    sfSprite_setPosition(sprite->sfsprite, pos);

    /* return it */
    return sprite;
}

Sprite *Sprite_createSubExt(int x, int y, unsigned tx_x, unsigned tx_y, unsigned w, unsigned h, unsigned xtimes,
    unsigned ytimes, const char *file)
{
    /* create sprite */
    Sprite *sprite = Sprite_createSub(x, y, tx_x, tx_y, w, h, file);

    /* set texture rect */
    sfIntRect rect = { tx_x, tx_y, 8 * xtimes, 8 * ytimes };
    sfSprite_setTextureRect(sprite->sfsprite, rect);

    /* repeat it */
    sfTexture_setRepeated(sprite->sftexture, sfTrue);
    /* set position */
    sfVector2f pos = { x, y };
    sfSprite_setPosition(sprite->sfsprite, pos);

    /* return it */
    return sprite;
}

void Sprite_destroy(Sprite *sprite)
{
    /* destroy sfSprite and sfTexture */
    sfSprite_destroy(sprite->sfsprite);
    sfTexture_destroy(sprite->sftexture);

    /* free memory */
    free(sprite);
}

void Sprite_draw(Sprite *sprite)
{
    /* draw sfSprite */
    sfRenderWindow_drawSprite(common.window, sprite->sfsprite, NULL);
}

void Sprite_setPosition(Sprite *sprite, int x, int y)
{
    /* position vector */
    sfVector2f pos = { x, y };

    /* set new position */
    sfSprite_setPosition(sprite->sfsprite, pos);
}

void Sprite_setSubTexture(Sprite *sprite, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    /* texture rectangle */
    sfIntRect rect = { x, y, w, h };

    /* set texture rectangle */
    sfSprite_setTextureRect(sprite->sfsprite, rect);
}

void Sprite_rotate(Sprite *sprite, int angle)
{
    /* rotate sprite */
    sfSprite_rotate(sprite->sfsprite, angle);
}
