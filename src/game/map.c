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
    list *neigbourhood = get_list_of_neighbours(vx, vy);

    while(list_size(neigbourhood) > 0){
        list_node *current = list_get_first(neigbourhood);
        ((map_tile *)current->ptr)->focus = true;
        list_node_delete(current);
    }
}