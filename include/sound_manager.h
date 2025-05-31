/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** sound_manager
*/

#ifndef SOUND_MANAGER_H
    #define SOUND_MANAGER_H

    #include <SFML/Audio.h>
    #include <stdbool.h>

typedef struct sound_effect_s {
    sfSound *sound;
    sfSoundBuffer *buffer;
    float volume;
    bool is_playing;
    float cooldown;
    sfClock *cooldown_clock;
} sound_effect_t;

typedef struct sound_manager_s {
    sound_effect_t shot_sound;
    sound_effect_t footstep_sound;
    bool sound_enabled;
    float master_volume;
} sound_manager_t;

extern sound_manager_t sound_manager;

// Sound manager core functions
void init_sound_manager(void);
void cleanup_sound_manager(void);
void update_sounds(float base_volume);
void toggle_sound(void);
bool can_play_sound(sound_effect_t *sound_effect);

// Sound effects functions (in sound_effects.c)
void play_shot_sound(void);
void play_footstep_sound(void);
void set_master_volume(float volume);

#endif /* SOUND_MANAGER_H */
