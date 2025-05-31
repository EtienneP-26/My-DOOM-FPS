/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** texture_mapping
*/

#include "raycaster.h"
#include "map.h"
#include "player.h"
#include "config.h"
#include "flashlight.h"
#include <math.h>

float calculate_texture_x(float hit_x, float hit_y, float cell_size_x,
    float cell_size_y)
{
    float hit_position_x;
    float hit_position_y;
    float epsilon = 0.01f;
    float edge_result;

    hit_position_x = fmodf(hit_x, cell_size_x) / cell_size_x;
    hit_position_y = fmodf(hit_y, cell_size_y) / cell_size_y;
    edge_result = handle_edge_cases(hit_position_x, hit_position_y, epsilon);
    if (edge_result >= 0.0f)
        return edge_result;
    return handle_texture_mapping(hit_position_x, hit_position_y);
}

void process_wall_hit(raycast_result_t *result,
    float ray_x, float ray_y,
    ray_context_t context)
{
    result->hit_wall = true;
    result->wall_type = 1;
    result->hit_x = ray_x;
    result->hit_y = ray_y;
    result->tex_x = calculate_texture_x(ray_x, ray_y,
        context.cell_size_x, context.cell_size_y);
}
