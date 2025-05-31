/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** hud
*/

#include "hud.h"
#include "config.h"
#include "flashlight.h"
#include <unistd.h>
#include <stdio.h>

sfFont *init_hud(void)
{
    sfFont *hud_font = sfFont_createFromFile("assets/fonts/videotype.ttf");

    if (!hud_font) {
        write(2, "Error: Could not load font\n", 27);
        return NULL;
    }
    return hud_font;
}

void cleanup_hud(sfFont *hud_font)
{
    if (hud_font) {
        sfFont_destroy(hud_font);
    }
}

void draw_crosshair(sfRenderWindow *window)
{
    sfRectangleShape *crosshairh = sfRectangleShape_create();
    sfRectangleShape *crosshairv = sfRectangleShape_create();
    sfVector2f sizeh = {20, 2};
    sfVector2f sizev = {2, 20};

    sfRectangleShape_setSize(crosshairh, sizeh);
    sfRectangleShape_setSize(crosshairv, sizev);
    sfRectangleShape_setPosition(crosshairh, (sfVector2f)
        {window_config.width / 2 - 10, window_config.height / 2 - 1});
    sfRectangleShape_setPosition(crosshairv, (sfVector2f)
        {window_config.width / 2 - 1, window_config.height / 2 - 10});
    sfRectangleShape_setFillColor(crosshairh, sfRed);
    sfRectangleShape_setFillColor(crosshairv, sfRed);
    sfRenderWindow_drawRectangleShape(window, crosshairh, NULL);
    sfRenderWindow_drawRectangleShape(window, crosshairv, NULL);
    sfRectangleShape_destroy(crosshairh);
    sfRectangleShape_destroy(crosshairv);
}

static void draw_n_destrow_text(sfRenderWindow *window, sfText *text1,
    sfText *text2, sfText *flashlight_text)
{
    sfRenderWindow_drawText(window, text1, NULL);
    sfRenderWindow_drawText(window, text2, NULL);
    if (flashlight_text != NULL)
        sfRenderWindow_drawText(window, flashlight_text, NULL);
    sfText_destroy(text1);
    sfText_destroy(text2);
    if (flashlight_text != NULL)
        sfText_destroy(flashlight_text);
}

static sfText* create_hud_text(hud_text_params_t params)
{
    sfText *text = sfText_create();

    if (!text)
        return NULL;
    sfText_setFont(text, params.font);
    sfText_setString(text, params.string);
    sfText_setCharacterSize(text, params.size);
    sfText_setPosition(text, params.position);
    sfText_setFillColor(text, params.color);
    return text;
}

static sfText* create_health_text(sfFont *font)
{
    hud_text_params_t params = {
        .font = font,
        .string = "HEALTH: 100%",
        .position = {25, window_config.height - 38},
        .color = (sfColor){220, 50, 50, 255},
        .size = 18
    };

    return create_hud_text(params);
}

static sfText* create_ammo_text(sfFont *font)
{
    hud_text_params_t params = {
        .font = font,
        .string = "AMMO: 30",
        .position = {window_config.width - 130, window_config.height - 38},
        .color = (sfColor){240, 220, 50, 255},
        .size = 18
    };

    return create_hud_text(params);
}

static sfText* create_flashlight_text(sfFont *font)
{
    char flashlight_status[20];
    sfColor color = flashlight.enabled ?
        (sfColor){80, 220, 80, 255} : (sfColor){220, 220, 220, 255};
    hud_text_params_t params;

    sprintf(flashlight_status, "FLASHLIGHT: %s",
        flashlight.enabled ? "ON" : "OFF");
    params.font = font;
    params.string = flashlight_status;
    params.position = (sfVector2f)
        {window_config.width / 2 - 85, window_config.height - 38};
    params.color = color;
    params.size = 18;
    return create_hud_text(params);
}

void draw_stats(sfRenderWindow *window, sfFont *hud_font)
{
    sfText *health_text = NULL;
    sfText *ammo_text = NULL;
    sfText *flashlight_text = NULL;

    if (!hud_font)
        return;
    health_text = create_health_text(hud_font);
    ammo_text = create_ammo_text(hud_font);
    flashlight_text = create_flashlight_text(hud_font);
    draw_n_destrow_text(window, health_text, ammo_text, flashlight_text);
}
