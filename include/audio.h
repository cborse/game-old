#ifndef AUDIO_H
#define AUDIO_H

#define NUM_BUFFERS 2
#define NUM_MUSICS 3

#include <SFML/Audio.h>

typedef struct
{
    sfSound *sound;
    sfSoundBuffer *buffers[NUM_BUFFERS];
    sfMusic *musics[NUM_MUSICS];
    unsigned int curr_music;
    unsigned int next_music;
    _Bool fading;
} Audio;

enum { SND_SELECT, SND_SAVE };

enum { MUS_MAINMENU, MUS_NEWBARK, MUS_ROUTE29 };

void Audio_init(void);

void Audio_shutdown(void);

void Audio_update(void);

void Audio_playSound(unsigned sound);

void Audio_playMusic(unsigned int music);

void Audio_playMusicFade(unsigned int new_music);

#endif
