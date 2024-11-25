# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 08:59:59 by dvan-hum          #+#    #+#              #
#    Updated: 2024/11/25 09:59:58 by dvan-hum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc -Wall -Wextra -Werror -g

SRC = events.c fractal.c main.c render.c
OBJ = $(patsubst %.c, obj/%.o, $(SRC))
INCLUDES = ./

all: $(NAME)

makelibft:
	make -C libft
	cp libft/libft.a ./

makeminilibx:
	make -C minilibx
	cp minilibx/libmlx.a ./

$(NAME): makelibft makeminilibx $(OBJ)
	$(CC) $(OBJ) -I ./libft -L ./libft -lft -I ./minilibx -L ./minilibx -lmlx -lXext -lX11 -lm -o $(NAME)

obj/%.o: src/%.c | ./obj
	$(CC) -c $< -o $@ -I $(INCLUDES) -I ./libft -L ./libft -lft -I ./minilibx -L ./minilibx -lmlx

./obj:
	mkdir obj

clean:
	rm -rf ./obj
	make -C libft clean
	make -C minilibx clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all