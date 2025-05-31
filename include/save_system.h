/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** save_system
*/

#ifndef SAVE_SYSTEM_H
    #define SAVE_SYSTEM_H

    #include <stdbool.h>

    #define QUICK_SAVE_FILE "saves/quicksave.sav"
    #define SAVE_DIR "saves"

typedef struct save_data_s {
    float player_x;
    float player_y;
    float player_angle;
    int player_health;
    int player_ammo;
    bool flashlight_enabled;
    float master_volume;
    char save_name[64];
    char timestamp[64];
} save_data_t;

bool save_game(const char *filename);
bool load_game(const char *filename);
bool quick_save(void);
bool quick_load(void);
void get_save_info(const char *filename, save_data_t *info);

#endif /* SAVE_SYSTEM_H */
