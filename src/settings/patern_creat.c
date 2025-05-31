/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** patern_creat.c
*/

#include "settings.h"
#include "define.h"

sfRectangleShape *create_rectangle(sfVector2f size,
    sfVector2f position, sfColor color)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setPosition(rect, position);
    sfRectangleShape_setFillColor(rect, color);
    return rect;
}

sfText *create_text(const char *string, sfFont *font,
    unsigned int size, sfVector2f position)
{
    sfText *text = sfText_create();

    sfText_setString(text, string);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    sfText_setPosition(text, position);
    return text;
}

keybinding_t *creat_key(SettingsScene_t *settings, sfVector2f position,
    char *action, char *key)
{
    keybinding_t *key_create = malloc(sizeof(keybinding_t));

    key_create->action = malloc(sizeof(button_t));
    key_create->key = malloc(sizeof(button_t));
    key_create->action->Text = create_text(action, FONT, 20,
        (sfVector2f){position.x + 10, position.y + 12});
    key_create->key->Text = create_text(key, FONT, 20,
        (sfVector2f){position.x + 180, position.y + 12});
    key_create->action->slider = create_rectangle(
        (sfVector2f){300, 50}, position, sfColor_fromRGB(50, 50, 50));
    key_create->key->slider = create_rectangle(
        (sfVector2f){180, 50}, (sfVector2f){position.x + 120, position.y},
        sfColor_fromRGB(150, 150, 150));
    key_create->is_binding = false;
    return key_create;
}
