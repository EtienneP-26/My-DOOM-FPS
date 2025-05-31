/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** enemy
*/

#ifndef ENEMY_H
    #define ENEMY_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>

    #define MAX_ENEMIES 20

typedef struct enemy_s {
    float x;
    float y;
    bool alive;
    sfTexture *texture;
    sfSprite *sprite;
} enemy_t;

typedef struct enemy_manager_s {
    enemy_t enemies[MAX_ENEMIES];
    int count;
    sfTexture *enemy_texture;
} enemy_manager_t;

extern enemy_manager_t enemy_manager;

void init_enemies(void);
void cleanup_enemies(void);
void render_enemies(sfRenderWindow *window);
bool shoot_enemy(float angle);
void spawn_enemy(float x, float y);
void draw_enemy_on_minimap(sfRenderWindow *window, enemy_t *enemy);
void render_enemy_sprite(sfRenderWindow *window, enemy_t *enemy);

#endif /* ENEMY_H */
