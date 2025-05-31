##
## EPITECH PROJECT, 2025
## v1.0.0
## File description:
## Makefile
##

SRC	=	src/main.c \
		src/config.c \
		src/game.c \
		src/player.c \
		src/map.c \
		src/renderer.c \
		src/raycaster.c \
		src/ray_calculation.c \
		src/texture_mapping.c \
		src/rendering_ray.c \
		src/hud.c \
		src/draw_hud.c \
		src/weapon.c \
		src/player_mvt.c \
		src/keybinds.c \
		src/flashlight.c \
		src/sound_manager.c \
		src/sound_effects.c \
		src/save_system.c \
		src/particle.c \
		src/main_menu.c \
		src/play_menu.c \
		src/settings/bind_event.c \
		src/settings/destroy_settings.c \
		src/settings/draw_settings.c \
		src/settings/event_settings.c \
		src/settings/init.c \
		src/settings/malloc_settings.c \
		src/settings/patern_creat.c \
		src/settings/resize.c \
		src/settings/settings.c \
		src/shell_particles.c \
		src/muzzle_flash.c \
		src/particle_init.c \
		src/settings/global_settings.c \
		src/enemy.c \
		src/render_enemy_sprite.c \
		src/init_enemies.c \
## src/utils.c

OBJ_DIR	=	obj/
OBJ	=	$(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRC))

CFLAGS	=	-I./include -Wall -Wextra -Werror
CSFML	=	-lcsfml-audio -lcsfml-graphics -lcsfml-system -lcsfml-window -lm
RM	=	rm -rf
NAME	=	My-DOOM

all:	$(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)settings

$(OBJ_DIR)%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CSFML) $(CFLAGS)

clean:
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)

sclean:
	$(RM) saves/

sfclean: sclean fclean

re:	fclean all

run: re
	./$(NAME)
	make fclean
