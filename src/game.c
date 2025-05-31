/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** game
*/

#include "game.h"
#include "config.h"
#include "player.h"
#include "renderer.h"
#include "map.h"
#include "hud.h"
#include "weapon.h"
#include "flashlight.h"
#include "sound_manager.h"
#include "particle.h"
#include "enemy.h"
#include "SFML/Graphics.h"

game_t game;

void init_game(sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);

    init_configurations();
    window_config.width = window_size.x;
    window_config.height = window_size.y;
    window_config.bits_per_pixel = 32;
    game.window = window;
    sfRenderWindow_setFramerateLimit(game.window, render_config.fps);
    sfRenderWindow_setMouseCursorVisible(game.window, sfFalse);
    game.is_running = true;
    init_renderer();
    init_map();
    init_player();
    init_weapon();
    init_flashlight();
    init_sound_manager();
    init_particle_systems();
    init_enemies();
}

int handle_events(void)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game.window, &event)) {
        if (event.type == sfEvtClosed) {
            game.is_running = false;
            sfRenderWindow_setMouseCursorVisible(game.window, sfTrue);
            return 1;
        }
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyM) {
                toggle_sound();
        }
    }
    return 0;
}

int game_loop(void)
{
    int result;

    while (game.is_running && sfRenderWindow_isOpen(game.window)) {
        result = handle_events();
        if (result != 0 || update_player_position(game.window)) {
            return result;
        }
        update_weapon();
        update_sounds(0.0f);
        update_particles();
        render_frame(game.window);
    }
    return 0;
}

void cleanup_game(void)
{
    cleanup_enemies();
    cleanup_particle_systems();
    cleanup_sound_manager();
    cleanup_flashlight();
    cleanup_weapon();
    cleanup_player();
    cleanup_map();
    cleanup_renderer();
}
