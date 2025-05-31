/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** raycaster
*/

#ifndef RAYCASTER_H
    #define RAYCASTER_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>

typedef struct raycast_result_s {
    float angle;
    float distance;
    float wall_height;
    bool hit_wall;
    int wall_type;
    float tex_x;
    float hit_x;
    float hit_y;
} raycast_result_t;

typedef struct ray_context_s {
    float cell_size_x;
    float cell_size_y;
} ray_context_t;

extern sfTexture *wall_texture;

raycast_result_t cast_ray(float ray_angle, float step);
void draw_ray(sfRenderWindow *window,
    float ray_angle, raycast_result_t result);
void render_wall_slice(sfRenderWindow *window,
    int ray_index, raycast_result_t result);
void render_view(sfRenderWindow *window);
float handle_texture_mapping(float hit_position_x, float hit_position_y);
float handle_edge_cases(float hit_position_x, float hit_position_y,
    float epsilon);

// ray_calculation.c
void initialize_ray(float *ray_x, float *ray_y, ray_context_t *context);
int step_ray(float *ray_x, float *ray_y, float ray_angle, float step);
void set_wall_height(raycast_result_t *result, float ray_angle);
float get_ray_max_distance(float ray_angle);

// texture_mapping.c
float calculate_texture_x(float hit_x, float hit_y,
    float cell_size_x, float cell_size_y);
void process_wall_hit(raycast_result_t *result,
    float ray_x, float ray_y, ray_context_t context);

// rendering_ray.c
void render_wall_color(sfRectangleShape *wall,
    raycast_result_t result, float light_intensity);
void setup_wall_texture(sfRectangleShape *wall,
    raycast_result_t result, float light_intensity);
void setup_wall_dimensions(sfRectangleShape *wall,
    int ray_index, raycast_result_t result);
float calculate_light_intensity(int ray_index, raycast_result_t result);

#endif /* RAYCASTER_H */
