/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** hud
*/

#ifndef HUD_H
    #define HUD_H

    #include <SFML/Graphics.h>

typedef struct hud_text_params_s {
    sfFont *font;
    const char *string;
    sfVector2f position;
    sfColor color;
    unsigned int size;
} hud_text_params_t;

sfFont *init_hud(void);
void cleanup_hud(sfFont *hud_font);
void draw_crosshair(sfRenderWindow *window);
void draw_stats(sfRenderWindow *window, sfFont *hud_font);
void draw_hud(sfRenderWindow *window, sfFont *hud_font);
void draw_hud_bar(sfRenderWindow *window);

#endif /* HUD_H */
