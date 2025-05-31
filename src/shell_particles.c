/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** shell_particles
*/

#include "particle.h"
#include "config.h"
#include "map.h"
#include <stdlib.h>
#include <math.h>

static void configure_shell_particle(particle_t *particle,
    float angle, float speed)
{
    particle->position = (sfVector2f){
        window_config.width / 2 + 350,
        window_config.height - 350
    };
    particle->velocity = (sfVector2f){
        cos(angle * M_PI / 180.0f) * speed,
        -sin(angle * M_PI / 180.0f) * speed
    };
    particle->color = sfColor_fromRGB(
        220 + rand() % 35,
        180 + rand() % 40,
        50 + rand() % 30
    );
    particle->size = 4.0f + (rand() % 2) / 5.0f;
    particle->lifetime = 0.0f;
    particle->max_lifetime = 1.5f + (rand() % 10) / 10.0f;
    particle->active = true;
}

void spawn_shell_particle(void)
{
    int index = -1;
    float fixed_angle = 60.0f;
    float speed = 3.0f + (rand() % 10) / 2.0f;

    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!shell_particle_system.particles[i].active) {
            index = i;
            break;
        }
    }
    if (index == -1)
        return;
    configure_shell_particle(&shell_particle_system.particles[index],
        fixed_angle, speed);
}

void render_shell_particles(sfRenderWindow *window)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!shell_particle_system.particles[i].active)
            continue;
        if (shell_particle_system.texture != NULL) {
            sfSprite_setPosition(shell_particle_system.sprite,
                shell_particle_system.particles[i].position);
            sfSprite_setScale(shell_particle_system.sprite,
                (sfVector2f){shell_particle_system.particles[i].size / 5.0f,
                shell_particle_system.particles[i].size / 10.0f});
            sfSprite_setColor(shell_particle_system.sprite,
                shell_particle_system.particles[i].color);
            sfSprite_setRotation(shell_particle_system.sprite, 30.0f);
            sfRenderWindow_drawSprite(window,
                shell_particle_system.sprite, NULL);
        }
    }
}
