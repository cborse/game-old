#include "audio.h"

static Audio audio;

void Audio_init(void)
{
    /* create sound */
    audio.sound = sfSound_create();

    /* create buffers */
    audio.buffers[0] = sfSoundBuffer_createFromFile("assets/sounds/select.wav");
    audio.buffers[1] = sfSoundBuffer_createFromFile("assets/sounds/save.wav");
    
    /* create musics */
    audio.musics[0] = sfMusic_createFromFile("assets/music/mainmenu.wav");
    audio.musics[1] = sfMusic_createFromFile("assets/music/newbark.wav");
    audio.musics[2] = sfMusic_createFromFile("assets/music/route29.wav");

    /* current and next music default is 0 */
    audio.curr_music = 0;
    audio.next_music = 0;

    /* fade is false */
    audio.fading = 0;
}

void Audio_shutdown(void)
{
    /* destroy sound */
    sfSound_destroy(audio.sound);

    /* destroy buffers */
    for (unsigned i = 0; i < NUM_BUFFERS; i++)
    {
        sfSoundBuffer_destroy(audio.buffers[i]);
    }
}

void Audio_update(void)
{
    /* fading */
    if (audio.fading == 1)
    {
        /* decrease volume */
        sfMusic_setVolume(audio.musics[audio.curr_music], sfMusic_getVolume(audio.musics[audio.curr_music]) - 1);

        /* volume is below 5% */
        if (sfMusic_getVolume(audio.musics[audio.curr_music]) < 5)
        {
            /* stop it */
            sfMusic_stop(audio.musics[audio.curr_music]);

            /* play new music */
            sfMusic_play(audio.musics[audio.next_music]);

            /* set curr_music */
            audio.curr_music = audio.next_music;
            audio.next_music = 0;

            /* reset volume */
            sfMusic_setVolume(audio.musics[audio.curr_music], 100);

            /* set fading to false */
            audio.fading = 0;
        }
    }
}

void Audio_playSound(unsigned sound)
{
    /* set buffer to sound */
    sfSound_setBuffer(audio.sound, audio.buffers[sound]);

    /* play it */
    sfSound_play(audio.sound);

    /* wait for it to finish */
    while (sfSound_getStatus(audio.sound) == sfPlaying) {;}
}

void Audio_playMusic(unsigned int music)
{
    /* play music */
    sfMusic_play(audio.musics[music]);
    sfMusic_setVolume(audio.musics[music], 100);
}

void Audio_playMusicFade(unsigned int music)
{
    /* set music as next_music */
    audio.next_music = music;

    /* trigger fade */
    audio.fading = 1;
}
