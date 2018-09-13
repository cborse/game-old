#include "player.h"
#include "audio.h"
#include "save.h"
#include "map.h"
#include "scenes/overworld.h"

Player player;
extern Save save;
extern Overworld overworld;

static void tryMoving(unsigned int dir);
static _Bool checkCollision(unsigned int dir);
static void checkBoundary(unsigned int dir);

enum { UP, DOWN, LEFT, RIGHT };

void Player_init(void)
{
    /* initial attributes */
    player.moving = 0;
    player.x = save.x;
    player.y = save.y;
    player.vx = 0;
    player.vy = 0;
    player.dir = DOWN;
    player.frame = 0;
    player.counter = 0;

    /* create sprite */
    player.sprite = Sprite_create(64, 60, "assets/textures/player.png");

    /* set sub texture */
    Sprite_setSubTexture(player.sprite, player.frame * 16, player.dir * 16, 16, 16);
}

void Player_shutdown(void)
{
    /* destroy sprite */
    Sprite_destroy(player.sprite);
}

void Player_update(void)
{
    /* player is moving */
    if (player.moving)
    {
        /* in last movement frame */
        if (player.counter > 15)
        {
            player.counter = 0;
            player.moving = 0;
            player.vx = 0;
            player.vy = 0;
        }

        else if (player.counter > 7)
        {
            player.counter++;
            if (player.frame == 1)
                player.frame = 2;
            else if (player.frame == 3)
                player.frame = 0;
        }

        else
        {
            player.counter++;
            if (player.frame == 0)
                player.frame = 1;
            else if (player.frame == 2)
                player.frame = 3;
        }

        player.x += player.vx;
        player.y += player.vy;

        /* update subtexture */
        Sprite_setSubTexture(player.sprite, player.frame * 16, player.dir * 16, 16, 16);
    }

    /* player is not moving */
    else
    {
        /* UP arrow is pressed */
        if (sfKeyboard_isKeyPressed(sfKeyUp))
        {
            tryMoving(UP);
        }

        /* DOWN arrow is pressed */
        else if (sfKeyboard_isKeyPressed(sfKeyDown))
        {
            tryMoving(DOWN);
        }

        /* LEFT arrow is pressed */
        else if (sfKeyboard_isKeyPressed(sfKeyLeft))
        {
            tryMoving(LEFT);
        }

        /* RIGHT arrow is pressed */
        else if (sfKeyboard_isKeyPressed(sfKeyRight))
        {
            tryMoving(RIGHT);
        }
    }
}

void Player_draw(void)
{
    /* draw sprite */
    Sprite_draw(player.sprite);
}

static void tryMoving(unsigned int dir)
{
    /* set player to moving */
    player.moving = 1;

    /* change direction */
    player.dir = dir;

    /* try moving up */
    if (dir == UP && checkCollision(UP))
    {
        /* check if player crossed map boundary */
        checkBoundary(UP);

        /* set speed */
        player.vx = 0;
        player.vy = -1;
    }

    /* try moving down */
    else if (dir == DOWN && checkCollision(DOWN))
    {
        /* check if player crossed map boundary */
        checkBoundary(DOWN);

        /* set speed */
        player.vx = 0;
        player.vy = 1;
    }

    /* try moving left */
    else if (dir == LEFT && checkCollision(LEFT))
    {
        /* check if player crossed map boundary */
        checkBoundary(LEFT);

        /* set speed */
        player.vx = -1;
        player.vy = 0;
    }

    /* try moving right */
    else if (dir == RIGHT && checkCollision(RIGHT))
    {
        /* check if player crossed map boundary */
        checkBoundary(RIGHT);

        /* set speed */
        player.vx = 1;
        player.vy = 0;
    }
}

static _Bool checkCollision(unsigned int dir)
{
    /* north tile */
    if (dir == UP)
    {
        return Map_getTile(overworld.map, player.y / 16 - 1, player.x / 16)->passable;
    }

    /* south tile */
    else if (dir == DOWN)
    {
        return Map_getTile(overworld.map, player.y / 16 + 1, player.x / 16)->passable;
    }

    /* west tile */
    else if (dir == LEFT)
    {
        return Map_getTile(overworld.map, player.y / 16, player.x / 16 - 1)->passable;
    }

    /* east tile */
    else if (dir == RIGHT)
    {
        return Map_getTile(overworld.map, player.y / 16, player.x / 16 + 1)->passable;
    }

    else
    {
        return 1;
    }
}

static void checkBoundary(unsigned int dir)
{
    /* crossing north boundary */
    if (dir == UP && player.y == 0)
    {
        /* change map */
        overworld.map = overworld.map->north;

        /* fade music */
        Audio_playMusicFade(overworld.map->id);

        /* change position */
        player.y = overworld.map->h * 16;
    }

    /* crossing south boundary */
    else if (dir == DOWN && player.y == overworld.map->h * 16)
    {
        /* change map */
        overworld.map = overworld.map->south;

        /* fade music */
        Audio_playMusicFade(overworld.map->id);

        /* change position */
        player.y = 0;
    }

    /* crossing west boundary */
    else if (dir == LEFT && player.x == 0)
    {
        /* change map */
        overworld.map = overworld.map->west;

        /* fade music */
        Audio_playMusicFade(overworld.map->id);

        /* change position */
        player.x = overworld.map->w * 16;
    }

    /* crossing east boundary */
    else if (dir == RIGHT && player.x == overworld.map->w * 16)
    {
        /* change map */
        overworld.map = overworld.map->east;

        /* fade music */
        Audio_playMusicFade(overworld.map->id);

        /* change position */
        player.x = 0;
    }
}
