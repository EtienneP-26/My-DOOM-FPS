/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** resize.c
*/

#include "settings.h"
#include "define.h"

static void resize_volume(SettingsScene_t *settings, float ScF)
{
    sfRectangleShape_setSize(VOLUMEB, (sfVector2f){300 * ScF, 40 * ScF});
    sfRectangleShape_setPosition(VOLUMEB, (sfVector2f){200 * ScF, 150 * ScF});
    sfText_setCharacterSize(VOLUMET, 20 * ScF);
    sfText_setPosition(VOLUMET, (sfVector2f){220 * ScF, 158 * ScF});
    sfRectangleShape_setSize(MINUSVB, (sfVector2f){30 * ScF, 30 * ScF});
    sfRectangleShape_setPosition(MINUSVB, (sfVector2f){385 * ScF, 155 * ScF});
    sfRectangleShape_setSize(PLUSVB, (sfVector2f){30 * ScF, 30 * ScF});
    sfRectangleShape_setPosition(PLUSVB, (sfVector2f){465 * ScF, 155 * ScF});
    sfText_setCharacterSize(VOLUMEN, 20 * ScF);
    sfText_setPosition(VOLUMEN, (sfVector2f){435 * ScF, 158 * ScF});
    sfText_setCharacterSize(PLUSVT, 20 * ScF);
    sfText_setPosition(PLUSVT, (sfVector2f){475 * ScF, 158 * ScF});
    sfText_setCharacterSize(MINUSVT, 20 * ScF);
    sfText_setPosition(MINUSVT, (sfVector2f){395 * ScF, 158 * ScF});
}

static void resize_sensi(SettingsScene_t *settings, float ScF)
{
    sfRectangleShape_setSize(SENSIB, (sfVector2f){300 * ScF, 40 * ScF});
    sfRectangleShape_setPosition(SENSIB, (sfVector2f){510 * ScF, 150 * ScF});
    sfText_setCharacterSize(SENSIT, 20 * ScF);
    sfText_setPosition(SENSIT, (sfVector2f){530 * ScF, 158 * ScF});
    sfRectangleShape_setSize(MINUSSB, (sfVector2f){30 * ScF, 30 * ScF});
    sfRectangleShape_setPosition(MINUSSB, (sfVector2f){695 * ScF, 155 * ScF});
    sfRectangleShape_setSize(PLUSSB, (sfVector2f){30 * ScF, 30 * ScF});
    sfRectangleShape_setPosition(PLUSSB, (sfVector2f){775 * ScF, 155 * ScF});
    sfText_setCharacterSize(SENSIN, 20 * ScF);
    sfText_setPosition(SENSIN, (sfVector2f){745 * ScF, 158 * ScF});
    sfText_setCharacterSize(PLUSST, 20 * ScF);
    sfText_setPosition(PLUSST, (sfVector2f){785 * ScF, 158 * ScF});
    sfText_setCharacterSize(MINUSST, 20 * ScF);
    sfText_setPosition(MINUSST, (sfVector2f){705 * ScF, 158 * ScF});
}

static void resize_screen_case(SettingsScene_t *settings, float ScF)
{
    sfRectangleShape_setSize(SCREENB, (sfVector2f){600 * ScF, 40 * ScF});
    sfRectangleShape_setPosition(SCREENB, (sfVector2f){820 * ScF, 150 * ScF});
    sfRectangleShape_setSize(SWINDOWB, (sfVector2f){200 * ScF, 40 * ScF});
    sfRectangleShape_setPosition(SWINDOWB,
        (sfVector2f){1020 * ScF, 150 * ScF});
    sfText_setCharacterSize(SWINDOWT, 20 * ScF);
    sfText_setPosition(SWINDOWT, (sfVector2f){1065 * ScF, 160 * ScF});
    sfRectangleShape_setSize(FULLSCREENB,
        (sfVector2f){200 * ScF, 40 * ScF});
    sfRectangleShape_setPosition(FULLSCREENB,
        (sfVector2f){1220 * ScF, 150 * ScF});
    sfText_setCharacterSize(FULLSCREENT, 20 * ScF);
    sfText_setPosition(FULLSCREENT, (sfVector2f){1265 * ScF, 160 * ScF});
    sfText_setCharacterSize(SCREENT, 20 * ScF);
    sfText_setPosition(SCREENT, (sfVector2f){835 * ScF, 158 * ScF});
}

static void resize_keybinding(keybinding_t *keybinding,
    float ScF, sfVector2f pos)
{
    sfRectangleShape_setSize(KEYKS, (sfVector2f){180 * ScF, 50 * ScF});
    sfRectangleShape_setPosition(KEYKS,
        (sfVector2f){(pos.x + 120) * ScF, pos.y * ScF});
    sfRectangleShape_setSize(KEYAS, (sfVector2f){300 * ScF, 50 * ScF});
    sfRectangleShape_setPosition(KEYAS,
        (sfVector2f){pos.x * ScF, pos.y * ScF});
    sfText_setCharacterSize(KEYAT, 20 * ScF);
    sfText_setPosition(KEYAT,
        (sfVector2f){(pos.x + 10) * ScF, (pos.y + 12) * ScF});
    sfText_setCharacterSize(KEYKT, 20 * ScF);
    sfText_setPosition(KEYKT,
        (sfVector2f){(pos.x + 180) * ScF, (pos.y + 12) * ScF});
}

static void resize_keybindings(SettingsScene_t *settings, float ScF)
{
    resize_keybinding(SHOOT, ScF, (sfVector2f){200, 200});
    resize_keybinding(FORWARD, ScF, (sfVector2f){200, 300});
    resize_keybinding(BACKWARD, ScF, (sfVector2f){200, 400});
    resize_keybinding(LEFT, ScF, (sfVector2f){200, 500});
    resize_keybinding(RIGHT, ScF, (sfVector2f){200, 600});
}

static void resize_binding(scenebinding_t *bind, float ScF)
{
    sfRectangleShape_setSize(bind->slider, (sfVector2f){270 * ScF, 50 * ScF});
    sfRectangleShape_setPosition(bind->slider,
        (sfVector2f){600 * ScF, 300 * ScF});
    sfText_setCharacterSize(bind->Text, 20 * ScF);
    sfText_setPosition(bind->Text,
        (sfVector2f){625 * ScF, 312 * ScF});
}

void resize_elements(SettingsScene_t *settings, float ScF)
{
    sfSprite_setScale(BACKGROUNDSPRITE, (sfVector2f){2.1f * ScF, 1.75f * ScF});
    sfSprite_setPosition(BACKGROUNDSPRITE, (sfVector2f){0, 0});
    sfText_setCharacterSize(TITLET, 50 * ScF);
    sfText_setPosition(TITLET, (sfVector2f){700 * ScF, 20 * ScF});
    resize_volume(settings, ScF);
    resize_sensi(settings, ScF);
    resize_screen_case(settings, ScF);
    resize_keybindings(settings, ScF);
    resize_binding(settings->scenebinding, ScF);
    sfRectangleShape_setSize(BACKB, (sfVector2f){100 * ScF, 50 * ScF});
    sfRectangleShape_setPosition(BACKB, (sfVector2f){20 * ScF, 25 * ScF});
    sfText_setCharacterSize(BACKT, 25 * ScF);
    sfText_setPosition(BACKT, (sfVector2f){40 * ScF, 35 * ScF});
}
