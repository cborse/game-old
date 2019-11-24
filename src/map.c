#include <stdio.h>
#include "map.h"
#include "player.h"

#define TREES       0
#define NEWBARK     1
#define ROUTE29     2
#define NUM_MAPS    3

Map maps[NUM_MAPS];
extern Player player;

static void createMap(unsigned int id, const char *name, unsigned int w, unsigned int h, unsigned int north,
    unsigned int south, unsigned int west, unsigned int east, const char *csvfile);


void Map_createMaps(void)
{
    /* create maps */
    createMap(TREES, "TREES", 2, 2, TREES, TREES, TREES, TREES, "assets/maps/trees.csv");
    createMap(NEWBARK, "NEW BARK TOWN", 24, 18, TREES, TREES, ROUTE29, TREES, "assets/maps/newbark.csv");
    createMap(ROUTE29, "ROUTE 29", 60, 18, TREES, TREES, TREES, NEWBARK, "assets/maps/route1.csv");

    /* NPCs */
    //maps[NEWBARK].npcs[0] = NPC_get(0);
}

void Map_draw(Map *map)
{
    /* top and bottom bounds */
    int top = player.y / 16 - 4;
    int bottom = top + 9;
    int left = player.x / 16 - 4;
    int right = left + 10;

    /* draw only visible tiles */
    for (int i = top; i <= bottom; i++)
    {
        for (int j = left; j <= right; j++)
        {
            Tile *tile = Map_getTile( map, i, j );
            Sprite_setPosition(tile->sprite, j * 16 - player.x + 64, i * 16 - player.y + 64);
            Sprite_draw(tile->sprite);
        }
    }
}

Map *Map_get(unsigned int index)
{
    return &maps[index];
}

Tile *Map_getTile(Map *map, int i, int j)
{
    /* tile is in the north map */
    if (i < 0)
    {
        return Map_getTile(map->north, map->north->h + i, j);
    }

    /* tile is in the south map */
    else if (i >= map->h)
    {
        return Map_getTile(map->south, i - map->h, j);
    }

    /* tile is in the west map */
    else if (j < 0)
    {
        return Map_getTile(map->west, i, map->west->w + j);
    }

    /* tile is in the east map */
    else if (j >= map->w)
    {
        return Map_getTile(map->east, i, j - map->w);
    }

    /* tile is in the current map */
    else
    {
        return map->tiles[j][i];
    }
}

static void createMap(unsigned int id, const char *name, unsigned int w, unsigned int h, unsigned int north,
    unsigned int south, unsigned int west, unsigned int east, const char *csvfile)
{
    /* set attributes */
    maps[id].id = id;
    maps[id].name = name;
    maps[id].w = w;
    maps[id].h = h;
    maps[id].north = &maps[north];
    maps[id].south = &maps[south];
    maps[id].west = &maps[west];
    maps[id].east = &maps[east];

    /* load CSV file */
    FILE *file = fopen(csvfile, "r");
    unsigned int tile;

    for (unsigned int i = 0; i < h; ++i)
    {
        for (unsigned int j = 0; j < w; ++j)
        {
            fscanf(file, "%d,", &tile);
            maps[id].tiles[j][i] = Tile_get(tile);
        }
    }

    /* close file */
    fclose(file);
}
