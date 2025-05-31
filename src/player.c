/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** player
*/

#include "player.h"
#include "map.h"
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>
#include <stdio.h>
#include <math.h>

player_t player;

void init_player(void)
{
    player.x = 150.0f;
    player.y = 150.0f;
    player.angle = 0.0f;
    player.height = 0.0f;
    player.is_jumping = false;
    player.jump_velocity = 0.0f;
    player.first_mouse_frame = true;
    player.last_mouse_pos = (sfVector2i){0, 0};
    player.f_key_last_pressed = false;
    player.f5_key_last_pressed = false;
    player.f9_key_last_pressed = false;
    player.shape = sfCircleShape_create();
    sfCircleShape_setRadius(player.shape, player_config.radius);
    sfCircleShape_setFillColor(player.shape, sfColor_fromRGB(255, 0, 0));
}

void cleanup_player(void)
{
    sfCircleShape_destroy(player.shape);
}

void move_player(float dx, float dy)
{
    float new_x = player.x + dx;
    float new_y = player.y + dy;

    if (!checkcollision(new_x, new_y)) {
        player.x = new_x;
        player.y = new_y;
    }
}

int update_player_position(sfRenderWindow *window)
{
    sfVector2f pos = {0, 0};

    if (handle_player_movement(window, 0.3f) == 1)
        return 1;
    pos.x = player.x / world_config.rate_map;
    pos.y = player.y / world_config.rate_map;
    sfCircleShape_setPosition(player.shape, pos);
    return 0;
}

void draw_player(sfRenderWindow *window)
{
    sfRenderWindow_drawCircleShape(window, player.shape, NULL);
}
