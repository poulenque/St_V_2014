#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#define PLAYER_LOOP     1
#define PLAYER_AMBIENT  2
#define PLAYER_SOUND    4

#include <pthread.h>
#include "sound.h"

typedef struct AudioPlayer
{
    SoundSample * s;
    Sound * lastSound;
    unsigned int is_playing;
    unsigned int source_id;
    unsigned int buffer_id[2];
    unsigned int sound_buffer;
    pthread_t t;
    unsigned int flags;

}AudioPlayer;

int audio_init ();

void audio_shutdown ();

AudioPlayer * audio_new (unsigned int flags);

void audio_position (AudioPlayer * player, float x, float y, float z);

void audio_stop (AudioPlayer * player);

void audio_playMusic (AudioPlayer * player,const char * path);

int audio_isPlaying (AudioPlayer * player);

void audio_playSound (AudioPlayer * player, Sound * sound);


#endif

