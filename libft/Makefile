# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/25 16:53:51 by mhedeon           #+#    #+#              #
#    Updated: 2018/12/08 21:15:13 by mhedeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ./ft_memset.c ./ft_bzero.c \
		./ft_memcpy.c ./ft_memccpy.c \
		./ft_memmove.c ./ft_memchr.c \
		./ft_memcmp.c ./ft_strlen.c \
		./ft_strdup.c ./ft_strcpy.c \
		./ft_strncpy.c ./ft_strcat.c \
		./ft_strncat.c ./ft_strlcat.c \
		./ft_strchr.c ./ft_strrchr.c \
		./ft_strstr.c ./ft_strnstr.c \
		./ft_strcmp.c ./ft_strncmp.c \
		./ft_isalpha.c ./ft_isdigit.c \
		./ft_isalnum.c ./ft_isascii.c \
		./ft_isprint.c ./ft_toupper.c \
		./ft_tolower.c ./ft_atoi.c \
		./ft_memalloc.c ft_memdel.c \
		./ft_strnew.c ./ft_strdel.c \
		./ft_strclr.c ./ft_striter.c \
		./ft_striteri.c ./ft_strmap.c \
		./ft_strmapi.c ./ft_strequ.c \
		./ft_strnequ.c ./ft_strsub.c \
		./ft_strjoin.c ./ft_strtrim.c \
		./ft_strsplit.c ./ft_itoa.c \
		./ft_putchar.c ./ft_putstr.c \
		./ft_putendl.c ./ft_putnbr.c \
		./ft_putchar_fd.c ./ft_putstr_fd.c \
		./ft_putendl_fd.c ./ft_putnbr_fd.c \
		./ft_lstnew.c ./ft_lstdelone.c \
		./ft_lstdel.c ./ft_lstadd.c \
		./ft_lstiter.c ./ft_lstmap.c \
		./ft_pow.c ./ft_abs.c \
		./ft_lstadd_back.c ./ft_lstlen.c \
		./ft_realloc.c ./ft_matrixdel.c \
		./get_next_line.c ./ft_matrixdel_h.c

SRCO = $(SRC:.c=.o)

HEADER = .

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRCO)
	@ar rc libft.a $(SRCO)
	@ranlib libft.a

%.o : %.c
	@gcc $(FLAGS) -c $< -I $@

clean:
	@rm -f $(SRCO)

fclean: clean
	@rm -f libft.a

re: fclean all
