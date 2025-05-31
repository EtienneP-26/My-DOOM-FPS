/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** sound_manager
*/

#include "sound_manager.h"
#include "settings.h"
#include <stdio.h>

sound_manager_t sound_manager;

static void init_sound(sound_effect_t *sound_effect, const char *file_path,
    float volume, float cooldown)
{
    sound_effect->buffer = sfSoundBuffer_createFromFile(file_path);
    if (!sound_effect->buffer) {
        fprintf(stderr, "Failed to load sound: %s\n", file_path);
        return;
    }
    sound_effect->sound = sfSound_create();
    if (!sound_effect->sound) {
        fprintf(stderr, "Failed to create sound\n");
        sfSoundBuffer_destroy(sound_effect->buffer);
        sound_effect->buffer = NULL;
        return;
    }
    sfSound_setBuffer(sound_effect->sound, sound_effect->buffer);
    sound_effect->volume = volume;
    sound_effect->is_playing = false;
    sound_effect->cooldown = cooldown;
    sound_effect->cooldown_clock = sfClock_create();
    sfSound_setVolume(sound_effect->sound, volume);
}

void init_sound_manager(void)
{
    sound_manager.sound_enabled = true;
    sound_manager.master_volume = 100.0f;
    init_sound(&sound_manager.shot_sound, "assets/sound/shot_uzi.mp3",
        20.0f, 0.1f);
    init_sound(&sound_manager.footstep_sound, "assets/sound/footstep.mp3",
        90.0f, 0.4f);
}

static void cleanup_sound(sound_effect_t *sound_effect)
{
    if (sound_effect->sound) {
        sfSound_destroy(sound_effect->sound);
    }
    if (sound_effect->buffer) {
        sfSoundBuffer_destroy(sound_effect->buffer);
    }
    if (sound_effect->cooldown_clock) {
        sfClock_destroy(sound_effect->cooldown_clock);
    }
}

void cleanup_sound_manager(void)
{
    cleanup_sound(&sound_manager.shot_sound);
    cleanup_sound(&sound_manager.footstep_sound);
}

bool can_play_sound(sound_effect_t *sound_effect)
{
    sfTime elapsed;
    float seconds;

    if (!sound_effect->sound || !sound_effect->buffer) {
        return false;
    }
    elapsed = sfClock_getElapsedTime(sound_effect->cooldown_clock);
    seconds = sfTime_asSeconds(elapsed);
    return seconds >= sound_effect->cooldown;
}

void update_sounds(float base_volume)
{
    float volume_multiplier = get_volume_value() / 5.0f;

    if (sound_manager.shot_sound.sound) {
        base_volume = sound_manager.shot_sound.volume;
        sfSound_setVolume(sound_manager.shot_sound.sound,
            base_volume * volume_multiplier);
    }
    if (sound_manager.footstep_sound.sound) {
        base_volume = sound_manager.footstep_sound.volume;
        sfSound_setVolume(sound_manager.footstep_sound.sound,
            base_volume * volume_multiplier);
    }
    if (sound_manager.shot_sound.is_playing &&
        sfSound_getStatus(sound_manager.shot_sound.sound) == sfStopped) {
        sound_manager.shot_sound.is_playing = false;
    }
    if (sound_manager.footstep_sound.is_playing &&
        sfSound_getStatus(sound_manager.footstep_sound.sound) == sfStopped) {
        sound_manager.footstep_sound.is_playing = false;
    }
}

void toggle_sound(void)
{
    sound_manager.sound_enabled = !sound_manager.sound_enabled;
}
