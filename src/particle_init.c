/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** particle_init
*/

#include "particle.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

static void init_shell_particle_system(void)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        shell_particle_system.particles[i].active = false;
    }
    shell_particle_system.clock = sfClock_create();
    shell_particle_system.texture =
        sfTexture_createFromFile("assets/images/shell.png", NULL);
    if (!shell_particle_system.texture) {
        fprintf(stderr, "Warning: Failed to load shell texture\n");
    }
    shell_particle_system.sprite = sfSprite_create();
    if (shell_particle_system.texture) {
        sfSprite_setTexture(shell_particle_system.sprite,
            shell_particle_system.texture, sfTrue);
    }
}

static void init_muzzle_flash_system(void)
{
    for (int i = 0; i < MAX_MUZZLE_PARTICLES; i++) {
        muzzle_flash_system.particles[i].active = false;
    }
    muzzle_flash_system.clock = sfClock_create();
    muzzle_flash_system.is_active = false;
}

void init_particle_systems(void)
{
    init_shell_particle_system();
    init_muzzle_flash_system();
}

void cleanup_particle_systems(void)
{
    sfClock_destroy(shell_particle_system.clock);
    if (shell_particle_system.texture)
        sfTexture_destroy(shell_particle_system.texture);
    if (shell_particle_system.sprite)
        sfSprite_destroy(shell_particle_system.sprite);
    sfClock_destroy(muzzle_flash_system.clock);
}
