/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** weapon
*/

#ifndef WEAPON_H
    #define WEAPON_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>

typedef struct weapon_animation_s {
    int current_frame;
    int total_frames;
    sfClock *animation_clock;
    sfClock *cooldown_clock;
    float frame_time;
    float cooldown_time;
    bool is_animating;
} weapon_animation_t;

typedef struct weapon_s {
    sfSprite *sprite;
    sfTexture *texture;
    float bob_offset;
    bool is_firing;
    weapon_animation_t animation;
    sfIntRect frame_rect;
} weapon_t;

extern weapon_t weapon;

void init_weapon(void);
void cleanup_weapon(void);
void update_weapon(void);
void draw_weapon(sfRenderWindow *window);
void update_weapon_animation(void);

#endif /* WEAPON_H */
