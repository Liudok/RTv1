#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/07 17:05:29 by lberezyn          #+#    #+#              #
#    Updated: 2018/02/27 14:50:09 by lberezyn         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = RTv1

SRC = src/hooks.c \
	  src/create.c \
	  src/scenes.c \
	  src/scene.c \
	  src/vectors.c \
	  src/draw.c \
	  src/figures.c \
	  src/main.c \
	  src/trace.c \

OFILES = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -O3

all: $(NAME)

%.o : src/%.c include/ft_rtv.h
	@clang $(FLAG) -o $@ -c $<

$(NAME):  $(OFILES) include/ft_rtv.h
	@make -C libft
	@clang $(FLAG) -L./libft -lft $(OFILES) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@echo "$(NAME) SUCCESSFULLY compiled"

clean:
	rm -f $(OFILES)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all, clean, fclean, re
