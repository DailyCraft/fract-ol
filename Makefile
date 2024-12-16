# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 08:59:59 by dvan-hum          #+#    #+#              #
#    Updated: 2024/12/16 08:45:36 by dvan-hum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc -Wall -Wextra -Werror -O3

SRC = events.c fractal.c main.c mlx.c move.c print.c render.c update.c utils.c
OBJ = $(SRC:%.c=obj/%.o)
LIBS = minilibx/libmlx.a libft/libft.a

ifndef VERBOSE
MAKEFLAGS += --silent
endif

all: $(NAME)

%.a:
	make -C $(shell dirname $@)

$(NAME): $(LIBS) $(OBJ)
	echo "\n\t\e[1;32mBuilding\e[0m \e[36m$(NAME)\e[0m\n"
	$(CC) -o $(NAME) $(OBJ) -L ./libft -L ./minilibx -lft -lmlx -lXext -lX11 -lm

obj/%.o: src/%.c
	echo "$(NAME) \e[90m➤\e[0m \e[32mCompiling\e[0m \e[36m$<\e[0m"
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ -I ./ -I ./libft -I ./minilibx

clean:
	make -C minilibx clean
	make -C libft clean
	echo "$(NAME) \e[90m➤\e[0m\t\e[1;31mCleaning object files\e[0m"
	rm -rf ./obj

fclean:
	make -C minilibx clean
	make -C libft fclean
	echo "$(NAME) \e[90m➤\e[0m\t\e[1;31mCleaning object files\e[0m"
	rm -rf ./obj
	echo "$(NAME) \e[90m➤\e[0m\t\e[31mCleaning $(NAME)\e[0m"
	rm -f $(NAME)

re: fclean all

bonus: all