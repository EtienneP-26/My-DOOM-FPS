/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** flashlight
*/

#include "flashlight.h"
#include "config.h"
#include <math.h>

flashlight_t flashlight;

void init_flashlight(void)
{
    flashlight.enabled = false;
    flashlight.cone_angle = 45.0f;
    flashlight.max_distance = render_config.max_distance * 1.5f;
    flashlight.intensity = 1.0f;
    flashlight.ambient_light = 0.3f;
    flashlight.toggle_sound = NULL;
    flashlight.toggle_buffer = NULL;
}

void cleanup_flashlight(void)
{
    if (flashlight.toggle_sound)
        sfSound_destroy(flashlight.toggle_sound);
    if (flashlight.toggle_buffer)
        sfSoundBuffer_destroy(flashlight.toggle_buffer);
}

void toggle_flashlight(void)
{
    flashlight.enabled = !flashlight.enabled;
}

static float get_ambient_lighting(float distance)
{
    float base_intensity = 0.55f;
    float max_distance = render_config.max_distance;
    float distance_factor = 1.0f - fminf(distance / max_distance, 1.0f) * 0.7f;

    return fmaxf(base_intensity * distance_factor, 0.3f);
}

float get_light_intensity(float distance, float angle_diff)
{
    float base_intensity;
    float distance_factor;
    float angle_factor = 1.0f;
    float max_distance;

    if (!flashlight.enabled) {
        return get_ambient_lighting(distance);
    }
    max_distance = flashlight.max_distance;
    base_intensity = flashlight.intensity;
    distance_factor = 1.0f - fminf(distance / max_distance, 1.0f) * 0.8f;
    if (fabs(angle_diff) > 0) {
        angle_factor = 1.0f - fminf(fabs(angle_diff) /
            (flashlight.cone_angle / 2.0f), 1.0f);
        angle_factor = angle_factor * angle_factor * 0.7f + 0.3f;
    }
    return fmaxf(base_intensity * fmaxf(distance_factor * angle_factor, 0.4f),
        flashlight.ambient_light * 0.8f);
}

sfColor apply_lighting(sfColor color, float intensity)
{
    sfColor result;
    int min_brightness = 40;

    intensity = fmaxf(0.0f, fminf(1.0f, intensity * 1.2f));
    result.r = (sfUint8)(color.r * intensity);
    result.g = (sfUint8)(color.g * intensity);
    result.b = (sfUint8)(color.b * intensity);
    result.a = color.a;
    result.r = fmaxf(result.r, min_brightness);
    result.g = fmaxf(result.g, min_brightness);
    result.b = fmaxf(result.b, min_brightness);
    return result;
}
