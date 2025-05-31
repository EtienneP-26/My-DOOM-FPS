/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** draw_hud
*/

#include "hud.h"
#include "config.h"
#include "flashlight.h"
#include <unistd.h>
#include <stdio.h>

void draw_hud_bar(sfRenderWindow *window)
{
    sfRectangleShape *hud_bar = sfRectangleShape_create();
    sfRectangleShape *hud_border = sfRectangleShape_create();
    int bar_height = 50;

    sfRectangleShape_setSize(hud_bar,
        (sfVector2f){window_config.width, bar_height});
    sfRectangleShape_setPosition(hud_bar,
        (sfVector2f){0, window_config.height - bar_height});
    sfRectangleShape_setFillColor(hud_bar, (sfColor){65, 65, 75, 255});
    sfRectangleShape_setSize(hud_border, (sfVector2f){window_config.width, 2});
    sfRectangleShape_setPosition(hud_border,
        (sfVector2f){0, window_config.height - bar_height - 2});
    sfRectangleShape_setFillColor(hud_border, (sfColor){160, 160, 160, 255});
    sfRenderWindow_drawRectangleShape(window, hud_bar, NULL);
    sfRenderWindow_drawRectangleShape(window, hud_border, NULL);
    sfRectangleShape_destroy(hud_bar);
    sfRectangleShape_destroy(hud_border);
}

void draw_hud(sfRenderWindow *window, sfFont *hud_font)
{
    draw_crosshair(window);
    draw_hud_bar(window);
    draw_stats(window, hud_font);
    cleanup_hud(hud_font);
}
