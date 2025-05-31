/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** muzzle_flash
*/

#include "particle.h"
#include "config.h"
#include <stdlib.h>

static void configure_muzzle_flash_particle(particle_t *particle)
{
    float baseX = window_config.width / 2 + 160 + (rand() % 30) - 15;
    float baseY = window_config.height - 320 + (rand() % 20) - 10;
    float size = 3.0f + (rand() % 6);

    particle->position = (sfVector2f){baseX, baseY};
    particle->velocity = (sfVector2f){0.0f, 0.0f};
    particle->color = sfColor_fromRGBA(
        220 + rand() % 35,
        120 + rand() % 80,
        10 + rand() % 30,
        200 + rand() % 55
    );
    particle->size = size;
    particle->lifetime = 0.0f;
    particle->max_lifetime = 0.1f + (rand() % 10) / 100.0f;
    particle->active = true;
}

void spawn_muzzle_flash(void)
{
    int num_particles = 3 + rand() % (MAX_MUZZLE_PARTICLES - 3);
    int i;

    for (i = 0; i < MAX_MUZZLE_PARTICLES; i++) {
        muzzle_flash_system.particles[i].active = false;
    }
    for (i = 0; i < num_particles; i++) {
        configure_muzzle_flash_particle(&muzzle_flash_system.particles[i]);
    }
    muzzle_flash_system.is_active = true;
    sfClock_restart(muzzle_flash_system.clock);
}

static void render_single_muzzle_particle(sfRenderWindow *window,
    particle_t *particle)
{
    sfCircleShape *circle = sfCircleShape_create();
    sfCircleShape *glow = sfCircleShape_create();
    sfColor glowColor = particle->color;

    sfCircleShape_setRadius(circle, particle->size);
    sfCircleShape_setPosition(circle, (sfVector2f){
        particle->position.x - particle->size,
        particle->position.y - particle->size});
    sfCircleShape_setFillColor(circle, particle->color);
    glowColor.a = glowColor.a / 3;
    sfCircleShape_setRadius(glow, particle->size * 1.8f);
    sfCircleShape_setPosition(glow, (sfVector2f){
        particle->position.x - particle->size * 1.8f,
        particle->position.y - particle->size * 1.8f});
    sfCircleShape_setFillColor(glow, glowColor);
    sfRenderWindow_drawCircleShape(window, glow, NULL);
    sfRenderWindow_drawCircleShape(window, circle, NULL);
    sfCircleShape_destroy(circle);
    sfCircleShape_destroy(glow);
}

void render_muzzle_flash(sfRenderWindow *window)
{
    int i;

    if (!muzzle_flash_system.is_active)
        return;
    for (i = 0; i < MAX_MUZZLE_PARTICLES; i++) {
        if (!muzzle_flash_system.particles[i].active)
            continue;
        render_single_muzzle_particle(window,
            &muzzle_flash_system.particles[i]);
    }
}
