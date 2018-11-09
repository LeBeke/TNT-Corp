# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: display grayscale black_and_white matrix01

display: display.o
grayscale: pixel_operations.o grayscale.o
black_and_white: pixel_operations.o black_and_white.o
black_and_white.o: pixel_operations.h
grayscale.o: pixel_operations.h
matrix01:pixel_operations.o matrix01.o
matrix01.o: pixel_operations.o

clean:
	${RM} *.o
	${RM} *.d
	${RM} display
	${RM} grayscale
	${RM}black_and_white
	${RM}matrix01

# END