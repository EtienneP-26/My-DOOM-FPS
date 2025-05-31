/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** weapon
*/

#include "weapon.h"
#include "config.h"
#include "sound_manager.h"
#include "particle.h"
#include "settings.h"
#include "enemy.h"
#include "player.h"

weapon_t weapon;

static void init_weapon_animation(void)
{
    weapon.animation.current_frame = 0;
    weapon.animation.total_frames = 5;
    weapon.animation.frame_time = 0.05f;
    weapon.animation.cooldown_time = 0.5f;
    weapon.animation.is_animating = false;
    weapon.animation.animation_clock = sfClock_create();
    weapon.animation.cooldown_clock = sfClock_create();
    weapon.frame_rect = (sfIntRect){0, 0, 256, 256};
}

void init_weapon(void)
{
    weapon.texture =
        sfTexture_createFromFile("assets/images/gun_sheet.png", NULL);
    if (!weapon.texture) {
        fprintf(stderr, "Failed to load weapon texture\n");
        return;
    }
    weapon.sprite = sfSprite_create();
    if (!weapon.sprite) {
        fprintf(stderr, "Failed to create weapon sprite\n");
        sfTexture_destroy(weapon.texture);
        return;
    }
    init_weapon_animation();
    sfSprite_setTexture(weapon.sprite, weapon.texture, sfTrue);
    sfSprite_setTextureRect(weapon.sprite, weapon.frame_rect);
    sfSprite_setPosition(weapon.sprite, (sfVector2f)
        {window_config.width / 2 + 50, window_config.height - 200});
    sfSprite_setScale(weapon.sprite, (sfVector2f){0.8f, 0.8f});
    weapon.bob_offset = 0.0f;
    weapon.is_firing = false;
}

void cleanup_weapon(void)
{
    if (weapon.sprite) {
        sfSprite_destroy(weapon.sprite);
    }
    if (weapon.texture) {
        sfTexture_destroy(weapon.texture);
    }
    if (weapon.animation.animation_clock) {
        sfClock_destroy(weapon.animation.animation_clock);
    }
    if (weapon.animation.cooldown_clock) {
        sfClock_destroy(weapon.animation.cooldown_clock);
    }
}

static bool can_fire_weapon(void)
{
    sfTime elapsed = sfClock_getElapsedTime(weapon.animation.cooldown_clock);
    float seconds = sfTime_asSeconds(elapsed);

    return seconds >= weapon.animation.cooldown_time;
}

static void start_weapon_animation(void)
{
    weapon.animation.is_animating = true;
    weapon.animation.current_frame = 0;
    sfClock_restart(weapon.animation.animation_clock);
    sfClock_restart(weapon.animation.cooldown_clock);
    play_shot_sound();
    spawn_shell_particle();
    spawn_muzzle_flash();
    shoot_enemy(player.angle);
}

void update_weapon_animation(void)
{
    sfTime elapsed;
    float seconds;

    if (!weapon.animation.is_animating) {
        return;
    }
    elapsed = sfClock_getElapsedTime(weapon.animation.animation_clock);
    seconds = sfTime_asSeconds(elapsed);
    if (seconds >= weapon.animation.frame_time) {
        weapon.animation.current_frame++;
        sfClock_restart(weapon.animation.animation_clock);
        if (weapon.animation.current_frame >= weapon.animation.total_frames) {
            weapon.animation.current_frame = 0;
            weapon.animation.is_animating = false;
        }
        weapon.frame_rect.left =
            weapon.animation.current_frame * weapon.frame_rect.width;
        sfSprite_setTextureRect(weapon.sprite, weapon.frame_rect);
    }
}

static bool check_weapon_fire(void)
{
    int key_binding = get_key_binding("Shoot");
    bool should_fire = false;

    if (key_binding < 0) {
        switch (key_binding) {
            case -2:
                should_fire = sfMouse_isButtonPressed(sfMouseRight);
                break;
            case -3:
                should_fire = sfMouse_isButtonPressed(sfMouseMiddle);
                break;
            default:
                should_fire = sfMouse_isButtonPressed(sfMouseLeft);
                break;
        }
    } else
        should_fire = sfKeyboard_isKeyPressed((sfKeyCode)key_binding);
    return should_fire;
}

void update_weapon(void)
{
    float bob_amount;
    bool should_fire = check_weapon_fire();

    weapon.bob_offset += 0.1f;
    bob_amount = sinf(weapon.bob_offset) * 5.0f;
    sfSprite_setPosition(weapon.sprite, (sfVector2f)
        {window_config.width / 2 + 150,
            window_config.height - 350 + bob_amount});
    sfSprite_setScale(weapon.sprite, (sfVector2f){1.2f, 1.2f});
    if (should_fire && !weapon.animation.is_animating && can_fire_weapon()) {
        weapon.is_firing = true;
        start_weapon_animation();
    } else
        weapon.is_firing = false;
    update_weapon_animation();
}

void draw_weapon(sfRenderWindow *window)
{
    if (weapon.sprite) {
        sfRenderWindow_drawSprite(window, weapon.sprite, NULL);
    }
}
