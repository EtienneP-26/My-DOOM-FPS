/*
** EPITECH PROJECT, 2025
** v1.0.0
** File description:
** renderer
*/

#include "renderer.h"
#include "config.h"
#include "map.h"
#include "raycaster.h"
#include "hud.h"
#include "weapon.h"
#include "player.h"
#include "particle.h"
#include "enemy.h"
#include <stdio.h>

sfTexture *wall_texture;
sfTexture *sky_texture;

void init_renderer(void)
{
    wall_texture = sfTexture_createFromFile("assets/images/wall.png", NULL);
    if (!wall_texture) {
        fprintf(stderr, "Failed to load wall texture\n");
        return;
    }
    sky_texture = sfTexture_createFromFile("assets/images/sky.png", NULL);
    if (!sky_texture) {
        fprintf(stderr, "Failed to load sky texture\n");
    }
}

void cleanup_renderer(void)
{
    if (wall_texture) {
        sfTexture_destroy(wall_texture);
    }
    if (sky_texture) {
        sfTexture_destroy(sky_texture);
    }
}

static void setup_ground(sfRectangleShape *ground, sfVector2f size)
{
    sfRectangleShape_setSize(ground, size);
    sfRectangleShape_setPosition(ground,
        (sfVector2f){0, window_config.height / 2});
    sfRectangleShape_setFillColor(ground, sfColor_fromRGB(50, 50, 50));
}

static int calculate_sky_offset(int sky_width)
{
    float center_angle = 270.0f;
    float relative_angle = player.angle - center_angle;
    float sky_offset;
    float center_pixel;

    while (relative_angle < 0)
        relative_angle += 360.0f;
    while (relative_angle >= 360.0f)
        relative_angle -= 360.0f;
    center_pixel = (relative_angle / 360.0f) * sky_width;
    sky_offset = center_pixel - (window_config.width / 2);
    sky_offset = fmodf(sky_offset + sky_width, sky_width);
    return (int)sky_offset;
}

static void setup_sky_with_texture(sfRectangleShape *sky, sfVector2f size)
{
    int sky_width;
    int offset;

    sfRectangleShape_setSize(sky, size);
    sfRectangleShape_setPosition(sky, (sfVector2f){0, 0});
    if (sky_texture) {
        sky_width = sfTexture_getSize(sky_texture).x;
        sfTexture_setRepeated(sky_texture, sfTrue);
        sfRectangleShape_setTexture(sky, sky_texture, sfTrue);
        offset = calculate_sky_offset(sky_width);
        sfRectangleShape_setTextureRect(sky, (sfIntRect){offset, 0,
            window_config.width, sfTexture_getSize(sky_texture).y});
    } else {
        sfRectangleShape_setFillColor(sky, sfColor_fromRGB(80, 27, 19));
    }
}

void draw_sky_and_ground(sfRenderWindow *window)
{
    sfRectangleShape *sky = sfRectangleShape_create();
    sfRectangleShape *ground = sfRectangleShape_create();
    sfVector2f size = {window_config.width, window_config.height / 2};

    setup_ground(ground, size);
    setup_sky_with_texture(sky, size);
    sfRenderWindow_drawRectangleShape(window, sky, NULL);
    sfRenderWindow_drawRectangleShape(window, ground, NULL);
    sfRectangleShape_destroy(sky);
    sfRectangleShape_destroy(ground);
}

void draw_minimap(sfRenderWindow *window)
{
    sfRectangleShape *tile;

    for (int i = 0; i < game_map.width * game_map.height; i++) {
        if (game_map.data[i] == 1) {
            tile = create_map_tile(i);
            sfRenderWindow_drawRectangleShape(window, tile, NULL);
            sfRectangleShape_destroy(tile);
        }
    }
    draw_player(window);
}

void render_frame(sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfColor_fromRGB(200, 200, 200));
    draw_sky_and_ground(window);
    render_view(window);
    render_enemies(window);
    draw_minimap(window);
    draw_weapon(window);
    render_particles(window);
    draw_hud(window, init_hud());
    sfRenderWindow_display(window);
}
