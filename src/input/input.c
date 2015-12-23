#include <SDL_mouse.h>
#include <stdio.h>
#include <SDL_events.h>
#include "input.h"
#include "../game/game.h"
#include "../game/map.h"

static void handle_focus(SDL_MouseMotionEvent *event){
    map_focus_on(event->x * VIRTUAL_W / WINDOW_W, event->y * VIRTUAL_H / WINDOW_H);
}
void input_update() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_QUIT:
                game_stop();
                break;
            case SDL_MOUSEMOTION:
                handle_focus(&event.motion);
                break;
        }
    }
}
