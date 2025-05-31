/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** bind_event.c
*/

#include "settings.h"
#include "keybinds.h"

static void handle_binding_mouse(SettingsScene_t *settings,
    keybinding_t *keybind, sfEvent event)
{
    if (event.type == sfEvtMouseButtonPressed) {
        if (event.mouseButton.button == sfMouseLeft) {
            sfText_setString(keybind->key->Text, "Mouse L");
            settings->scenebinding->is_binding = false;
            keybind->is_binding = false;
        }
        if (event.mouseButton.button == sfMouseRight) {
            sfText_setString(keybind->key->Text, "Mouse R");
            settings->scenebinding->is_binding = false;
            keybind->is_binding = false;
        }
        if (event.mouseButton.button == sfMouseMiddle) {
            sfText_setString(keybind->key->Text, "Mouse M");
            settings->scenebinding->is_binding = false;
            keybind->is_binding = false;
        }
    }
}

void handle_binding_events(SettingsScene_t *settings,
    keybinding_t *keybind, sfEvent event)
{
    int index;

    if (event.type == sfEvtKeyPressed) {
        index = event.key.code;
        if (index == -1) {
            settings->scenebinding->is_binding = false;
            keybind->is_binding = false;
            return;
        }
        if (!strcmp(keybinds_list[index], "Escape")) {
            settings->scenebinding->is_binding = false;
            keybind->is_binding = false;
            return;
        }
        sfText_setString(keybind->key->Text, keybinds_list[index]);
        settings->scenebinding->is_binding = false;
        keybind->is_binding = false;
    }
    handle_binding_mouse(settings, keybind, event);
}
