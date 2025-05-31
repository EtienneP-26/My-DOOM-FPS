/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** enemy
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

enemy_manager_t enemy_manager;

void cleanup_enemies(void)
{
    if (enemy_manager.enemy_texture) {
        sfTexture_destroy(enemy_manager.enemy_texture);
    }
    for (int i = 0; i < enemy_manager.count; i++) {
        if (enemy_manager.enemies[i].sprite) {
            sfSprite_destroy(enemy_manager.enemies[i].sprite);
        }
    }
}

static void setup_enemy_attributes(enemy_t *enemy, float x, float y)
{
    enemy->x = x;
    enemy->y = y;
    enemy->alive = true;
    enemy->texture = enemy_manager.enemy_texture;
    enemy->sprite = sfSprite_create();
}

void spawn_enemy(float x, float y)
{
    int mapX;
    int mapY;
    enemy_t *enemy;

    if (enemy_manager.count >= MAX_ENEMIES) {
        fprintf(stderr, "Cannot spawn more enemies, maximum reached\n");
        return;
    }
    mapX = (int)(x / (world_config.width / map_config.grid_width));
    mapY = (int)(y / (world_config.height / map_config.grid_height));
    if (is_wall_at(mapX, mapY)) {
        fprintf(stderr, "Cannot spawn enemy at (%f, %f): wall present\n",
            x, y);
        return;
    }
    enemy = &enemy_manager.enemies[enemy_manager.count];
    setup_enemy_attributes(enemy, x, y);
    if (enemy->texture && enemy->sprite)
        sfSprite_setTexture(enemy->sprite, enemy->texture, sfTrue);
    enemy_manager.count++;
}

static void configure_minimap_circle(sfCircleShape *shape,
    float radius, sfVector2f position)
{
    sfCircleShape_setRadius(shape, radius);
    sfCircleShape_setPosition(shape, position);
    sfCircleShape_setFillColor(shape, sfRed);
}

void draw_enemy_on_minimap(sfRenderWindow *window, enemy_t *enemy)
{
    sfCircleShape *shape;
    float radius;
    sfVector2f position;

    shape = sfCircleShape_create();
    radius = player_config.radius / world_config.rate_map;
    position.x = enemy->x / world_config.rate_map - radius;
    position.y = enemy->y / world_config.rate_map - radius;
    configure_minimap_circle(shape, radius, position);
    sfRenderWindow_drawCircleShape(window, shape, NULL);
    sfCircleShape_destroy(shape);
}

void render_enemies(sfRenderWindow *window)
{
    for (int i = 0; i < enemy_manager.count; i++) {
        if (enemy_manager.enemies[i].alive) {
            draw_enemy_on_minimap(window, &enemy_manager.enemies[i]);
            render_enemy_sprite(window, &enemy_manager.enemies[i]);
        }
    }
}

static void normalize_angle_value(float *angle)
{
    while (*angle < 0)
        *angle += 360.0f;
    while (*angle >= 360.0f)
        *angle -= 360.0f;
}

static float calculate_angle_diff(float angle_a, float angle_b)
{
    float angle_diff;

    normalize_angle_value(&angle_a);
    normalize_angle_value(&angle_b);
    angle_diff = fabs(angle_a - angle_b);
    if (angle_diff > 180.0f) {
        angle_diff = 360.0f - angle_diff;
    }
    return angle_diff;
}

static bool check_enemy_hit(enemy_t *enemy, float angle)
{
    float dx;
    float dy;
    float distance;
    float angle_to_enemy;
    float angle_diff;

    dx = enemy->x - player.x;
    dy = enemy->y - player.y;
    distance = sqrt(dx * dx + dy * dy);
    if (distance > render_config.max_distance)
        return false;
    angle_to_enemy = atan2(-dy, dx) * 180.0f / M_PI;
    angle_diff = calculate_angle_diff(angle, angle_to_enemy);
    if (angle_diff <= 5.0f)
        return true;
    return false;
}

bool shoot_enemy(float angle)
{
    if (!weapon.is_firing) {
        return false;
    }
    for (int i = 0; i < enemy_manager.count; i++) {
        if (!enemy_manager.enemies[i].alive)
            continue;
        if (check_enemy_hit(&enemy_manager.enemies[i], angle)) {
            enemy_manager.enemies[i].alive = false;
            return true;
        }
    }
    return false;
}
