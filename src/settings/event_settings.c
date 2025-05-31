/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** event_settings.c
*/

#include "settings.h"
#include "define.h"

static void handle_sensivol_events(sensivol_t *module, sfVector2i mousePos)
{
    sfFloatRect sensiminusBounds =
    sfRectangleShape_getGlobalBounds(module->minus->slider);
    sfFloatRect sensiplusBounds =
    sfRectangleShape_getGlobalBounds(module->plus->slider);
    char moduleStr[3];

    if (sfFloatRect_contains(&sensiminusBounds, mousePos.x, mousePos.y) &&
    module->value >= 1)
        module->value--;
    if (sfFloatRect_contains(&sensiplusBounds, mousePos.x, mousePos.y) &&
    module->value < 10)
        module->value++;
    sprintf(moduleStr, "%d", module->value);
    sfText_setString(module->Nbr, moduleStr);
}

static void handle_back_events(SettingsScene_t *settings,
    sfVector2i mousePos)
{
    sfFloatRect backBounds =
    sfRectangleShape_getGlobalBounds(BACKB);

    if (sfFloatRect_contains(&backBounds, mousePos.x, mousePos.y))
        settings->goBack = true;
}

static void handle_wsize_events(SettingsScene_t *settings, sfVector2i mousePos)
{
    sfFloatRect windowBounds = sfRectangleShape_getGlobalBounds(SWINDOWB);
    sfView *view;
    sfVector2f viewSize = {1600.0f, 900.0f};
    sfVector2f viewCenter = {800.0f, 450.0f};

    if (sfFloatRect_contains(&windowBounds, mousePos.x, mousePos.y)) {
        view = sfView_create();
        sfRenderWindow_setSize(WINDOW, (sfVector2u){1600, 900});
        sfView_setSize(view, viewSize);
        sfView_setCenter(view, viewCenter);
        sfRenderWindow_setView(WINDOW, view);
        if (settings->fullscreen_view) {
            sfView_destroy(settings->fullscreen_view);
            settings->fullscreen_view = NULL;
        }
        resize_elements(settings, 1.0f);
        settings->fullscreen_view = view;
    }
}

static void handle_fsize_events(SettingsScene_t *settings, sfVector2i mousePos)
{
    sfFloatRect fullscreenBounds =
    sfRectangleShape_getGlobalBounds(FULLSCREENB);
    sfView *view;
    sfVector2f viewSize = {1920.0f, 945.0f};
    sfVector2f viewCenter = {960.0f, 472.5f};

    if (sfFloatRect_contains(&fullscreenBounds, mousePos.x, mousePos.y)) {
        view = sfView_create();
        sfRenderWindow_setSize(WINDOW, (sfVector2u){1920, 945});
        sfView_setSize(view, viewSize);
        sfView_setCenter(view, viewCenter);
        sfRenderWindow_setView(WINDOW, view);
        resize_elements(settings, 1.2f);
        settings->fullscreen_view = view;
    }
}

static void handle_binding(SettingsScene_t *settings, sfEvent event,
    keybinding_t *keybind)
{
    if (keybind->is_binding) {
        handle_binding_events(settings, keybind, event);
    }
}

static void select_key(keybinding_t *keybind,
    sfVector2i mousePos, SettingsScene_t *settings)
{
    sfFloatRect keyBounds;

    keyBounds = sfRectangleShape_getGlobalBounds(keybind->key->slider);
    if (sfFloatRect_contains(&keyBounds, mousePos.x, mousePos.y)) {
        keybind->is_binding = true;
        settings->scenebinding->is_binding = true;
    }
}

static void handle_action(SettingsScene_t *settings, sfEvent *event,
    sfVector2i mousePos)
{
    if (settings->scenebinding->is_binding) {
        handle_binding(settings, *event, settings->shoot);
        handle_binding(settings, *event, settings->Forward);
        handle_binding(settings, *event, settings->Backward);
        handle_binding(settings, *event, settings->Left);
        handle_binding(settings, *event, settings->Right);
    } else {
        handle_sensivol_events(settings->sensi, mousePos);
        handle_sensivol_events(settings->volume, mousePos);
        handle_back_events(settings, mousePos);
        handle_wsize_events(settings, mousePos);
        handle_fsize_events(settings, mousePos);
        select_key(settings->shoot, mousePos, settings);
        select_key(settings->Forward, mousePos, settings);
        select_key(settings->Backward, mousePos, settings);
        select_key(settings->Left, mousePos, settings);
        select_key(settings->Right, mousePos, settings);
    }
}

int handle_settings_events(SettingsScene_t *settings, sfEvent *event)
{
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(WINDOW);

    while (sfRenderWindow_pollEvent(WINDOW, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(WINDOW);
            return 100;
        }
        if (event->type == sfEvtMouseButtonPressed ||
            event->type == sfEvtKeyPressed) {
            handle_action(settings, event, mousePos);
        }
    }
    return 0;
}
