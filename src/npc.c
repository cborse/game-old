#include "npc.h"

static NPC npcs[1];

void NPC_createNPCs(void)
{
    /* test NPC */
    npcs[0].sprite = Sprite_create(0, 0, "assets/textures/player.png");
    Sprite_setSubTexture(npcs[0].sprite, 0, 16, 16, 16);
    npcs[0].x = 128;
    npcs[0].y = 128;
}

void NPC_destroyNPCs(void)
{
}

NPC *NPC_get(unsigned id)
{
    return &npcs[id];
}
