#ifndef ANIHILACJA_WINDOW_H
#define ANIHILACJA_WINDOW_H

#include <SDL_video.h>
#include <SDL.h>

SDL_Surface *surface;

void window_init();

void window_update();

void window_destroy();

#endif //ANIHILACJA_WINDOW_H
