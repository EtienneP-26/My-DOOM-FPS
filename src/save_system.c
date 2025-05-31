/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** save_system
*/

#include "save_system.h"
#include "player.h"
#include "flashlight.h"
#include "sound_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

static void ensure_save_directory(void)
{
    if (access(SAVE_DIR, F_OK) != 0) {
        mkdir(SAVE_DIR, 0700);
    }
}

static void generate_timestamp(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

static void collect_save_data(save_data_t *data, const char *save_name)
{
    data->player_x = player.x;
    data->player_y = player.y;
    data->player_angle = player.angle;
    data->player_health = 100;
    data->player_ammo = 30;
    data->flashlight_enabled = flashlight.enabled;
    data->master_volume = sound_manager.master_volume;
    strncpy(data->save_name, save_name, sizeof(data->save_name) - 1);
    data->save_name[sizeof(data->save_name) - 1] = '\0';
    generate_timestamp(data->timestamp, sizeof(data->timestamp));
}

static void apply_save_data(save_data_t *data)
{
    player.x = data->player_x;
    player.y = data->player_y;
    player.angle = data->player_angle;
    flashlight.enabled = data->flashlight_enabled;
    set_master_volume(data->master_volume);
}

bool save_game(const char *filename)
{
    FILE *file;
    save_data_t save_data;
    bool success = false;

    ensure_save_directory();
    collect_save_data(&save_data, filename);
    file = fopen(filename, "wb");
    if (file) {
        if (fwrite(&save_data, sizeof(save_data_t), 1, file) == 1) {
            success = true;
        }
        fclose(file);
    }
    return success;
}

bool load_game(const char *filename)
{
    FILE *file;
    save_data_t save_data;
    bool success = false;

    file = fopen(filename, "rb");
    if (file) {
        if (fread(&save_data, sizeof(save_data_t), 1, file) == 1) {
            apply_save_data(&save_data);
            success = true;
        }
        fclose(file);
    }
    return success;
}

bool quick_save(void)
{
    return save_game(QUICK_SAVE_FILE);
}

bool quick_load(void)
{
    return load_game(QUICK_SAVE_FILE);
}

void get_save_info(const char *filename, save_data_t *info)
{
    FILE *file = fopen(filename, "rb");

    if (file) {
        fread(info, sizeof(save_data_t), 1, file);
        fclose(file);
    } else {
        memset(info, 0, sizeof(save_data_t));
        strncpy(info->save_name, "Invalid Save", sizeof(info->save_name) - 1);
        strncpy(info->timestamp, "Unknown", sizeof(info->timestamp) - 1);
    }
}
