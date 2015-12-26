#include <SDL_timer.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map.h"
#include "../list/list.h"

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

map_tile *get_tile_by_window_pos(int x, int y) {
    return &map[x * VIRTUAL_W / WINDOW_W][y * VIRTUAL_H / WINDOW_H];
}

void unfocus_all(){
    for(int x = 0; x < VIRTUAL_W; x++){
        for(int y = 0; y < VIRTUAL_H; y++){
            map[x][y].focus = false;
        }
    }
}

static void get_list_of_neighbours_recursion(list *list1, int x, int y){
    map_tile *tile = &map[x][y];
    if(tile->color == ((map_tile *)list1->first->ptr)->color && list_find_by_ptr(list1, tile) == NULL){
        list_node *a = list_node_new(tile);
        list_add_first(list1, a);
        if(x > 0){
            get_list_of_neighbours_recursion(list1, x - 1, y);
        }
        if(y > 0){
            get_list_of_neighbours_recursion(list1, x, y - 1);
        }
        if(x < VIRTUAL_W - 1){
            get_list_of_neighbours_recursion(list1, x + 1, y);
        }
        if(y < VIRTUAL_H - 1){
            get_list_of_neighbours_recursion(list1, x, y + 1);
        }
    }
}

list *get_list_of_neighbours(int x, int y){
    list *list1 = list_new();
    map_tile *tile = &map[x][y];
    list_node *a = list_node_new(tile);
    list_add_first(list1, a);
    if(x > 0){
        get_list_of_neighbours_recursion(list1, x - 1, y);
    }
    if(y > 0){
        get_list_of_neighbours_recursion(list1, x, y - 1);
    }
    if(x < VIRTUAL_W - 1){
        get_list_of_neighbours_recursion(list1, x + 1, y);
    }
    if(y < VIRTUAL_H - 1){
        get_list_of_neighbours_recursion(list1, x, y + 1);
    }
    return list1;
}

void map_focus_on(int vx, int vy) {
    map_tile *tile = &map[vx][vy];
    if(!tile->focus){
        unfocus_all();
        tile->focus = true;
    }
    list *neighbourhood = get_list_of_neighbours(vx, vy);

    while(list_size(neighbourhood) > 0){
        list_node *current = list_get_first(neighbourhood);
        ((map_tile *)current->ptr)->focus = true;
        list_node_delete(current);
    }
    list_delete(neighbourhood);
}

void map_annihilate(int vx, int vy) {
    list *neighbourhood = get_list_of_neighbours(vx, vy);

    if(list_size(neighbourhood) < 2){
        return;
    }

    while(list_size(neighbourhood) > 0){
        list_node *current = list_get_first(neighbourhood);
        ((map_tile *)current->ptr)->color = DEAD;
        list_node_delete(current);
    }
    list_delete(neighbourhood);
}

static void handle_vertical_gravity(){
    for(int x = 0; x < VIRTUAL_W; x++){
        for(int y = VIRTUAL_H - 2; y >= 0; y--){
            if(map[x][y].color != DEAD && map[x][y + 1].color == DEAD){
                map_tile t = map[x][y];
                map[x][y] = map[x][y + 1];
                map[x][y + 1] = t;
            }
        }
    }
}

static void move_left(int target_x){
    for(int x = target_x; x < VIRTUAL_W - 1; x++){
        for(int y = 0; y < VIRTUAL_H; y++){
            map[x][y] = map[x + 1][y];
        }
    }
    for(int y = 0; y < VIRTUAL_H; y++){
        map[VIRTUAL_W - 1][y].color = DEAD;
    }
}

static void handle_horizontal_gravity(){
    for(int x = 0; x < VIRTUAL_W - 1; x++){
        int non_empty = false;
        for(int y = VIRTUAL_H - 1; y >= 0; y--){
            if(map[x][y].color != DEAD){
                non_empty = true;
                break;
            }
        }
        if(!non_empty){
            move_left(x);
        }
    }
}

void map_update() {
    handle_vertical_gravity();
    handle_horizontal_gravity();
}
