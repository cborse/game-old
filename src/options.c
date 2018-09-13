#include <stdio.h>
#include "options.h"

Options options;

void Options_read(void)
{
    /* open options file if it exists */
    FILE *file = fopen("data/options.dat", "r");

    if (file)
    {
        /* text speed */
        fscanf(file, "TEXTSPEED %u\n", &options.textspeed);

        /* frame type */
        fscanf(file, "FRAME %u\n", &options.frametype);

        /* close file */
        fclose(file);
    }

    /* if it doesn't exist, create one */
    else
    {
        /* close file */
        fclose(file);

        /* set default options */
        options.textspeed = 1;
        options.frametype = 0;

        /* write */
        Options_write();
    }
}

void Options_write(void)
{
    /* open options file for writing */
    FILE *file = fopen("data/options.dat", "w");

    /* text speed */
    fprintf(file, "TEXTSPEED %u\n", options.textspeed);

    /* frame type */
    fprintf(file, "FRAME %u\n", options.frametype);

    /* close file */
    fclose(file);
}
