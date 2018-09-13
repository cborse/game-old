#include "tile.h"
  
#define TILESET_WIDTH 20
#define TILESET_HEIGHT 22

static Tile tiles[TILESET_WIDTH * TILESET_HEIGHT];

void Tile_createTiles(void)
{
    /* load tiles */
    for (unsigned int i = 0; i < TILESET_WIDTH * TILESET_HEIGHT; i++)
    {
        /* default is NOT passable */
        tiles[i].passable = 0;

        /* rectangle for subtexture */
        sfIntRect rect = { (i % TILESET_WIDTH) * 16, (i / TILESET_WIDTH) * 16, 16, 16 };

        /* tileset position */
        int x = (i % TILESET_WIDTH) * 16;
        int y = (i / TILESET_WIDTH) * 16;

        /* create sprite */
        tiles[i].sprite = Sprite_createSub(0, 0, x, y, 16, 16, "assets/textures/tileset.png");
    }

    /* set passable tiles */
    tiles[0].passable = 1;
    tiles[10].passable = 1;
    tiles[11].passable = 1;
    tiles[20].passable = 1;
    tiles[40].passable = 1;
    tiles[43].passable = 1;
    tiles[60].passable = 1;
    tiles[66].passable = 1;
    tiles[80].passable = 1;
}

void Tile_destroyTiles(void)
{
    /* destroy sprites */
    for (unsigned int i = 0; i < TILESET_WIDTH * TILESET_HEIGHT; ++i)
    {
        Sprite_destroy(tiles[i].sprite);
    }
}

Tile *Tile_get(unsigned int index)
{
    return &tiles[index];
}
