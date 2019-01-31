# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 16:01:48 by mhedeon           #+#    #+#              #
#    Updated: 2019/01/31 18:13:08 by mhedeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC = cast.c death.c door.c draw.c event.c face.c fight.c game.c \
		get_error.c hud.c init_trash.c init.c intro.c loading.c \
		lvl1.c lvl2.c lvl3.c lvl4.c main.c map_check.c map_trash.c \
		map.c menu_lvl.c menu_resource.c menu.c other_1.c other_2.c \
		rotation.c sprite.c texture.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I./frameworks/SDL2.framework/Headers/ \
			-I./frameworks/SDL2_image.framework/Headers/ \
			-I./frameworks/SDL2_mixer.framework/Headers/ \
			-I./frameworks/SDL2_ttf.framework/Headers/ \
			-F./frameworks -I./libft

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
												-framework SDL2_image \
												-framework SDL2_mixer \
												-framework SDL2_ttf

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@gcc -g -o $(NAME) $(OBJ) $(FRAMEWORKS) -L./libft -lft

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@rm -f $(OBJ)

re: fclean all
	@make -C libft re
