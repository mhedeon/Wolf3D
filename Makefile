# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 16:01:48 by mhedeon           #+#    #+#              #
#    Updated: 2019/01/19 23:09:01 by mhedeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3D

SRC = main.c init.c other.c intro.c menu.c start.c menu_resource.c menu_lvl.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LDFLAGS = -I./frameworks/SDL2.framework/Headers/ \
			-I./frameworks/SDL2_image.framework/Headers/ \
			-I./frameworks/SDL2_mixer.framework/Headers/ \
			-F./frameworks -I./libft

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer

start: all clean
	./Wolf3D

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -g $(FLAGS) -o $(NAME) $(OBJ) $(FRAMEWORKS) -L./libft -lft

%.o: %.c
	@gcc -c $< -o $@ $(LDFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(OBJ)

re: fclean all



# PA6OTAIT
# e3r7p2:test mhedeon$ gcc  main.c  -I./frameworks/SDL2.framework/Headers/ -I./frameworks/SDL2_image.framework/Headers/   -F./frameworks -rpath ./frameworks -framework SDL2 -framework SDL2_image

