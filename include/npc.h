#ifndef NPC_H
#define NPC_H

#include "helpers/sprite.h"

typedef struct
{
    unsigned x, y;
    Sprite *sprite;
} NPC;

void NPC_createNPCs(void);

void NPC_destroyNPCs(void);

NPC *NPC_get(unsigned id);

#endif
