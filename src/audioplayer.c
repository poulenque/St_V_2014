#include "audioplayer.h"
#include <stdio.h>
#include <stdlib.h>

static void * play (void * p);

int audio_init () {
	ALCdevice * device = alcOpenDevice(NULL);
	if (!device) {return 1;}
	ALCcontext * context = alcCreateContext (device, NULL);
	if (!context) {return 1;}
	if (!alcMakeContextCurrent (context)) {return 1;}
	alListener3f (AL_POSITION, 0.0, 0.0, 0.0);
	return 0;
}

void audio_shutdown () {
	ALCcontext * context = alcGetCurrentContext ();
	ALCdevice *  device  = alcGetContextsDevice (context);
	alcMakeContextCurrent (NULL);
	alcDestroyContext (context);
	alcCloseDevice (device);
}

AudioPlayer* new_audioplayer(){
	AudioPlayer* player;	
	player = malloc (sizeof(AudioPlayer));

	alGenSources (1, &player->source_id);
	alSourceStop (player->source_id);
	alSource3f (player->source_id, AL_POSITION, 0.0, 0.0, 0.0);

	// 1 buffer pour la piste suivante
	alGenBuffers (2, player->buffer_id);

	player->next_file_path=NULL;

	player->s1 = sound_loadSample ("music/silence.ogg");

	if (player->s1 == NULL) {
		printf("ERROR : STUPID SILENT FILE MISSING X¬D NEED : \"%s\"\n",player->next_file_path);
		return;
	}

	//ecrire un bout dans le buffer
	if (!sound_nextSample (player->s1)) {
		printf("FILE EMPTY, COULD NOT PLAY\n");
		sound_closeSample (player->s1);
		return;
	}
	alBufferData (player->buffer_id[0], player->s1->format, player->s1->data, player->s1->read_size, player->s1->freq);

	//if sample is empty, read the same stuff
	if (sound_nextSample (player->s1)==0) {
		sound_seekSample (player->s1);
		sound_nextSample (player->s1);
	}
	alBufferData (player->buffer_id[1], player->s1->format, player->s1->data, player->s1->read_size, player->s1->freq);
	alSourceQueueBuffers (player->source_id, 2, player->buffer_id);

	alSourcePlay (player->source_id);


	//le thread tourne en permanence
	pthread_create (&player->t, NULL, play, player);
	pthread_detach (player->t);

	return player;
}

void audioplayer_play(AudioPlayer* player){
		printf("audioplayer -> play\n");
		alSourcePlay (player->source_id);
}

// pause
void audioplayer_pause(AudioPlayer* player){
		printf("audioplayer -> pause\n");
		alSourcePause (player->source_id);
}

void audioplayer_set_next(AudioPlayer* player, const char * path){
	//TODO MUTEX
	player->next_file_path=path;
	//TODO MUTEX
}

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


















// void audio_position (AudioPlayer * player, float x, float y, float z) {
// 	alSource3f (player->source_id, AL_POSITION, x, y, z);
// }

// this thread sould be playing a file and play the next one as the first one finished,
static void * play (void * p) {
	AudioPlayer * player = (AudioPlayer *)p;
	int i;
	int no_buf;
	unsigned int buf;


	do {
			alGetSourcei (player->source_id, AL_BUFFERS_PROCESSED, &no_buf);

			for (i = 0; i < no_buf; i++) {
				alSourceUnqueueBuffers (player->source_id, 1, &buf);

				if (sound_nextSample (player->s1)) {
					alBufferData (buf, player->s1->format, player->s1->data, player->s1->read_size, player->s1->freq);
					alSourceQueueBuffers (player->source_id, 1, &buf);
				} else {

					//===
					//===
					//===
					// TODO MUTEX
					if(player->next_file_path){
						// printf("MUSIC CHANGED TO %s\n",player->next_file_path);
						sound_closeSample(player->s1);
						player->s1=sound_loadSample(player->next_file_path);
						sound_nextSample (player->s1);
						alBufferData (buf, player->s1->format, player->s1->data, player->s1->read_size, player->s1->freq);
						alSourceQueueBuffers (player->source_id, 1, &buf);
						player->next_file_path=NULL;
						alSourcePlay (player->source_id);
					}
					// TODO MUTEX
					//===
					//===
					//===
					else if(player->s1!=NULL){
						// printf("FINISHED, GONNA LOOP\n");
						sound_seekSample (player->s1);
						sound_nextSample (player->s1);
						alBufferData (buf, player->s1->format, player->s1->data, player->s1->read_size, player->s1->freq);
						alSourceQueueBuffers (player->source_id, 1, &buf);
						alSourcePlay (player->source_id);
					}else{
						printf("ERROR : SOUND CRASHED\n");
						break;
					}
				}
			}
	}while (1);

	alGetSourcei (player->source_id, AL_BUFFERS_QUEUED, &no_buf);

	for (i = 0; i < no_buf; i++){
		alSourceUnqueueBuffers (player->source_id, 1, &buf);
	}


	return NULL;
}
