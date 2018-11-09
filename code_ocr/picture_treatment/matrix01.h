#ifndef MATRIX01_H
#define MATRIX01_H

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "err.h"

int **frompicturetomatrix();
SDL_Surface* load_image(char* path);




#endif
