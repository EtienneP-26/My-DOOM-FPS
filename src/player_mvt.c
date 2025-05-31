/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** player_mvt
*/

#include "player.h"
#include "map.h"
#include "keybinds.h"
#include "flashlight.h"
#include "sound_manager.h"
#include "save_system.h"
#include "settings.h"
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>
#include <stdio.h>
#include <math.h>

static void handle_forward_movement(float *nx, float *ny, float speed)
{
    sfKeyCode forward_key = get_key_binding("Forward");

    if (forward_key >= 0 && sfKeyboard_isKeyPressed(forward_key)) {
        *nx = player.x + cos(player.angle * M_PI / 180) * speed;
        *ny = player.y - sin(player.angle * M_PI / 180) * speed;
        return;
    }
    *nx = player.x;
    *ny = player.y;
}

static void handle_backward_movement(float *nx, float *ny, float speed)
{
    sfKeyCode backward_key = get_key_binding("Backward");

    if (backward_key >= 0 && sfKeyboard_isKeyPressed(backward_key)) {
        *nx = player.x - cos(player.angle * M_PI / 180) * speed;
        *ny = player.y + sin(player.angle * M_PI / 180) * speed;
    }
}

static void handle_left_movement(float *nx, float *ny, float speed)
{
    sfKeyCode left_key = get_key_binding("Left");

    if (left_key >= 0 && sfKeyboard_isKeyPressed(left_key)) {
        *nx = player.x - cos((player.angle + 90) * M_PI / 180) * speed;
        *ny = player.y + sin((player.angle + 90) * M_PI / 180) * speed;
    }
}

static void handle_right_movement(float *nx, float *ny, float speed)
{
    sfKeyCode right_key = get_key_binding("Right");

    if (right_key >= 0 && sfKeyboard_isKeyPressed(right_key)) {
        *nx = player.x + cos((player.angle + 90) * M_PI / 180) * speed;
        *ny = player.y - sin((player.angle + 90) * M_PI / 180) * speed;
    }
}

static float get_movement_speed(void)
{
    float speed = player_config.move_speed;

    if (sfKeyboard_isKeyPressed(sfKeyLShift))
        speed *= 1.5f;
    return speed;
}

static bool process_movement(float nx, float ny)
{
    if (nx != player.x || ny != player.y) {
        move_player(nx - player.x, ny - player.y);
        play_footstep_sound();
        return true;
    }
    return false;
}

void manage_mvt(float nx, float ny)
{
    float speed = get_movement_speed();

    handle_forward_movement(&nx, &ny, speed);
    handle_backward_movement(&nx, &ny, speed);
    handle_left_movement(&nx, &ny, speed);
    handle_right_movement(&nx, &ny, speed);
    process_movement(nx, ny);
}

static void handle_key_functions(bool f_key, bool f5_key, bool f9_key)
{
    if (f_key && !player.f_key_last_pressed)
        toggle_flashlight();
    player.f_key_last_pressed = f_key;
    if (f5_key && !player.f5_key_last_pressed) {
        if (quick_save())
            printf("Game saved successfully\n");
        else
            printf("Failed to save game\n");
    }
    player.f5_key_last_pressed = f5_key;
    if (f9_key && !player.f9_key_last_pressed) {
        if (quick_load())
            printf("Game loaded successfully\n");
        else
            printf("No save file found or load failed\n");
    }
    player.f9_key_last_pressed = f9_key;
}

static void handle_mouse_look(sfRenderWindow *window, float mouse_sensitivity)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    int deltaX = mouse_pos.x - player.last_mouse_pos.x;
    sfVector2i center_pos =
        {window_config.width / 2, window_config.height / 2};
    float adjusted_sensitivity;
    float user_sensitivity;

    if (player.first_mouse_frame) {
        player.last_mouse_pos = sfMouse_getPositionRenderWindow(window);
        player.first_mouse_frame = false;
        return;
    }
    user_sensitivity = get_sensitivity_value() / 5.0f;
    adjusted_sensitivity = mouse_sensitivity * user_sensitivity;
    player.angle += deltaX * adjusted_sensitivity;
    sfMouse_setPositionRenderWindow(center_pos, window);
    player.last_mouse_pos = center_pos;
}

int handle_player_movement(sfRenderWindow *window, float mouse_sensitivity)
{
    bool f_key = sfKeyboard_isKeyPressed(sfKeyF);
    bool f5_key = sfKeyboard_isKeyPressed(sfKeyF5);
    bool f9_key = sfKeyboard_isKeyPressed(sfKeyF9);

    handle_mouse_look(window, mouse_sensitivity);
    handle_key_functions(f_key, f5_key, f9_key);
    manage_mvt(0.0, 0.0);
    if (sfKeyboard_isKeyPressed(sfKeyEscape)){
        sfRenderWindow_setMouseCursorVisible(window, sfTrue);
        return 1;
    }
    return 0;
}
