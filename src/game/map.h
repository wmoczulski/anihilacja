#ifndef ANIHILACJA_MAP_H
#define ANIHILACJA_MAP_H


#include <stdbool.h>
#include "../config/config.h"
#include "../list/list.h"

typedef struct map_tile map_tile;
struct map_tile {
    enum color color;
    bool focus;
};

map_tile map[VIRTUAL_W][VIRTUAL_H];

void map_init();

list *get_list_of_neighbours(int x, int y);

map_tile *get_tile_by_window_pos(int x, int y);

map_tile *get_tile_by_virtual_pos(int x, int y);

void map_focus_on(int vx, int vy);

#endif //ANIHILACJA_MAP_H
