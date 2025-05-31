/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** menu
*/

#ifndef MENU_H
    #define MENU_H

    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <stdbool.h>
    #include <stdlib.h>

typedef struct menu_s {
    sfSprite *button1_sprite;
    sfTexture *button1_texture;
    sfSprite *button2_sprite;
    sfTexture *button2_texture;
    sfSprite *button3_sprite;
    sfTexture *button3_texture;
    sfSprite *logo_sprite;
    sfTexture *logo_texture;
    sfSprite *background_sprite;
    sfTexture *background_texture;
    int status;
} menu_t;

int main_menu(sfRenderWindow *window);
int play_menu(sfRenderWindow *window);
menu_t *put_background(menu_t *menu, sfRenderWindow *window);
sfClock *display_menu(menu_t *menu, sfRenderWindow *window,
    sfClock *clock);
void free_all(menu_t *menu, sfClock *clock);
menu_t *put_logo(menu_t *menu, sfRenderWindow *window);
#endif
