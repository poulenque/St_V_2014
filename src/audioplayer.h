#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H


#include <pthread.h>
#include "sound.h"


typedef struct AudioPlayer{
	SoundSample * s1;
	// SoundSample * s2;
	char * next_file_path;
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
void audio_playMusic (AudioPlayer * player, const char * path);
void audio_stop (AudioPlayer * player);


// !!! optionnal nice generalization : allow user to play n files in same time !
//     set_next => set_next(AudioPlayer*audioplayer, int file_count ,const char ** paths_to_files)
//     getDuration will return an array of double



//will create an AudioPlayer and will return it. (allocate memory, set variables etc...)
AudioPlayer* new_audioplayer();


// this will set the next file to play.
//
// !!! if the function is called before the player gets to the end of the last file,
//     the effect should be the same as if the last call was not done.
//
// if nothing is playing, then play immediatly
void audioplayer_set_next(AudioPlayer* audioplayer, const char * path_to_file);

// pause
void audioplayer_pause(AudioPlayer* audioplayer);

// play where paused
// if there is nothing to play, does nothing.
void audioplayer_play(AudioPlayer* audioplayer);

// actual time in file 
double audioplayer_getTime(AudioPlayer* audioplayer);

// how long the music lasts
double audioplayer_getDuration(AudioPlayer* audioplayer);

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