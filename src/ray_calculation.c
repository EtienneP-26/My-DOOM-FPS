/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** ray_calculation
*/

#include "raycaster.h"
#include "map.h"
#include "player.h"
#include "config.h"
#include "flashlight.h"
#include <math.h>

void set_wall_height(raycast_result_t *result, float ray_angle)
{
    result->distance = result->distance *
        cos((ray_angle - player.angle) * M_PI / 180);
    if (result->distance > 0) {
        result->wall_height = window_config.height / (result->distance / 40);
        if (result->wall_height > window_config.height)
            result->wall_height = window_config.height;
    } else
        result->wall_height = window_config.height;
}

float get_ray_max_distance(float ray_angle)
{
    float angle_diff = ray_angle - player.angle;
    float max_distance = render_config.max_distance;

    while (angle_diff > 180)
        angle_diff -= 360;
    while (angle_diff < -180)
        angle_diff += 360;
    if (flashlight.enabled && fabs(angle_diff) <=
            flashlight.cone_angle / 2.0f) {
        max_distance = flashlight.max_distance;
    }
    return max_distance;
}

int step_ray(float *ray_x, float *ray_y, float ray_angle, float step)
{
    *ray_x += cos(ray_angle * M_PI / 180) * step;
    *ray_y -= sin(ray_angle * M_PI / 180) * step;
    return 1;
}

void initialize_ray(float *ray_x, float *ray_y,
    ray_context_t *context)
{
    *ray_x = player.x;
    *ray_y = player.y;
    context->cell_size_x = (world_config.width / map_config.grid_width);
    context->cell_size_y = (world_config.height / map_config.grid_height);
}

static bool check_wall_hit(raycast_result_t *result, float ray_x, float ray_y,
    ray_context_t context)
{
    int map_x = (int)(ray_x / context.cell_size_x);
    int map_y = (int)(ray_y / context.cell_size_y);

    if (is_wall_at(map_x, map_y)) {
        process_wall_hit(result, ray_x, ray_y, context);
        return true;
    }
    return false;
}

raycast_result_t cast_ray(float ray_angle, float step)
{
    raycast_result_t result = {ray_angle, 0, 0, false, 0, 0.0f, 0.0f, 0.0f};
    float ray_x;
    float ray_y;
    float max_distance;
    ray_context_t context;

    initialize_ray(&ray_x, &ray_y, &context);
    max_distance = get_ray_max_distance(ray_angle);
    while (!result.hit_wall && result.distance < max_distance) {
        result.distance += step_ray(&ray_x, &ray_y, ray_angle, step) * step;
        if (check_wall_hit(&result, ray_x, ray_y, context))
            break;
    }
    set_wall_height(&result, ray_angle);
    return result;
}
