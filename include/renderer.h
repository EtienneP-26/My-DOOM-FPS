/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** renderer
*/

#ifndef RENDERER_H
    #define RENDERER_H

    #include <SFML/Graphics.h>

void init_renderer(void);
void cleanup_renderer(void);
void render_frame(sfRenderWindow *window);
void draw_minimap(sfRenderWindow *window);
void draw_sky_and_ground(sfRenderWindow *window);

extern sfTexture *wall_texture;

#endif /* RENDERER_H */
