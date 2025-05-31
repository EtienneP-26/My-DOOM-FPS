/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** destroy_settings.c
*/

#include "settings.h"
#include "define.h"

static void destroy_button(button_t *button)
{
    sfRectangleShape_destroy(button->slider);
    sfText_destroy(button->Text);
}

static void destroy_key(keybinding_t *key)
{
    destroy_button(key->action);
    destroy_button(key->key);
}

static void destroy_screen_size(SettingsScene_t *settings)
{
    sfRectangleShape_destroy(settings->sizescreen->SizescreenShape);
    sfText_destroy(settings->sizescreen->SizescreenText);
    destroy_button(settings->sizescreen->fullscreen);
    destroy_button(settings->sizescreen->windowed);
}

static void destroy_sensivol(sensivol_t *module)
{
    sfRectangleShape_destroy(module->slider);
    sfText_destroy(module->Nbr);
    sfText_destroy(module->Text);
    destroy_button(module->plus);
    destroy_button(module->minus);
}

static void destroy_background(SettingsScene_t *settings)
{
    sfTexture_destroy(settings->background->Background);
    sfSprite_destroy(settings->background->BackgroundSprite);
}

static void destroy_keybinding(scenebinding_t *bind)
{
    sfRectangleShape_destroy(bind->slider);
    sfText_destroy(bind->Text);
}

void destroy_settings_scene(SettingsScene_t *settings)
{
    destroy_button(settings->back);
    destroy_button(settings->title);
    destroy_screen_size(settings);
    destroy_sensivol(settings->sensi);
    destroy_sensivol(settings->volume);
    destroy_background(settings);
    destroy_key(settings->shoot);
    destroy_key(settings->Forward);
    destroy_key(settings->Backward);
    destroy_key(settings->Left);
    destroy_key(settings->Right);
    destroy_keybinding(settings->scenebinding);
    sfFont_destroy(settings->font);
    if (settings->fullscreen_view) {
        sfView_destroy(settings->fullscreen_view);
        settings->fullscreen_view = NULL;
    }
}
