##
## EPITECH PROJECT, 2024
## MAkefile
## File description:
## Makefile
##

CFLAGS   = -g3 -Wall -Wextra -Iinclude
LDFLAGS  = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

SRC      =  src/main.c \
			src/init/init.c \
			src/free/free.c \
			src/display/raycast.c \
			src/display/rotate_raycast.c \
			src/init/init_weapon.c \
			src/event/move.c \
			src/display/weapon.c \
			src/ui/menu.c \
			src/ui/exit.c \
			src/ui/settings.c \
			src/event/event.c \
			src/ui/functions_settings.c \
			src/event/collision.c \
			src/display/process_display.c \
			src/event/manage_window.c \
			src/display/draw_wall_slice.c \
			src/init/init_player.c \
			src/init/init_game.c \
			src/free/free_map.c \
			src/ennemy/enemy.c \
			src/free/free_menu.c \
			src/free/free_game.c \
			src/save.c \
			src/maze_generator.c \
			src/victory.c \
			src/display/particles.c \
			src/ennemy/enemy_visibility.c \
			src/init/init_hud.c \
			src/display/display_hud.c \
			src/display/update_hud.c \
			src/display/lighting.c \
			src/ui/functions_sound.c

LSRC     = $(wildcard lib/*.c)

OBJ      = $(SRC:.c=.o)
LOBJ     = $(LSRC:.c=.o)
NAME     = wolf3d

all: $(NAME)

$(NAME): $(OBJ) $(LOBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LOBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: ${NAME}
	./${NAME}

val: ${NAME}
	valgrind ./${NAME}

clean:
	$(RM) $(OBJ) $(LOBJ)

fclean: clean
	$(RM) $(NAME) *.o *.gcda *.gcno

re: fclean all

.PHONY: all clean fclean re tests_run
