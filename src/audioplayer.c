#include <stdio.h>
#include <stdlib.h>
#include "audioplayer.h"
#define ONEMEGAOCTET 1048576

int
audio_init ()
{
    ALCdevice * device = alcOpenDevice(NULL);
    if (!device) {return 1;}

    ALCcontext * context = alcCreateContext (device, NULL);
    if (!context) {return 1;}

    if (!alcMakeContextCurrent (context)) {return 1;}

    alListener3f (AL_POSITION, 0.0, 0.0, 0.0);

    return 0;
}

void
audio_shutdown ()
{
    ALCcontext * context = alcGetCurrentContext ();
    ALCdevice *  device  = alcGetContextsDevice (context);

    alcMakeContextCurrent (NULL);

    alcDestroyContext (context);

    alcCloseDevice (device);
}


static void *
play (void * p)
{
    AudioPlayer * player = (AudioPlayer *)p;
    int i;
    int no_buf;
    unsigned int buf;
    int state;

    do
    {
        alGetSourcei (player->source_id, AL_BUFFERS_PROCESSED, &no_buf);

        for (i = 0; i < no_buf; i++)
        {
            alSourceUnqueueBuffers (player->source_id, 1, &buf);

            if (sound_nextSample (player->s))
            {
                alBufferData (buf, player->s->format, player->s->data, player->s->read_size, player->s->freq);
                alSourceQueueBuffers (player->source_id, 1, &buf);
            }
            else if (player->flags & PLAYER_LOOP)
            {
                sound_seekSample (player->s);
                sound_nextSample (player->s);
                alBufferData (buf, player->s->format, player->s->data, player->s->read_size, player->s->freq);
                alSourceQueueBuffers (player->source_id, 1, &buf);
            }
        }

        alGetSourcei (player->source_id, AL_SOURCE_STATE, &state);
    }
    while (state == AL_PLAYING);

    alGetSourcei (player->source_id, AL_BUFFERS_QUEUED, &no_buf);

    for (i = 0; i < no_buf; i++)
        alSourceUnqueueBuffers (player->source_id, 1, &buf);

    player->is_playing = 0;

    return NULL;
}

AudioPlayer *
audio_new (unsigned int flags)
{
    AudioPlayer * player;
    player = malloc (sizeof (AudioPlayer));

    alGenSources (1, &player->source_id);
    alSource3f (player->source_id, AL_POSITION, 0.0, 0.0, 0.0);

    if (flags & PLAYER_SOUND)
    {
        alGenBuffers (1, &player->sound_buffer);
    }
    else
    {
        flags |= PLAYER_AMBIENT;
    }
    
    if (flags & PLAYER_AMBIENT)
    {
        alGenBuffers (2, player->buffer_id);
    }

    player->is_playing = 0;
    player->flags = flags;
    player->lastSound = NULL;

    return player;
}

void
audio_position (AudioPlayer * player, float x, float y, float z)
{
    alSource3f (player->source_id, AL_POSITION, x, y, z);
}

void
audio_stop (AudioPlayer * player)
{
    int i;
    int nb_buf;
    unsigned int buf;
   
    if (!player->is_playing) {return;}

    alSourceStop (player->source_id);
    player->is_playing = 0;

    alGetSourcei (player->source_id, AL_BUFFERS_QUEUED, &nb_buf);

    for (i = 0; i < nb_buf; i++)
        alSourceUnqueueBuffers (player->source_id, 1, &buf);
    
    sound_closeSample (player->s);
    player->s = NULL;
}

void
audio_playMusic (AudioPlayer * player, const char * path)
{
    if (!(player->flags & PLAYER_AMBIENT)) {return;}

    audio_stop (player);

    player->s = sound_loadSample (path, ONEMEGAOCTET);
    if (player->s == NULL) {return;}

    sound_nextSample (player->s);

    alBufferData (player->buffer_id[0], player->s->format, player->s->data, player->s->read_size, player->s->freq);

    if (sound_nextSample (player->s))
    {
        alBufferData (player->buffer_id[1], player->s->format, player->s->data, player->s->read_size, player->s->freq);
        alSourceQueueBuffers (player->source_id, 2, player->buffer_id);
    }
    else
        alSourceQueueBuffers (player->source_id, 1, player->buffer_id);

    alSourcePlay (player->source_id);

    pthread_create (&player->t, NULL, play, player);

    pthread_detach (player->t);

    player->is_playing = 1;
}

int
audio_isPlaying (AudioPlayer * player)
{
    return player->is_playing;
}

void
audio_playSound (AudioPlayer * player, Sound * sound)
{
    if (player->flags & PLAYER_SOUND)
    {
        if (player->lastSound != sound)
            alBufferData (player->sound_buffer, sound->format, sound->data, sound->size, sound->freq);
        if (!player->is_playing)
        {
            alSourcei (player->source_id, AL_BUFFER, player->sound_buffer);
            alSourcePlay (player->source_id);
        }
    }
}



