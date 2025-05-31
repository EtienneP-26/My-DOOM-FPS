/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** config
*/

#include "config.h"

window_config_t window_config;
world_config_t world_config;
map_config_t map_config;
player_config_t player_config;
render_config_t render_config;

const sfContextSettings sfml_settings = {
    .depthBits = 0,
    .stencilBits = 0,
    .antialiasingLevel = 8,
    .majorVersion = 2,
    .minorVersion = 0,
    .sRgbCapable = sfFalse};

void init_configurations(void)
{
    world_config.width = 900;
    world_config.height = 900;
    world_config.scale_factor = 1.0;
    world_config.rate_map = 5;
    map_config.grid_width = 20;
    map_config.grid_height = 20;
    player_config.move_speed = 5.0f;
    player_config.rotate_speed = 10.0f;
    player_config.radius = 1.0f;
    player_config.jump_force = 15.0f;
    player_config.gravity = 1.0f;
    render_config.fov = 90.0f;
    render_config.precision = 10;
    render_config.max_distance = 500;
    render_config.fps = 30;
}
