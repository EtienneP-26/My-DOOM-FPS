/*
** EPITECH PROJECT, 2024
** My-DOOM FPS
** File description:
** settings.h
*/


#ifndef SETTINGS_H
    #define SETTINGS_H
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>


typedef struct {
    sfRectangleShape *slider;
    sfText *Text;
} button_t;

typedef struct {
    button_t *action;
    button_t *key;
    bool is_binding;
} keybinding_t;

typedef struct {
    sfRectangleShape *slider;
    sfText *Nbr;
    sfText *Text;
    button_t *plus;
    button_t *minus;
    int value;
} sensivol_t;

typedef struct {
    sfRectangleShape *SizescreenShape;
    sfText *SizescreenText;
    button_t *fullscreen;
    button_t *windowed;
} sizescreen_t;

typedef struct {
    sfTexture *Background;
    sfSprite *BackgroundSprite;
} background_t;

typedef struct {
    sfRectangleShape *slider;
    sfText *Text;
    bool is_binding;
} scenebinding_t;

typedef struct {
    sfRenderWindow *window;
    sfFont *font;
    background_t *background;
    sizescreen_t *sizescreen;
    button_t *back;
    button_t *title;
    sensivol_t *sensi;
    sensivol_t *volume;
    keybinding_t *shoot;
    keybinding_t *Forward;
    keybinding_t *Backward;
    keybinding_t *Left;
    keybinding_t *Right;
    scenebinding_t *scenebinding;
    sfView *fullscreen_view;
    bool goBack;
} SettingsScene_t;

// Global settings instance
extern SettingsScene_t *global_settings;

// Helper functions to access settings values
int get_sensitivity_value(void);
int get_volume_value(void);
int get_key_binding(const char *action);
void init_global_settings(sfRenderWindow *window);
void cleanup_global_settings(void);

void resize_elements(SettingsScene_t *settings, float ScF);
void init_settings_scene(SettingsScene_t *settings, sfRenderWindow *window);
keybinding_t *creat_key(SettingsScene_t *settings, sfVector2f position,
    char *action, char *key);
sfText *create_text(const char *string, sfFont *font,
    unsigned int size, sfVector2f position);
sfRectangleShape *create_rectangle(sfVector2f size,
    sfVector2f position, sfColor color);
void draw_settings_scene(SettingsScene_t *settings);
void destroy_settings_scene(SettingsScene_t *settings);
int handle_settings_events(SettingsScene_t *settings, sfEvent *event);
void malloc_settings_scene(SettingsScene_t *settings);
void handle_binding_events(SettingsScene_t *settings, keybinding_t *keybind,
    sfEvent event);
void free_settings_scene(SettingsScene_t *settings);
int start_setting(sfRenderWindow *windows);

#endif /* SETTINGS_H */
