/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** sound_effects
*/

#include "sound_manager.h"
#include <stdio.h>

void play_shot_sound(void)
{
    if (!sound_manager.sound_enabled ||
        !can_play_sound(&sound_manager.shot_sound)) {
        return;
    }
    sfSound_play(sound_manager.shot_sound.sound);
    sfClock_restart(sound_manager.shot_sound.cooldown_clock);
    sound_manager.shot_sound.is_playing = true;
}

void play_footstep_sound(void)
{
    if (!sound_manager.sound_enabled ||
        !can_play_sound(&sound_manager.footstep_sound)) {
        return;
    }
    sfSound_play(sound_manager.footstep_sound.sound);
    sfClock_restart(sound_manager.footstep_sound.cooldown_clock);
    sound_manager.footstep_sound.is_playing = true;
}

void set_master_volume(float volume)
{
    sound_manager.master_volume = volume;
    if (sound_manager.shot_sound.sound) {
        sfSound_setVolume(sound_manager.shot_sound.sound,
            sound_manager.shot_sound.volume * (volume / 100.0f));
    }
    if (sound_manager.footstep_sound.sound) {
        sfSound_setVolume(sound_manager.footstep_sound.sound,
            sound_manager.footstep_sound.volume * (volume / 100.0f));
    }
}
