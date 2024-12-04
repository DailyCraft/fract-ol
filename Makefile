# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 08:59:59 by dvan-hum          #+#    #+#              #
#    Updated: 2024/12/04 14:51:22 by dvan-hum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc -Wall -Wextra -Werror -O3
#CC = gcc -Wall -Wextra -Werror -g -fsanitize=address

SRC = events.c fractal.c main.c mlx.c render.c move.c update.c utils.c
OBJ = $(patsubst %.c, obj/%.o, $(SRC))

all: $(NAME)

makelibs:
	make -C libft
	make -C minilibx

$(NAME): makelibs $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L ./libft -L ./minilibx -lft -lmlx -lXext -lX11 -lm

obj/%.o: src/%.c | ./obj
	$(CC) -c $< -o $@ -I ./ -I ./libft -I ./minilibx

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

bonus: all