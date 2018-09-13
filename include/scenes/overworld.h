#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "scenes/scene.h"
#include "map.h"

typedef struct
{
    Scene scene;
    Map *map;
} Overworld;

void Overworld_init(void);

#endif
