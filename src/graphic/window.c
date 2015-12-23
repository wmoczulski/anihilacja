#include <SDL_video.h>
#include <SDL.h>
#include "window.h"
#include "../debug/debug.h"
#include "../config/config.h"

static SDL_Window *window = NULL;


void window_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fatal_error(2, "Couldn't init SDL video", SDL_GetError());
    }
    window = SDL_CreateWindow(WINDOW_TITLE,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_W,
                              WINDOW_H,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fatal_error(2, "Couldn't create window", SDL_GetError());
    }

    surface = SDL_GetWindowSurface(window);
}


void window_update() {
    SDL_UpdateWindowSurface(window);
}


void window_destroy() {
    SDL_DestroyWindow(window);

    SDL_Quit();
}