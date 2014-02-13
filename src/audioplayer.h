#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H


#include <pthread.h>
#include "sound.h"


typedef struct AudioPlayer{
	SoundSample * s1;
	// SoundSample * s2;
	char * next_file_path;
	char * now_playing;
	double time_buffer_offset;
	// Sound * lastSound;
	// unsigned int is_playing;
	unsigned int source_id;
	unsigned int buffer_id[2];
	unsigned int sound_buffer;
	pthread_t t;
	// unsigned int flags;
}AudioPlayer;


int audio_init ();
void audio_shutdown ();

AudioPlayer* new_audioplayer();

void audioplayer_set_next(AudioPlayer* audioplayer, const char * path_to_file);

void audioplayer_play(AudioPlayer* audioplayer);
void audioplayer_pause(AudioPlayer* audioplayer);

// actual time in file 
double audioplayer_getTime(AudioPlayer* audioplayer);

// how long the music lasts
// double audioplayer_getDuration(AudioPlayer* audioplayer);

// this will do this calculation :
//  - there will be a buffer in which the audio file
//    is uncompressed so that buf[t] corresponds to
//    the position of the membrane at t.
//  - the calculation returned looks like this :
//      return = sum but[x]^2  for x from t to t+dt
//            where t is the position now
//                  t+dt is the position in time_dt
double audioplayer_getAmplitude(AudioPlayer* audioplayer, int time_dt);


// maybe a function to get what is in the buffer between t and t+time_dt ?
// might be very useful :¬D


#endif