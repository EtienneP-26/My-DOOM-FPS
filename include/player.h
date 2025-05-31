/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** player
*/

#ifndef PLAYER_H
    #define PLAYER_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include "config.h"

typedef struct player_s {
    float x;
    float y;
    float angle;
    float height;
    bool is_jumping;
    float jump_velocity;
    sfCircleShape *shape;
    sfVector2i last_mouse_pos;
    bool first_mouse_frame;
    bool f_key_last_pressed;
    bool f5_key_last_pressed;
    bool f9_key_last_pressed;
} player_t;

extern player_t player;

void init_player(void);
void cleanup_player(void);
int update_player_position(sfRenderWindow *window);
int handle_player_movement(sfRenderWindow *window, float mouse_sensitivity);
void process_jump(void);
void move_player(float dx, float dy);
void draw_player(sfRenderWindow *window);

#endif /* PLAYER_H */
