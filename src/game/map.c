#include <SDL_timer.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map.h"

enum color random_color() {
    return (enum color)rand() % 5; // values 0 - 4 represents colors
}

void map_init() {
    srand(time(NULL));
    for(int x = 0; x < VIRTUAL_W; x++){
        for(int y = 0; y < VIRTUAL_H; y++){
            map[x][y].color = random_color();
            map[x][y].focus = false;
        }
    }
}
