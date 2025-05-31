/*
** EPITECH PROJECT, 2025
** My-DOOM
** File description:
** menu
*/

#include "menu_sett.h"

static menu_t *innit_menu(sfRenderWindow *window)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    menu->button1_texture = sfTexture_createFromFile(
        "assets/images/menu/load.png", NULL);
    if (!menu->button1_texture)
        return NULL;
    menu->button1_sprite = sfSprite_create();
    sfSprite_setTexture(menu->button1_sprite, menu->button1_texture, sfTrue);
    menu->button2_texture = sfTexture_createFromFile(
        "assets/images/menu/create_game.png", NULL);
    if (!menu->button2_texture)
        return NULL;
    menu->button2_sprite = sfSprite_create();
    sfSprite_setTexture(menu->button2_sprite, menu->button2_texture, sfTrue);
    menu = put_background(menu, window);
    return menu;
}

sfClock *display_menu(menu_t *menu, sfRenderWindow *window,
    sfClock *clock)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, menu->background_sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->button1_sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->button2_sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->button3_sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->logo_sprite, NULL);
    sfRenderWindow_display(window);
    sfClock_restart(clock);
    return clock;
}

static void place_sprite(menu_t *menu, sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f load_pos = {
        (window_size.x - 200) / 2 - 35,
        (window_size.y - 200) / 2 + 100};
    sfVector2f create_game_pos = {
        (window_size.x - 200) / 2 - 50,
        (window_size.y - 200) / 2 + 300};
    sfVector2f bg_position = {0, 0};
    sfVector2f exit_pos = {
        (window_size.x - 200) / 2 + 650,
        (window_size.y - 200) / 2 + 400};

    sfSprite_setPosition(menu->background_sprite, bg_position);
    sfSprite_setPosition(menu->button1_sprite, load_pos);
    sfSprite_setPosition(menu->button2_sprite, create_game_pos);
    sfSprite_setPosition(menu->button3_sprite, exit_pos);
    sfSprite_setScale(menu->background_sprite, (sfVector2f){2.5f, 2.5f});
    sfSprite_setScale(menu->button1_sprite, (sfVector2f){0.4f, 0.4f});
    sfSprite_setScale(menu->button2_sprite, (sfVector2f){0.4f, 0.4f});
    sfSprite_setScale(menu->button3_sprite, (sfVector2f){0.25f, 0.25f});
}

static int next_scene(menu_t *menu, int x, int y)
{
    sfFloatRect play_bounds = sfSprite_getGlobalBounds(menu->button1_sprite);
    sfFloatRect setting_bounds = sfSprite_getGlobalBounds(
        menu->button2_sprite);
    sfFloatRect exit_bounds = sfSprite_getGlobalBounds(menu->button3_sprite);

    if (sfFloatRect_contains(&play_bounds, x, y))
        return 3;
    if (sfFloatRect_contains(&setting_bounds, x, y))
        return 4;
    if (sfFloatRect_contains(&exit_bounds, x, y))
        return 0;
    return 1;
}

static void handle_menu_events(sfRenderWindow *window, menu_t *menu)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft)
        menu->status = next_scene(menu, event.mouseButton.x,
            event.mouseButton.y);
}

int play_menu(sfRenderWindow *window)
{
    menu_t *menu = innit_menu(window);
    sfClock *clock = sfClock_create();

    if (!menu)
        return 84;
    place_sprite(menu, window);
    display_menu(menu, window, clock);
    menu->status = 1;
    while (sfRenderWindow_isOpen(window) && menu->status == 1) {
        if (sfClock_getElapsedTime(clock).microseconds > 1000000)
            clock = display_menu(menu, window, clock);
        handle_menu_events(window, menu);
    }
    free_all(menu, clock);
    return menu->status;
}
