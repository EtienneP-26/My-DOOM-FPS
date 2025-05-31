/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** map
*/

#ifndef MAP_H
    #define MAP_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include "config.h"

    #define M_PI 3.14159265358979323846

typedef struct map_s {
    int *data;
    int width;
    int height;
} map_t;

extern map_t game_map;

void init_map(void);
void cleanup_map(void);
bool is_wall_at(int x, int y);
bool checkcollision(float x, float y);
sfRectangleShape *create_map_tile(int index);

#endif /* MAP_H */
