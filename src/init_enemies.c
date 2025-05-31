/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** init_enemies
*/

#include "enemy.h"
#include "player.h"
#include "map.h"
#include "config.h"
#include "weapon.h"
#include "sound_manager.h"
#include "raycaster.h"
#include <stdio.h>
#include <math.h>

static void spawn_enemy_at_grid(int grid_x, int grid_y)
{
    float cell_width = (float)world_config.width / map_config.grid_width;
    float cell_height = (float)world_config.height / map_config.grid_height;
    float world_x = (grid_x + 0.5f) * cell_width;
    float world_y = (grid_y + 0.5f) * cell_height;

    spawn_enemy(world_x, world_y);
}

static bool is_valid_enemy_position(int x, int y)
{
    if (x < 0 || x >= game_map.width || y < 0 || y >= game_map.height) {
        return false;
    }
    return game_map.data[y * game_map.width + x] == 0;
}

static void init_enemy_manager(void)
{
    enemy_manager.count = 0;
    enemy_manager.enemy_texture =
        sfTexture_createFromFile("assets/images/enemy_doom.png", NULL);
    if (!enemy_manager.enemy_texture) {
        fprintf(stderr, "Failed to load enemy texture\n");
    }
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemy_manager.enemies[i].alive = false;
    }
}

static void spawn_initial_enemies(void)
{
    if (is_valid_enemy_position(1, 1))
        spawn_enemy_at_grid(1, 1);
    if (is_valid_enemy_position(5, 3))
        spawn_enemy_at_grid(5, 3);
    if (is_valid_enemy_position(10, 5))
        spawn_enemy_at_grid(10, 5);
    if (is_valid_enemy_position(3, 7))
        spawn_enemy_at_grid(3, 7);
    if (is_valid_enemy_position(16, 8))
        spawn_enemy_at_grid(16, 8);
    if (is_valid_enemy_position(18, 11))
        spawn_enemy_at_grid(18, 11);
    if (is_valid_enemy_position(9, 15))
        spawn_enemy_at_grid(9, 15);
    if (is_valid_enemy_position(15, 17))
        spawn_enemy_at_grid(15, 17);
    if (is_valid_enemy_position(2, 17))
        spawn_enemy_at_grid(2, 17);
}

void init_enemies(void)
{
    init_enemy_manager();
    spawn_initial_enemies();
}
