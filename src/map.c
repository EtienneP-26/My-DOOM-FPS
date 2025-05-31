/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** map
*/

#include "map.h"
#include <stdlib.h>

map_t game_map;

const int default_map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

void init_map(void)
{
    game_map.width = map_config.grid_width;
    game_map.height = map_config.grid_height;
    game_map.data = malloc(sizeof(int) * game_map.width * game_map.height);
    for (int i = 0; i < game_map.width * game_map.height; i++) {
        game_map.data[i] = default_map[i];
    }
}

void cleanup_map(void)
{
    free(game_map.data);
}

bool is_wall_at(int x, int y)
{
    if (x < 0 || x >= game_map.width || y < 0 || y >= game_map.height) {
        return true;
    }
    return game_map.data[y * game_map.width + x] == 1;
}

bool checkcollision(float x, float y)
{
    int mapX = (int)(x / (world_config.width / map_config.grid_width));
    int mapY = (int)(y / (world_config.height / map_config.grid_height));

    return is_wall_at(mapX, mapY);
}

sfRectangleShape* create_map_tile(int index)
{
    sfRectangleShape *shape = sfRectangleShape_create();
    int x = index % game_map.width;
    int y = index / game_map.width;
    sfVector2f size = {
        world_config.width / game_map.width / world_config.rate_map,
        world_config.height / game_map.height / world_config.rate_map
    };
    sfVector2f position = {x * size.x, y * size.y};

    sfRectangleShape_setSize(shape, size);
    sfRectangleShape_setPosition(shape, position);
    sfRectangleShape_setFillColor(shape, sfColor_fromRGB(150, 150, 150));
    return shape;
}
