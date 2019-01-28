# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 16:01:48 by mhedeon           #+#    #+#              #
#    Updated: 2019/01/28 23:18:27 by mhedeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3D

SRC = main.c init.c intro.c menu.c menu_resource.c menu_lvl.c \
		texture.c map.c map_check.c map_trash.c loading.c lvl1.c cast.c \
		draw.c event.c rotation.c sprite.c hud.c face.c death.c lvl2.c get_error.c \
		fight.c game.c door.c other_1.c other_2.c init_trash.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LDFLAGS = -I./frameworks/SDL2.framework/Headers/ \
			-I./frameworks/SDL2_image.framework/Headers/ \
			-I./frameworks/SDL2_mixer.framework/Headers/ \
			-I./frameworks/SDL2_ttf.framework/Headers/ \
			-F./frameworks -I./libft

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

start: all clean
	./Wolf3D

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -g -o $(NAME) $(OBJ) $(FRAMEWORKS) -L./libft -lft

%.o: %.c
	@gcc -c $< -o $@ $(LDFLAGS) $(FLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(OBJ)

re: fclean all
