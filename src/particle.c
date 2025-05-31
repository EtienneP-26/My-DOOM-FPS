/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** particle
*/

#include "particle.h"
#include "config.h"
#include <stdlib.h>
#include <math.h>

particle_system_t shell_particle_system;
muzzle_flash_t muzzle_flash_system;

static void update_particle_lifetime(particle_t *particle, float dt)
{
    float alpha;

    particle->lifetime += dt;
    if (particle->lifetime >= particle->max_lifetime) {
        particle->active = false;
        return;
    }
    alpha = 255.0f * (1.0f - (particle->lifetime /
        particle->max_lifetime) * 0.8f);
    particle->color.a = (sfUint8)alpha;
}

static void update_particle_physics(particle_t *particle,
    float dt, float floor_height)
{
    particle->velocity.y += 64.0f * dt;
    particle->position.x += particle->velocity.x;
    particle->position.y += particle->velocity.y;
    if (particle->position.y > floor_height) {
        particle->position.y = floor_height;
        particle->velocity.y *= -0.3f;
        particle->velocity.x *= 0.5f;
    }
}

static void update_muzzle_flash_particles(float dt)
{
    int i;
    bool any_active = false;

    if (!muzzle_flash_system.is_active)
        return;
    for (i = 0; i < MAX_MUZZLE_PARTICLES; i++) {
        if (muzzle_flash_system.particles[i].active)
            update_particle_lifetime(&muzzle_flash_system.particles[i], dt);
        if (muzzle_flash_system.particles[i].active)
            any_active = true;
    }
    if (!any_active)
        muzzle_flash_system.is_active = false;
}

void update_particles(void)
{
    float dt;
    float floor_height;
    int i;

    dt = sfTime_asSeconds(sfClock_restart(shell_particle_system.clock));
    floor_height = window_config.height * 0.98f;
    for (i = 0; i < MAX_PARTICLES; i++) {
        if (!shell_particle_system.particles[i].active)
            continue;
        update_particle_lifetime(&shell_particle_system.particles[i], dt);
        if (shell_particle_system.particles[i].active) {
            update_particle_physics(&shell_particle_system.particles[i],
                dt, floor_height);
        }
    }
    update_muzzle_flash_particles(dt);
}

void render_particles(sfRenderWindow *window)
{
    render_shell_particles(window);
    render_muzzle_flash(window);
}
