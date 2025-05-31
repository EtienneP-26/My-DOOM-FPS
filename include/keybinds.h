/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** keybinds
*/

#ifndef KEYBINDS_H
    #define KEYBINDS_H

    #include <SFML/Window/Keyboard.h>

typedef struct controls_s {
    sfKeyCode up;
    sfKeyCode down;
    sfKeyCode left;
    sfKeyCode right;
    sfKeyCode shoot;
    sfKeyCode run;
    sfKeyCode pause;
    float sensi;
} controls_t;

extern const char *keybinds_list[];
extern const sfKeyCode keybinds_values[];

int finds_keycode(const char *keybind);
int find_keybind(sfKeyCode keycode);

#endif /* KEYBINDS_H */
