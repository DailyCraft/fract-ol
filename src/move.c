/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:09:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/03 10:14:35 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_data *data, double factor, int mouse_x, int mouse_y)
{
	int	old[WIDTH * HEIGHT];
	int	x;
	int	y;
	int	old_x;
	int	old_y;

	ft_memcpy(old, data->img.data, WIDTH * HEIGHT * sizeof(int));
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			old_x = (x - mouse_x) / factor + mouse_x;
			old_y = (y - mouse_y) / factor + mouse_y;
			if (old_x >= 0 && old_x < WIDTH && old_y >= 0 && old_y < HEIGHT)
				data->img.data[y * WIDTH + x] = old[old_y * WIDTH + old_x];
			x++;
		}
		y++;
	}
	data->centered_update_x = mouse_x;
	data->centered_update_y = (HEIGHT - 1 - mouse_y);
}

static void	reset_moved(t_data *data, int horizontal, int vertical)
{
	int	x;
	int	y;

	(void) vertical;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (x <= -horizontal || x >= WIDTH - horizontal)
				reset_point(data, x, y);
			y++;
		}
		x++;
	}
}

static void	move_horizontal(t_data *data, int horizontal)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		ft_memmove(data->fractal.points + WIDTH * y
			- horizontal * (horizontal < 0),
			data->fractal.points + WIDTH * y
			+ horizontal * (horizontal > 0),
			(WIDTH - abs(horizontal)) * sizeof(t_point));
		y++;
	}
	if (horizontal < 0)
		set_update_rect_x(data, 0, -horizontal);
	else
		set_update_rect_x(data, WIDTH - horizontal, WIDTH);
	set_update_rect_y(data, 0, HEIGHT);
}

static void	move_vertical(t_data *data, int vertical)
{
	ft_memmove(data->fractal.points - vertical * WIDTH * (vertical < 0),
		data->fractal.points + vertical * WIDTH * (vertical > 0),
		WIDTH * (HEIGHT - abs(vertical)) * sizeof(t_point));
	if (vertical < 0)
		set_update_rect_y(data, HEIGHT - vertical, HEIGHT);
	else
		set_update_rect_y(data, 0, vertical);
	set_update_rect_x(data, 0, WIDTH);
}

void	move(t_data *data, int horizontal, int vertical)
{
	data->fractal.iteration = fminl(data->scale / 25, 500);
	if (horizontal != 0)
		move_horizontal(data, horizontal);
	if (vertical != 0)
		move_vertical(data, vertical);
	reset_moved(data, horizontal, vertical);
	draw_pixels(data, 0, WIDTH);
}
