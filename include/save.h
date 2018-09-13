#ifndef SAVE_H
#define SAVE_H

typedef struct
{
    unsigned int status;
    char name[8];
    unsigned int badges;
    unsigned int pokedex;
    unsigned int time;
    unsigned int x;
    unsigned int y;
    unsigned int map;
} Save;

void Save_read(void);

void Save_write(void);

#endif
