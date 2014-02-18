#ifndef SOUND_H
#define SOUND_H

#include <vorbis/vorbisfile.h>
#include <ogg/ogg.h>
#include <AL/al.h>
#include <AL/alc.h>

typedef struct Sound{
	char * data;
	int size;
	int freq;
	int format;
}Sound;

union soundFile{
	OggVorbis_File oggFile;
};

typedef struct SoundSample{
	char * data;
	char * old_data;
	int size;
	int old_read_size;
	int read_size;
	int freq;
	int format;
	int bitStream;
	union soundFile s_file;
}SoundSample;

// Sound * sound_load (const char * path);

SoundSample * sound_loadSample (const char * path);

int sound_nextSample (SoundSample * sample);

void sound_seekSample (SoundSample * sample);

void sound_closeSample (SoundSample * sample);

#endif

