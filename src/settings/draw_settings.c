/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** draw_settings.c
*/

#include "settings.h"
#include "define.h"

static void draw_button(SettingsScene_t *settings, button_t *button)
{
    sfRenderWindow_drawRectangleShape(WINDOW, button->slider, NULL);
    sfRenderWindow_drawText(WINDOW, button->Text, NULL);
}

static void draw_keybind(SettingsScene_t *settings, keybinding_t *keyBinding)
{
    draw_button(settings, keyBinding->action);
    draw_button(settings, keyBinding->key);
}

static void draw_sensivol(SettingsScene_t *settings, sensivol_t *module)
{
    sfRenderWindow_drawRectangleShape(WINDOW,
        module->slider, NULL);
    sfRenderWindow_drawText(WINDOW, module->Nbr, NULL);
    sfRenderWindow_drawText(WINDOW, module->Text, NULL);
    sfRenderWindow_drawRectangleShape(WINDOW,
        module->plus->slider, NULL);
    sfRenderWindow_drawText(WINDOW, module->plus->Text, NULL);
    sfRenderWindow_drawRectangleShape(WINDOW,
        module->minus->slider, NULL);
    sfRenderWindow_drawText(WINDOW, module->minus->Text, NULL);
}

static void draw_screen_size(SettingsScene_t *settings)
{
    sfRenderWindow_drawRectangleShape(WINDOW, SCREENB, NULL);
    sfRenderWindow_drawText(WINDOW, SCREENT, NULL);
    draw_button(settings, settings->sizescreen->fullscreen);
    draw_button(settings, settings->sizescreen->windowed);
}

static void draw_scenekeybind(SettingsScene_t *settings, scenebinding_t *bind)
{
    sfRenderWindow_drawRectangleShape(WINDOW, bind->slider, NULL);
    sfRenderWindow_drawText(WINDOW, bind->Text, NULL);
}

void draw_settings_scene(SettingsScene_t *settings)
{
    sfRenderWindow_clear(WINDOW, sfColor_fromRGB(0, 0, 0));
    sfRenderWindow_drawSprite(WINDOW, BACKGROUNDSPRITE, NULL);
    draw_sensivol(settings, settings->volume);
    draw_sensivol(settings, settings->sensi);
    draw_screen_size(settings);
    draw_button(settings, settings->back);
    draw_button(settings, settings->title);
    draw_keybind(settings, settings->shoot);
    draw_keybind(settings, settings->Forward);
    draw_keybind(settings, settings->Backward);
    draw_keybind(settings, settings->Left);
    draw_keybind(settings, settings->Right);
    if (settings->scenebinding->is_binding)
        draw_scenekeybind(settings, settings->scenebinding);
    sfRenderWindow_display(WINDOW);
}
