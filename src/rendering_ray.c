/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** rendering_ray
*/

#include "raycaster.h"
#include "map.h"
#include "player.h"
#include "config.h"
#include "flashlight.h"
#include <math.h>

void render_wall_color(sfRectangleShape *wall,
    raycast_result_t result, float light_intensity)
{
    sfColor wall_color;
    int base_shade;

    if (result.hit_wall) {
        base_shade = 255;
        wall_color = sfColor_fromRGB(base_shade, base_shade, base_shade);
        wall_color = apply_lighting(wall_color, light_intensity);
    } else
        wall_color = sfColor_fromRGB(20, 20, 20);
    sfRectangleShape_setFillColor(wall, wall_color);
}

void setup_wall_texture(sfRectangleShape *wall, raycast_result_t result,
    float light_intensity)
{
    sfVector2f texture_size;
    float tex_x;
    sfIntRect texture_rect;
    sfColor wall_color;

    sfRectangleShape_setTexture(wall, wall_texture, sfFalse);
    texture_size.x = (float)sfTexture_getSize(wall_texture).x;
    texture_size.y = (float)sfTexture_getSize(wall_texture).y;
    tex_x = result.tex_x * texture_size.x;
    texture_rect.left = tex_x;
    texture_rect.top = 0;
    texture_rect.width = 1;
    texture_rect.height = texture_size.y;
    sfRectangleShape_setTextureRect(wall, texture_rect);
    wall_color = sfWhite;
    wall_color = apply_lighting(wall_color, light_intensity);
    sfRectangleShape_setFillColor(wall, wall_color);
}

void setup_wall_dimensions(sfRectangleShape *wall, int ray_index,
    raycast_result_t result)
{
    float slice_width = (float)window_config.width /
        (render_config.fov * render_config.precision);
    sfVector2f wall_size = {slice_width, result.wall_height};
    sfVector2f wall_pos = {
        ray_index * slice_width,
        (window_config.height - result.wall_height) / 2
    };

    sfRectangleShape_setSize(wall, wall_size);
    sfRectangleShape_setPosition(wall, wall_pos);
}

float calculate_light_intensity(int ray_index, raycast_result_t result)
{
    float ray_angle = player.angle - (render_config.fov / 2) +
        ((float)ray_index / render_config.precision);
    float angle_diff = ray_angle - player.angle;

    return get_light_intensity(result.distance, angle_diff);
}
