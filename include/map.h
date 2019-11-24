#ifndef MAP_H
#define MAP_H

#define MAX_TILE_WIDTH 60
#define MAX_TILE_HEIGHT 18
#define MAX_NPCS 5

#include "tile.h"

typedef struct Map Map;

typedef struct Map
{
    unsigned int id;
    const char *name;
    unsigned int w, h;
    Map *north, *south, *west, *east;
    Tile *tiles[MAX_TILE_WIDTH][MAX_TILE_HEIGHT];
} Map;

void Map_createMaps(void);

void Map_draw(Map *map);

Map *Map_get(unsigned int index);

Tile *Map_getTile(Map *map, int i, int j);

#endif
