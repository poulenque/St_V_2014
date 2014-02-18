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
	player->time_buffer_offset=0;

	player->s1 = sound_loadSample ("music/silence.ogg");
	player->now_playing="music/silence.ogg";

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
		// printf("audioplayer -> play\n");
		alSourcePlay (player->source_id);
}

// pause
void audioplayer_pause(AudioPlayer* player){
		// printf("audioplayer -> pause\n");
		alSourcePause (player->source_id);
}

void audioplayer_set_next(AudioPlayer* player, const char * path){
	//TODO MUTEX
	player->next_file_path=path;
	//TODO MUTEX
}

// actual time in file 
double audioplayer_getTime(AudioPlayer* player){
	float time_position; 
	alGetSourcef( player->source_id, AL_SAMPLE_OFFSET, &time_position );
	time_position/=player->s1->freq;
	return time_position + player->time_buffer_offset;
	// return  player->time_position;
}

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
double audioplayer_getAmplitude(AudioPlayer* player, int time_dt){
	//MUTEX NEEDED !!!

	// time_dt=2;//en millisecondes


	float time_position;
	alGetSourcef( player->source_id, AL_SAMPLE_OFFSET, &time_position );
	int begin = (int)time_position*4;// + .2*player->s1->freq;//lire a l'avance

	{
		int delta=time_dt*player->s1->freq*.001;//.001 pour se mettre en seconde car Hz
		int end =delta+begin;
		if(end>player->s1->old_read_size)
			end=player->s1->old_read_size;
		double ret=0;
		int i;
		for(i=begin+1;i<end;i+=4){
			// ret+=pow(player->s1->old_data[i]*.001,2);
			ret+=pow(fabs(player->s1->old_data[i]/128.),4);
			// ret+=fabs((float)(player->s1->old_data[i]/128.));
			// ret+=fabs((float)(player->s1->old_data[i]/128.));
		}
		i-=begin;
		// ret=ret/i*200;
		// ret=ret/i*75;
		ret=ret/i*50;
		if(i==0)ret=0;
		// printf("%2.8lf,%.10i,%.10i\n", ret ,begin,player->s1->old_read_size);
		return ret;
	}

	//MUTEX NEEDED !!!
}


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

	int music_changed=0;
	int music_looped=0;

	float buf_time=0;
	float buf_time_next=0;
	char * next_file_path;

	int cache=0;

	do {
			//how many buf to unqueue ?
			alGetSourcei (player->source_id, AL_BUFFERS_PROCESSED, &no_buf);
			while(no_buf--){

				//unqueue -> time_buffer_offset incrased by time buffered in this buffer
				alSourceUnqueueBuffers (player->source_id, 1, &buf);
				player->time_buffer_offset+=buf_time;
				buf_time=buf_time_next;

				if(music_changed){
					music_changed=0;
					player->time_buffer_offset=0;
					player->now_playing=next_file_path;
				}
				if(music_looped){
					music_looped=0;
					player->time_buffer_offset=0;
				}
				
				#undef AMPLITUDE_BETA
				/////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////
				#ifdef AMPLITUDE_BETA
					//IF SOUND_NEXTSAMPLE_CALLEF HERE : AMPLITUDE WORKS FINE UNTIL LAST LOOP
					cache = sound_nextSample (player->s1);
				#endif
				/////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////
				if (cache) {
					// printf("______________CONTINUE\n");
					alBufferData (buf, player->s1->format, player->s1->data, player->s1->read_size, player->s1->freq);
					alSourceQueueBuffers (player->source_id, 1, &buf);
					buf_time_next=player->s1->read_size/(double)player->s1->freq/4.;
				} else {
					if(player->next_file_path){
						// printf("______________NEW_FILE\n");
						// printf("MUSIC CHANGED TO %s\n",player->next_file_path);
						sound_closeSample(player->s1);
						//===
						//===
						//===
						// TODO MUTEX
						player->s1=sound_loadSample(player->next_file_path);
						next_file_path=player->next_file_path;
						player->next_file_path=NULL;
						// TODO MUTEX
						//===
						//===
						//===
						music_changed=1;
					}
					else if(player->s1!=NULL){
						// printf("______________RELOAD\n");
						// printf("GONNA REPLAY\n");
						music_looped=1;
						sound_seekSample (player->s1);
					}else{
						printf("ERROR : SOUND CRASHED\n");
						break;
					}
					sound_nextSample (player->s1);
					alBufferData (buf, player->s1->format, player->s1->data, player->s1->read_size, player->s1->freq);
					alSourceQueueBuffers (player->source_id, 1, &buf);
					alSourcePlay (player->source_id);
					buf_time_next=player->s1->read_size/(double)player->s1->freq/4.;
				}
				/////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////
				#ifndef AMPLITUDE_BETA
					cache = sound_nextSample (player->s1);
				#endif
				/////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////
			}
	}while (1);

	alGetSourcei (player->source_id, AL_BUFFERS_QUEUED, &no_buf);

	for (i = 0; i < no_buf; i++){
		alSourceUnqueueBuffers (player->source_id, 1, &buf);
	}

	return NULL;
}
