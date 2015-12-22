#include <stdbool.h>
#include <SDL_timer.h>
#include "game.h"
#include "../config/config.h"


static bool stop = false;
static Uint32 ms_per_frame;

static void calculate_delta_time() {
    ms_per_frame = 1000 / FPS;
}

static void init() {
    calculate_delta_time();
}

static void input() {

}

static void update() {

}

static void draw() {

}

static void destroy() {

}


void game_run() {
    init();

    while (!stop) {
        Uint32 ms_on_start = SDL_GetTicks();
        input();
        update();
        draw();
        SDL_Delay(ms_per_frame - SDL_GetTicks() + ms_on_start);
    }
    stop = false;

    destroy();
}

void game_stop() {
    stop = true;
}
