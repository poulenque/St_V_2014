#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sound.h"

#define BUFFER 4096

static int openOgg (char * path, OggVorbis_File * oggFile, int * format, int * freq) {
	FILE * fp;
	fp = fopen (path, "rb");
	if (!fp) {return 1;}

	vorbis_info * pInfo;

	ov_open (fp, oggFile, NULL, 0);
	pInfo = ov_info (oggFile, -1);

	if (pInfo->channels == 1)
		*format = AL_FORMAT_MONO16;
	else
		*format = AL_FORMAT_STEREO16;

	*freq = pInfo->rate;
	return 0;
}

Sound * sound_load (char * path) {
	Sound * s;
	int bitStream;
	unsigned long bytes;
	char array[BUFFER];
	unsigned int total_read;
	size_t allocated;
	OggVorbis_File oggFile;

	s = malloc (sizeof (Sound));

	openOgg (path, &oggFile, &s->format, &s->freq);

	allocated = 8 * BUFFER;
	s->data = malloc (allocated);

	bitStream = 0;
	total_read = 0;

	do{
		bytes = ov_read (&oggFile, array, BUFFER, 0, 2, 1, &bitStream);

		if ((total_read + bytes) >= allocated) {
			char * tmp;
			allocated += (8 * BUFFER);
			tmp = realloc (s->data, allocated);
			if (tmp == NULL) {
				free (s->data);
				free (s);
				return NULL;
			}
			s->data = tmp;
		}

		memcpy (&s->data[total_read], array, bytes);

		total_read += bytes;
	}
	while (bytes > 0);

	s->size = total_read;

	ov_clear (&oggFile);

	return s;
}

SoundSample * sound_loadSample (char * path, int size){
	SoundSample * s;

	s = malloc (sizeof (SoundSample));

	if (openOgg (path, &s->s_file.oggFile, &s->format, &s->freq) == 1){
		free (s);
		return NULL;
	}

	s->data = malloc (size);
	s->size = size;

	s->bitStream = 0;
	s->read_size = 0;

	return s;
}

int sound_nextSample (SoundSample * sample){
	char array[BUFFER];
	long bytes;
	sample->read_size = 0;
	do{
		bytes = ov_read (&sample->s_file.oggFile, array, BUFFER, 0, 2, 1, &sample->bitStream);

		memcpy (&sample->data[sample->read_size], array, bytes);

		sample->read_size += bytes;
	}while ((sample->read_size + BUFFER) < sample->size && bytes != 0);

	return sample->read_size;
}

void sound_seekSample (SoundSample * sample){
	ov_raw_seek (&sample->s_file.oggFile, 0);
}

void sound_closeSample (SoundSample * sample){
	free (sample->data);
	ov_clear (&sample->s_file.oggFile);
	free (sample);
}

