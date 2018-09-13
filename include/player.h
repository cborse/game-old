#ifndef PLAYER_H
#define PLAYER_H

#include "helpers/sprite.h"

typedef struct
{
    _Bool moving;
    int x, y, vx, vy;
    unsigned int dir, frame, counter;
    Sprite *sprite;
} Player;

void Player_init(void);

void Player_shutdown(void);

void Player_update(void);

void Player_draw(void);

#endif
