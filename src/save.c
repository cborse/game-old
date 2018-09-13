#include <stdio.h>
#include <string.h>
#include "save.h"

Save save;

void Save_read(void)
{
    /* open save file if it exists */
    FILE *file = fopen("data/save.dat", "r");

    if (file)
    {
        /* status */
        fscanf(file, "STATUS %u\n", &save.status);

        /* name */
        fscanf(file, "NAME %s\n", save.name);

        /* badges */
        fscanf(file, "BADGES %u\n", &save.badges);

        /* pokedex */
        fscanf(file, "POKEDEX %u\n", &save.pokedex);

        /* time */
        fscanf(file, "TIME %u\n", &save.time);

        /* position */
        fscanf(file, "X %u\n", &save.x);
        fscanf(file, "Y %u\n", &save.y);

        /* map */
        fscanf(file, "MAP %u\n", &save.map);

        /* close file */
        fclose(file);
    }

    /* if it doesn't exist, create it */
    else
    {
        /* close file */
        fclose(file);

        /* set defaults */
        save.status = 0;
        strcpy(save.name, "PLAYER\0");
        save.badges = 0;
        save.pokedex = 0;
        save.time = 0;
        save.x = 128;
        save.y = 128;
        save.map = 1;

        /* write */
        Save_write();
    }
}

void Save_write(void)
{
    /* open save file for writing */
    FILE *file = fopen("data/save.dat", "w");

    /* status */
    fprintf(file, "STATUS %u\n", save.status);

    /* name */
    fprintf(file, "NAME %s\n", save.name);

    /* badges */
    fprintf(file, "BADGES %u\n", save.badges);

    /* pokedex */
    fprintf(file, "POKEDEX %u\n", save.pokedex);

    /* time */
    fprintf(file, "TIME %u\n", save.time);

    /* position */
    fprintf(file, "X %u\n", save.x);
    fprintf(file, "Y %u\n", save.y);

    /* map */
    fprintf(file, "MAP %u\n", save.map);

    /* close file */
    fclose(file);
}
