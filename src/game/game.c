#include <stdbool.h>
#include <SDL_timer.h>
#include <stdio.h>
#include "game.h"
#include "../config/config.h"
#include "map.h"
#include "../graphic/draw.h"
#include "../graphic/window.h"
#include "../input/input.h"


static bool stop = false;
static Uint32 ms_per_frame;

static void calculate_delta_time() {
    ms_per_frame = 1000 / FPS;
}

static void init() {
    window_init();
    calculate_delta_time();
    map_init();
}

static void update() {
    window_update();
    map_update();
}

static void draw() {
    draw_map();
}

static void destroy() {
    window_destroy();
}

static void loop(){
    input_update();
    update();
    draw();
}
void game_run() {
    init();
    update();

    Uint32 current_tick = SDL_GetTicks();
    while (!stop) {
        loop();
        current_tick += ms_per_frame;
        if(SDL_GetTicks() < current_tick){
            SDL_Delay(current_tick - SDL_GetTicks());
        }
    }
    stop = false;

    destroy();
}

void game_stop() {
    stop = true;
}
