/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** settings.c
*/

#include "settings.h"
#include "define.h"

int start_setting(sfRenderWindow *windows)
{
    sfEvent event;

    if (!windows) {
        return EXIT_FAILURE;
    }
    if (global_settings == NULL) {
        init_global_settings(windows);
    } else {
        global_settings->goBack = false;
    }
    while (!global_settings->goBack) {
        if (handle_settings_events(global_settings, &event) == 100) {
            sfRenderWindow_close(global_settings->window);
            return 100;
        }
        draw_settings_scene(global_settings);
    }
    return 0;
}
