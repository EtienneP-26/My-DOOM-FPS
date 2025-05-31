/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** particle
*/

#ifndef PARTICLE_H
    #define PARTICLE_H

    #include <SFML/Graphics.h>
    #include <stdbool.h>

    #define MAX_PARTICLES 50
    #define MAX_MUZZLE_PARTICLES 10

typedef struct particle_s {
    sfVector2f position;
    sfVector2f velocity;
    sfColor color;
    float size;
    float lifetime;
    float max_lifetime;
    bool active;
} particle_t;

typedef struct particle_system_s {
    particle_t particles[MAX_PARTICLES];
    sfClock *clock;
    sfTexture *texture;
    sfSprite *sprite;
} particle_system_t;

typedef struct muzzle_flash_s {
    particle_t particles[MAX_MUZZLE_PARTICLES];
    sfClock *clock;
    bool is_active;
} muzzle_flash_t;

extern particle_system_t shell_particle_system;
extern muzzle_flash_t muzzle_flash_system;

// Initialization and cleanup
void init_particle_systems(void);
void cleanup_particle_systems(void);

// Shell particles
void spawn_shell_particle(void);
void render_shell_particles(sfRenderWindow *window);

// Muzzle flash particles
void spawn_muzzle_flash(void);
void render_muzzle_flash(sfRenderWindow *window);

// Core particle functions
void update_particles(void);
void render_particles(sfRenderWindow *window);

#endif /* PARTICLE_H */
