/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** main
*/

#include "game.h"
#include "menu_sett.h"
#include "settings.h"
#include "save_system.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_help(void)
{
    FILE *help_file = fopen("help_file.txt", "r");
    char buffer[1024];

    if (help_file == NULL) {
        write(2, "Error: Could not open help file\n", 32);
        write(2, "The help file is missing or corrupted.\n", 39);
        write(2, "Please contact the support team.\n", 33);
        write(2, "Exiting the program.\n", 21);
        return;
    }
    while (fgets(buffer, sizeof(buffer), help_file) != NULL) {
        printf("%s", buffer);
    }
    fclose(help_file);
}

int check_is_tty(char **env)
{
    bool has_display = false;

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], "DISPLAY=", 8) == 0 && strlen(env[i]) > 8) {
            has_display = true;
            break;
        }
    }
    if (!has_display) {
        write(2, "Error: No display environment detected.\n", 40);
        return 84;
    }
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)) {
        write(2, "Error: This program must be run in a terminal.\n", 47);
        write(2, "Please launch the game directly from a terminal window.\n",
            55);
        return 84;
    }
    return 0;
}

static sfRenderWindow *create_game_window(void)
{
    sfRenderWindow *window = sfRenderWindow_create(
        (sfVideoMode){1600, 900, 32}, "My-DOOM", sfResize | sfClose, NULL);

    if (!window) {
        write(2, "Error: Could not create window.\n", 33);
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(window, 30);
    init_global_settings(window);
    return window;
}

static int handle_menu_state(int status, sfRenderWindow *window)
{
    int (*menu_func[3])(sfRenderWindow *) = {
        main_menu,
        play_menu,
        start_setting
    };

    if (status >= 0 && status <= 2) {
        return menu_func[status](window);
    }
    return status;
}

static int handle_game_state(int status, sfRenderWindow *window)
{
    int result;

    if (status == 3) {
        init_game(window);
        quick_load();
        result = game_loop();
        cleanup_game();
        return result == 0 ? 0 : result;
    } else if (status == 4) {
        init_game(window);
        result = game_loop();
        cleanup_game();
        return result == 0 ? 0 : result;
    }
    return status;
}

static int process_game_state(sfRenderWindow *window, int status)
{
    switch (status) {
        case 0:
        case 1:
        case 2:
            status = handle_menu_state(status, window);
            break;
        case 3:
        case 4:
            status = handle_game_state(status, window);
            break;
        case 5:
            sfRenderWindow_close(window);
            break;
        default:
            break;
    }
    return status;
}

int choice_menu(void)
{
    sfRenderWindow *window = create_game_window();
    sfMusic *music =
        sfMusic_createFromFile("assets/sound/background_music.mp3");
    int status = 0;

    if (!window || !music) {
        return 84;
    }
    sfMusic_setLoop(music, sfTrue);
    sfMusic_setVolume(music, 2 * get_volume_value());
    sfMusic_play(music);
    while (sfRenderWindow_isOpen(window)) {
        sfMusic_setVolume(music, 2 * get_volume_value());
        status = process_game_state(window, status);
    }
    sfMusic_stop(music);
    sfMusic_destroy(music);
    sfRenderWindow_destroy(window);
    return status;
}

int main(int argc, char **argv, char **env)
{
    if (argc > 2) {
        write(2, "Too many arguments\n", 20);
        return 84;
    }
    if (argc == 2 && strcmp(argv[1], "-h") == 0){
        print_help();
        return 0;
    } else if (argc == 2 && strcmp(argv[1], "-h") != 0) {
        write(2, "Invalid argument\n", 17);
        return 84;
    }
    if (check_is_tty(env) == 84)
        return 84;
    if (choice_menu() == 84) {
        write(2, "Error: Failed to start the game.\n", 34);
        return 84;
    }
    return 0;
}
