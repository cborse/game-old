#ifndef GAME_H
#define GAME_H

#define MAX_SCENES 5

#include "scenes/scene.h"

typedef struct
{
    _Bool running;
    unsigned scenes_size;
    Scene *scenes[MAX_SCENES];
} Game;

void Game_init(void);

void Game_shutdown(void);

void Game_processEvent(void);

void Game_update(void);

void Game_draw(void);

void Game_pushScene(Scene *scene);

void Game_popScene(void);

void Game_changeScene(Scene *scene);

void Game_clearScenes(void);

#endif
