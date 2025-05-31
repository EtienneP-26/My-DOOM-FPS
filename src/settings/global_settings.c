/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** global_settings.c
*/

#include "settings.h"
#include "keybinds.h"

SettingsScene_t *global_settings;

void init_global_settings(sfRenderWindow *window)
{
    if (global_settings != NULL) {
        return;
    }
    global_settings = malloc(sizeof(SettingsScene_t));
    if (global_settings == NULL) {
        fprintf(stderr,
            "Error: Failed to allocate memory for global settings\n");
        return;
    }
    global_settings->window = window;
    malloc_settings_scene(global_settings);
    init_settings_scene(global_settings, window);
    global_settings->goBack = false;
}

void cleanup_global_settings(void)
{
    if (global_settings != NULL) {
        destroy_settings_scene(global_settings);
        free_settings_scene(global_settings);
        free(global_settings);
        global_settings = NULL;
    }
}

int get_sensitivity_value(void)
{
    if (global_settings == NULL || global_settings->sensi == NULL) {
        return 5;
    }
    return global_settings->sensi->value;
}

int get_volume_value(void)
{
    if (global_settings == NULL || global_settings->volume == NULL) {
        return 5;
    }
    return global_settings->volume->value;
}

static keybinding_t *find_key_for_action(const char *action)
{
    if (global_settings == NULL)
        return NULL;
    if (strcmp(action, "Forward") == 0)
        return global_settings->Forward;
    if (strcmp(action, "Backward") == 0)
        return global_settings->Backward;
    if (strcmp(action, "Left") == 0)
        return global_settings->Left;
    if (strcmp(action, "Right") == 0)
        return global_settings->Right;
    if (strcmp(action, "Shoot") == 0)
        return global_settings->shoot;
    return NULL;
}

int get_key_binding(const char *action)
{
    keybinding_t *key = find_key_for_action(action);
    const char *key_str;
    char *key_copy;
    int code = sfKeyUnknown;

    if (key == NULL || key->key == NULL || key->key->Text == NULL)
        return sfKeyUnknown;
    key_str = sfText_getString(key->key->Text);
    if (strcmp(key_str, "Mouse L") == 0)
        return -1;
    if (strcmp(key_str, "Mouse R") == 0)
        return -2;
    if (strcmp(key_str, "Mouse M") == 0)
        return -3;
    key_copy = strdup(key_str);
    if (key_copy) {
        code = finds_keycode(key_copy);
        free(key_copy);
    }
    return code;
}
