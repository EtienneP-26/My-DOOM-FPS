/*
** EPITECH PROJECT, 2025
** My-DOOM
** File description:
** menu
*/

#include "menu_sett.h"
#include <string.h>

menu_t *put_logo(menu_t *menu, sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f logo_pos = {
        (window_size.x - 200) / 2 - 150,
        (window_size.y - 200) / 2 - 300};

    menu->logo_texture = sfTexture_createFromFile(
        "assets/images/menu/logo.png", NULL);
    if (!menu->logo_texture){
        free_all(menu, NULL);
        return NULL;
    }
    menu->logo_sprite = sfSprite_create();
    sfSprite_setTexture(menu->logo_sprite, menu->logo_texture, sfTrue);
    sfSprite_setPosition(menu->logo_sprite, logo_pos);
    return menu;
}

menu_t *put_background(menu_t *menu, sfRenderWindow *window)
{
    menu->background_texture = sfTexture_createFromFile(
        "assets/images/menu/background_menu.png", NULL);
    if (!menu->background_texture){
        free_all(menu, NULL);
        return NULL;
    }
    menu->background_sprite = sfSprite_create();
    sfSprite_setTexture(menu->background_sprite, menu->background_texture,
        sfTrue);
    menu->status = 0;
    menu->button3_texture = sfTexture_createFromFile(
        "assets/images/menu/exit.png", NULL);
    if (!menu->button1_texture)
        return NULL;
    menu->button3_sprite = sfSprite_create();
    sfSprite_setTexture(menu->button3_sprite, menu->button3_texture, sfTrue);
    return put_logo(menu, window);
}

static menu_t *innit_menu(sfRenderWindow *window)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    memset(menu, 0, sizeof(menu_t));
    menu->button1_texture = sfTexture_createFromFile(
        "assets/images/menu/play.png", NULL);
    if (!menu->button1_texture)
        return NULL;
    menu->button1_sprite = sfSprite_create();
    sfSprite_setTexture(menu->button1_sprite, menu->button1_texture, sfTrue);
    menu->button2_texture = sfTexture_createFromFile(
        "assets/images/menu/setting.png", NULL);
    if (!menu->button2_texture)
        return NULL;
    menu->button2_sprite = sfSprite_create();
    sfSprite_setTexture(menu->button2_sprite, menu->button2_texture, sfTrue);
    menu = put_background(menu, window);
    return menu;
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
    sfSprite_setScale(menu->background_sprite, (sfVector2f){2.0f, 2.0f});
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
        return 1;
    if (sfFloatRect_contains(&setting_bounds, x, y))
        return 2;
    if (sfFloatRect_contains(&exit_bounds, x, y))
        return 5;
    return 0;
}

static void handle_menu_events(sfRenderWindow *window, menu_t *menu)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)){
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft)
        menu->status = next_scene(menu, event.mouseButton.x,
            event.mouseButton.y);
}

void continue_free(menu_t *menu, sfClock *clock)
{
    if (menu->button3_sprite)
        sfSprite_destroy(menu->button3_sprite);
    if (menu->button3_texture)
        sfTexture_destroy(menu->button3_texture);
    if (menu->logo_sprite)
        sfSprite_destroy(menu->logo_sprite);
    if (menu->logo_texture)
        sfTexture_destroy(menu->logo_texture);
    free(menu);
    if (clock)
        sfClock_destroy(clock);
}

void free_all(menu_t *menu, sfClock *clock)
{
    if (menu->button1_sprite)
        sfSprite_destroy(menu->button1_sprite);
    if (menu->button1_texture)
        sfTexture_destroy(menu->button1_texture);
    if (menu->button2_sprite)
        sfSprite_destroy(menu->button2_sprite);
    if (menu->button2_texture)
        sfTexture_destroy(menu->button2_texture);
    if (menu->background_sprite)
        sfSprite_destroy(menu->background_sprite);
    if (menu->background_texture)
        sfTexture_destroy(menu->background_texture);
    continue_free(menu, clock);
}

int main_menu(sfRenderWindow *window)
{
    menu_t *menu = innit_menu(window);
    sfClock *clock = sfClock_create();

    if (!menu){
        free_all(menu, clock);
        return 84;
    }
    place_sprite(menu, window);
    display_menu(menu, window, clock);
    while (sfRenderWindow_isOpen(window) && menu->status == 0) {
        if (sfClock_getElapsedTime(clock).microseconds > 1000000)
            clock = display_menu(menu, window, clock);
        handle_menu_events(window, menu);
    }
    free_all(menu, clock);
    return menu->status;
}
