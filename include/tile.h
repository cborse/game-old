#ifndef TILE_H
#define TILE_H

#include "helpers/sprite.h"

typedef struct
{
    _Bool passable;
    Sprite *sprite;
} Tile;

void Tile_createTiles(void);

void Tile_destroyTiles(void);

Tile *Tile_get(unsigned int index);

#endif
