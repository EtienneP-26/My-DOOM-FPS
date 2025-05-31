/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** flashlight
*/

#ifndef FLASHLIGHT_H
    #define FLASHLIGHT_H

    #include <stdbool.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

typedef struct flashlight_s {
    bool enabled;
    float cone_angle;
    float max_distance;
    float intensity;
    float ambient_light;
    sfSound *toggle_sound;
    sfSoundBuffer *toggle_buffer;
} flashlight_t;

extern flashlight_t flashlight;

void init_flashlight(void);
void cleanup_flashlight(void);
void toggle_flashlight(void);
float get_light_intensity(float distance, float angle_diff);
sfColor apply_lighting(sfColor color, float intensity);

#endif /* FLASHLIGHT_H */
