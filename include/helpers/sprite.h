#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.h>

typedef struct
{
    int x, y;
    sfTexture *sftexture;
    sfSprite *sfsprite;
} Sprite;

Sprite *Sprite_create(int x, int y, const char *file);

Sprite *Sprite_createSub(int x, int y, unsigned tx_x, unsigned tx_y, unsigned w, unsigned h, const char *file);

Sprite *Sprite_createSubExt(int x, int y, unsigned tx_x, unsigned tx_y, unsigned w, unsigned h, unsigned xtimes,
    unsigned ytimes, const char *file);

void Sprite_destroy(Sprite *sprite);

void Sprite_draw(Sprite *sprite);

void Sprite_setPosition(Sprite *sprite, int x, int y);

void Sprite_setSubTexture(Sprite *sprite, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

void Sprite_rotate(Sprite *sprite, int angle);

#endif
