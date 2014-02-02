#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include "shader.h"

#define PATH_MAX_LENGTH 1024


static int
compileLog (const char * const src, unsigned int shader)
{
	int status = GL_TRUE;
	int logsize;

	glGetShaderiv (shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char * log;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);

		log = malloc (logsize + 1);

		glGetShaderInfoLog (shader, logsize, &logsize, log);
		log[logsize + 1] = '\0';

		fprintf(stderr, "Cannot compile shader \n %s :\n%s\n", src, log);

		free (log);

		glDeleteShader(shader);
		return 1;
	}
	return 0;
}

static int
linkLog (unsigned int status, unsigned int program)
{
	if (status != GL_TRUE)
	{
		int logsize;
		char * log;

		logsize = 0;

		glGetProgramiv (program, GL_INFO_LOG_LENGTH, &logsize);

		log = malloc (logsize + 1);

		glGetProgramInfoLog (program, logsize, &logsize, log);
		log[logsize + 1] = '\0';

		fprintf (stderr, "Cannot link shader :\n%s\n", log);

		return 1;
	}
	return 0;
}

static int
shader_compile (int * shader, const char * const src, int type)
{
	*shader = glCreateShader (type);

	if (!shader)
	{
		printf("Can't create shader\n");
		return 1;
	}
	if (!src)
	{
		glDeleteShader (*shader);
		printf ("Can't load shader source\n");
		return 1;
	}

	glShaderSource (*shader, 1, (const GLchar **)&src, NULL);

	glCompileShader (*shader);

	if (compileLog (src, *shader))
		return 1;

	return 0;
}

static unsigned int
shader_link (unsigned int program)
{
	int status;

	glLinkProgram (program);
	glGetProgramiv (program, GL_LINK_STATUS, &status);

	return (linkLog (status, program));
}


static void shader_loadSrc (const char * name, int * fid, int * vid) {
	FILE * fp;
	char * src;
	long nb_bytes;
	char path[PATH_MAX_LENGTH];

	strcpy (path, "src/");
	strncat (path, name, PATH_MAX_LENGTH-1);
	strncat (path, ".vert", PATH_MAX_LENGTH-1);

	fp = fopen (path, "r");

	if (!fp) {return;}

	fseek (fp, 0, SEEK_END);
	nb_bytes = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	src = malloc (nb_bytes + 1);
	fread (src, sizeof (char), nb_bytes, fp);
	fclose (fp);
	src[nb_bytes] = '\0';

	shader_compile (vid, src, GL_VERTEX_SHADER);

	free (src);

	strcpy (path, "src/");
	strncat (path, name, PATH_MAX_LENGTH-1);
	strncat (path, ".frag", PATH_MAX_LENGTH-1);

	fp = fopen (path, "r");

	if (!fp) {return;}

	fseek (fp, 0, SEEK_END);
	nb_bytes = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	src = malloc (nb_bytes + 1);
	fread (src, sizeof (char), nb_bytes, fp);
	fclose (fp);
	
	src[nb_bytes] = '\0';
	shader_compile (fid, src, GL_FRAGMENT_SHADER);

	free (src);
}

unsigned int
shader_createProgram (const char * name)
{
	unsigned int program;
	int vid;
	int fid;
	
	shader_loadSrc (name, &vid, &fid);

	program = glCreateProgram ();

	glAttachShader (program, vid);
	glAttachShader (program, fid);

	shader_link (program);

	return program;
}

