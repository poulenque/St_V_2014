
CC = gcc

#profiling
C_FLAGS += -pg

C_FLAGS += -W -ansi -pedantic -static -g
C_FLAGS += -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual
C_FLAGS += -Wpointer-arith -Wformat=2 -Wlogical-op
#CFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-unused

C_FLAGS += -O2
# C_FLAGS += -std=c99
C_FLAGS += -std=c11
C_FLAGS += -march=native








LIBS += -pg -g

LIBS += -lm
LIBS += -lSDL
# LIBS += -lSDL_image
LIBS += -lvorbisfile -lopenal
LIBS += -lpthread
LIBS += -lGL -lGLU -lGLEW


SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:%.c=%.o)

PROG = St_V_2014

all:$(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o $(PROG)
	
# To obtain object files
%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

run:all
	./St_V_2014

run-softwae:all
	LIBGL_DEBUG=verbose LIBGL_SHOW_FPS=1 LIBGL_ALWAYS_SOFTWARE=1 ./St_V_2014

run-profiling:all
	LIBGL_DEBUG=verbose LIBGL_SHOW_FPS=1 ./St_V_2014 ;gprof St_V_2014 gmon.out

clean:
	rm -f $(OBJECTS)

mrproper:
	rm -f $(PROG) $(OBJECTS)

