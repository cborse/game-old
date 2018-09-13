#ifndef SCENE_H
#define SCENE_H

#include <SFML/Window.h>

typedef struct
{
    void (*init)(void);
    void (*shutdown)(void);
    void (*resume)(void);
    void (*processEvent)(sfEvent *);
    void (*update)(void);
    void (*draw)(void);
} Scene;

#endif
