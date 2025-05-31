/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** render_enemy_sprite
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

static float calculate_sprite_size(float distance)
{
    float sprite_scale_factor = 25.0f;
    float min_distance = 100.0f;
    float adjusted_distance = distance < min_distance ? distance :
        min_distance + (distance - min_distance) * 0.4f;
    float sprite_size = (800.0f / adjusted_distance) * sprite_scale_factor;

    return sprite_size;
}

static bool is_enemy_visible(float dx, float dy, float distance)
{
    float ray_angle;
    raycast_result_t result;
    float relative_angle;

    ray_angle = atan2(-dy, dx) * 180.0f / M_PI;
    result = cast_ray(ray_angle, 0.1f);
    relative_angle = player.angle - ray_angle;
    while (relative_angle < -180.0f)
        relative_angle += 360.0f;
    while (relative_angle > 180.0f)
        relative_angle -= 360.0f;
    if (result.hit_wall && result.distance < distance)
        return false;
    if (distance > render_config.max_distance)
        return false;
    if (fabs(relative_angle) > render_config.fov / 1.5f)
        return false;
    return true;
}

static void normalize_angle(float *angle)
{
    while (*angle < -180.0f)
        *angle += 360.0f;
    while (*angle > 180.0f)
        *angle -= 360.0f;
}

static void calculate_sprite_position(float dx, float dy, float *screen_pos_x,
    float *y_pos)
{
    float ray_angle;
    float relative_angle;
    float screen_center;
    float relative_position;
    float sprite_vertical_offset;

    ray_angle = atan2(-dy, dx) * 180.0f / M_PI;
    relative_angle = player.angle - ray_angle;
    screen_center = window_config.width / 2.0f;
    sprite_vertical_offset = 50.0f;
    *y_pos = window_config.height / 2 + sprite_vertical_offset;
    normalize_angle(&relative_angle);
    relative_position =
        (relative_angle / render_config.fov) * window_config.width;
    *screen_pos_x = screen_center - relative_position;
}

static void set_sprite_attributes(sfSprite *sprite, float screen_pos_x,
    float y_pos, float sprite_size)
{
    sfVector2u texture_size;

    texture_size = sfTexture_getSize(enemy_manager.enemy_texture);
    sfSprite_setOrigin(sprite,
        (sfVector2f){texture_size.x / 2, texture_size.y / 2});
    sfSprite_setPosition(sprite, (sfVector2f){screen_pos_x, y_pos});
    sfSprite_setScale(sprite, (sfVector2f)
        {sprite_size / texture_size.x, sprite_size / texture_size.y});
}

static void position_sprite(sfSprite *sprite, float dx, float dy,
    float sprite_size)
{
    float screen_pos_x;
    float y_pos;

    calculate_sprite_position(dx, dy, &screen_pos_x, &y_pos);
    set_sprite_attributes(sprite, screen_pos_x, y_pos, sprite_size);
}

static void apply_lighting(sfSprite *sprite, float distance)
{
    float light_intensity = 1.0f;

    if (distance > 50.0f)
        light_intensity = 1.0f - fminf((distance - 50.0f) / 300.0f, 0.8f);
    sfSprite_setColor(sprite, sfColor_fromRGBA(
        255 * light_intensity,
        255 * light_intensity,
        255 * light_intensity,
        255
    ));
}

static void create_enemy_sprite(enemy_t *enemy)
{
    enemy->sprite = sfSprite_create();
    if (enemy->sprite) {
        sfSprite_setTexture(enemy->sprite,
            enemy_manager.enemy_texture, sfTrue);
    }
}

void render_enemy_sprite(sfRenderWindow *window, enemy_t *enemy)
{
    float dx = enemy->x - player.x;
    float dy = enemy->y - player.y;
    float distance = sqrt(dx * dx + dy * dy);
    float sprite_size;

    if (!is_enemy_visible(dx, dy, distance))
        return;
    sprite_size = calculate_sprite_size(distance);
    if (sprite_size < 10.0f)
        return;
    if (enemy->sprite == NULL) {
        create_enemy_sprite(enemy);
    }
    position_sprite(enemy->sprite, dx, dy, sprite_size);
    apply_lighting(enemy->sprite, distance);
    sfRenderWindow_drawSprite(window, enemy->sprite, NULL);
}
