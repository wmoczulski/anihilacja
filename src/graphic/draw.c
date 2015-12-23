#include <SDL_surface.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "draw.h"
#include "../config/config.h"
#include "../game/map.h"
#include "window.h"

/**
 * Na podstawie funkcji autorstwa "Darel Rex Finley" będącego w domenie publicznej
 */
void changeSaturation(int *r, int *g, int *b, double change) {

    double p = sqrt((*r) * (*r) * .299 +
                    (*g) * (*g) * .587 +
                    (*b) * (*b) * .114);

    *r = p + ((*r) - p) * change;
    *g = p + ((*g) - p) * change;
    *b = p + ((*b) - p) * change;

    if(*r > 255){
        *r = 255;
    }
    if(*r > 255){
        *r = 255;
    }
    if(*r > 255){
        *r = 255;
    }
}

static Uint32 getColor(map_tile *tile) {
    int r, g, b;
    switch (tile->color) {
        case YELLOW:
            r = YELLOW_R;
            g = YELLOW_G;
            b = YELLOW_B;
            break;
        case ORANGE:
            r = ORANGE_R;
            g = ORANGE_G;
            b = ORANGE_B;
            break;
        case RED:
            r = RED_R;
            g = RED_G;
            b = RED_B;
            break;
        case PINK:
            r = PINK_R;
            g = PINK_G;
            b = PINK_B;
            break;
        case PURPLE:
            r = PURPLE_R;
            g = PURPLE_G;
            b = PURPLE_B;
            break;
        case DEAD:
            r = DEAD_R;
            g = DEAD_G;
            b = DEAD_B;
            break;
    }

    if (tile->focus) {
        changeSaturation(&r, &g, &b, SATURATION_ON_FOCUS);
    }else{
        changeSaturation(&r, &g, &b, SATURATION_NO_FOCUS);
    }

    return SDL_MapRGB(surface->format, (int) r, (int) g, (int) b);
}

void draw_map() {
    for (int x = 0; x < VIRTUAL_W; x++) {
        for (int y = 0; y < VIRTUAL_H; y++) {
            SDL_Rect rect;
            rect.x = x * (WINDOW_W / VIRTUAL_W);
            rect.y = y * (WINDOW_H / VIRTUAL_H);
            rect.w = WINDOW_W / VIRTUAL_W;
            rect.h = WINDOW_H / VIRTUAL_H;
            Uint32 color = getColor(&map[x][y]);
            SDL_FillRect(surface, &rect, color);
            window_update();
        }
    }
}
