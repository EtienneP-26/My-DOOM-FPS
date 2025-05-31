/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** config
*/

#ifndef CONFIG_H
    #define CONFIG_H

    #include <SFML/Graphics.h>
    #include <math.h>
    #include <stdbool.h>

typedef struct window_config_s {
    int width;
    int height;
    int bits_per_pixel;
} window_config_t;

typedef struct world_config_s {
    int width;
    int height;
    int scale_factor;
    int rate_map;
} world_config_t;

typedef struct map_config_s {
    int grid_width;
    int grid_height;
} map_config_t;

typedef struct player_config_s {
    float move_speed;
    float rotate_speed;
    float radius;
    float jump_force;
    float gravity;
} player_config_t;

typedef struct render_config_s {
    float fov;
    int precision;
    int max_distance;
    int fps;
} render_config_t;

extern window_config_t window_config;
extern world_config_t world_config;
extern map_config_t map_config;
extern player_config_t player_config;
extern render_config_t render_config;

void init_configurations(void);

extern const sfContextSettings sfml_settings;

#endif /* CONFIG_H */
