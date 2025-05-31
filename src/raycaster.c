/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** raycaster
*/

#include "raycaster.h"
#include "map.h"
#include "player.h"
#include "config.h"
#include "flashlight.h"
#include <math.h>

float handle_edge_cases(float hit_position_x, float hit_position_y,
    float epsilon)
{
    if (hit_position_x < epsilon)
        return hit_position_y;
    if (hit_position_x > 1.0f - epsilon)
        return 1.0f - hit_position_y;
    if (hit_position_y < epsilon)
        return 1.0f - hit_position_x;
    if (hit_position_y > 1.0f - epsilon)
        return hit_position_x;
    return -1.0f;
}

float handle_texture_mapping(float hit_position_x, float hit_position_y)
{
    float dist_x = fminf(hit_position_x, 1.0f - hit_position_x);
    float dist_y = fminf(hit_position_y, 1.0f - hit_position_y);

    if (dist_x < dist_y) {
        return (hit_position_x < 0.5f) ?
            hit_position_y : 1.0f - hit_position_y;
    }
    return (hit_position_y < 0.5f) ?
        1.0f - hit_position_x : hit_position_x;
}

void render_wall_slice(sfRenderWindow *window,
    int ray_index, raycast_result_t result)
{
    sfRectangleShape *wall;
    float light_intensity;

    wall = sfRectangleShape_create();
    setup_wall_dimensions(wall, ray_index, result);
    light_intensity = calculate_light_intensity(ray_index, result);
    if (result.hit_wall && wall_texture)
        setup_wall_texture(wall, result, light_intensity);
    else
        render_wall_color(wall, result, light_intensity);
    sfRenderWindow_drawRectangleShape(window, wall, NULL);
    sfRectangleShape_destroy(wall);
}

void draw_ray(sfRenderWindow *window, float ray_angle, raycast_result_t result)
{
    float ray_end_x = player.x + cos(ray_angle * M_PI / 180) * result.distance;
    float ray_end_y = player.y - sin(ray_angle * M_PI / 180) * result.distance;
    sfVertex line[2] = {
        {{player.x / world_config.rate_map,
            player.y / world_config.rate_map}, sfWhite, {0, 0}},
        {{ray_end_x / world_config.rate_map,
                ray_end_y / world_config.rate_map},
            result.hit_wall ? sfRed : sfGreen, {0, 0}}
    };

    sfRenderWindow_drawPrimitives(window, line, 2, sfLines, NULL);
}

void render_view(sfRenderWindow *window)
{
    float strart_angle = player.angle - (render_config.fov / 2);
    raycast_result_t result;
    float ray_angle;

    for (int i = 0; i < render_config.fov * render_config.precision; i++) {
        ray_angle = strart_angle + ((float)i / render_config.precision);
        result = cast_ray(ray_angle, 1.0f);
        render_wall_slice(window, i, result);
        draw_ray(window, ray_angle, result);
    }
}
