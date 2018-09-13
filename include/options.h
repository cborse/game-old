#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct
{
    unsigned int textspeed;
    unsigned int frametype;
} Options;

void Options_read(void);

void Options_write(void);

#endif
