ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        CCFLAGS += -D AMD64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        CCFLAGS += -D IA32
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
    endif
endif


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

# C_FLAGS += -lmingw32
C_FLAGS += -lSDLmain
C_FLAGS += -lSDL
# C_FLAGS += -lopengl32
# C_FLAGS += -lglu32


# LIBS += -lmingw32

LIBS += -pg -g
LIBS += -lm
LIBS += -lvorbisfile
LIBS += -lopenal
# LIBS += -lopenal32

LIBS += -lSDLmain
LIBS += -lSDL

LIBS += -lGL -lGLU
# LIBS += -lopengl32 -lglu32
# LIBS += -lpthread
# LIBS += -lpthreadGC2



SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:%.c=%.o)

PROG = St_V_2014

all:$(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) $(LIBS) -o $(PROG)
	
# To obtain object files
%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

run:all
	./$(PROG)

run-softwae:all
	LIBGL_DEBUG=verbose LIBGL_SHOW_FPS=1 LIBGL_ALWAYS_SOFTWARE=1 ./$(PROG)

run-profiling:all
	LIBGL_DEBUG=verbose LIBGL_SHOW_FPS=1 ./$(PROG) ;gprof $(PROG) gmon.out

clean:
	rm -f $(OBJECTS)

mrproper:
	rm -f $(PROG) $(OBJECTS)

