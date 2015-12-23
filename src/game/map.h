#ifndef ANIHILACJA_MAP_H
#define ANIHILACJA_MAP_H


#include <stdbool.h>
#include "../config/config.h"

typedef struct map_tile map_tile;
struct map_tile {
    enum color color;
    bool focus;
};

map_tile map[VIRTUAL_W][VIRTUAL_H];

void map_init();

#endif //ANIHILACJA_MAP_H
