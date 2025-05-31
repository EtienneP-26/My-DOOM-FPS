/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** malloc_settings.c
*/

#include "settings.h"
#include "define.h"

void malloc_settings_scene(SettingsScene_t *settings)
{
    settings->background = malloc(sizeof(background_t));
    settings->sizescreen = malloc(sizeof(sizescreen_t));
    settings->back = malloc(sizeof(button_t));
    settings->title = malloc(sizeof(button_t));
    settings->sensi = malloc(sizeof(sensivol_t));
    settings->volume = malloc(sizeof(sensivol_t));
    settings->shoot = malloc(sizeof(keybinding_t));
    settings->Forward = malloc(sizeof(keybinding_t));
    settings->Backward = malloc(sizeof(keybinding_t));
    settings->Left = malloc(sizeof(keybinding_t));
    settings->Right = malloc(sizeof(keybinding_t));
    settings->scenebinding = malloc(sizeof(keybinding_t));
    settings->sizescreen->windowed = malloc(sizeof(button_t));
    settings->sizescreen->fullscreen = malloc(sizeof(button_t));
    settings->sensi->plus = malloc(sizeof(button_t));
    settings->sensi->minus = malloc(sizeof(button_t));
    settings->volume->plus = malloc(sizeof(button_t));
    settings->volume->minus = malloc(sizeof(button_t));
}

void free_settings_scene(SettingsScene_t *settings)
{
    free(settings->sizescreen->windowed);
    free(settings->sizescreen->fullscreen);
    free(settings->sizescreen);
    free(settings->sensi->plus);
    free(settings->sensi->minus);
    free(settings->sensi);
    free(settings->volume->plus);
    free(settings->volume->minus);
    free(settings->volume);
    free(settings->back);
    free(settings->title);
    free(settings->shoot);
    free(settings->Forward);
    free(settings->Backward);
    free(settings->Left);
    free(settings->Right);
    free(settings->scenebinding);
    free(settings->background);
}
