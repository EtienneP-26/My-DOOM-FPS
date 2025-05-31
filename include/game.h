/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** game
*/

#ifndef GAME_H
    #define GAME_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>

typedef struct game_s {
    sfRenderWindow *window;
    bool is_running;
} game_t;

extern game_t game;

void init_game(sfRenderWindow *window);
int game_loop(void);
void cleanup_game(void);
int handle_events(void);

#endif /* GAME_H */
