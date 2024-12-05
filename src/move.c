/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:09:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/05 17:59:21 by dvan-hum         ###   ########.fr       */
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

static void	move_horizontal(t_data *data, int horizontal)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		ft_memmove(data->img.data + WIDTH * y
			- horizontal * (horizontal < 0),
			data->img.data + WIDTH * y
			+ horizontal * (horizontal > 0),
			(WIDTH - abs(horizontal)) * sizeof(int));
		y++;
	}
	if (horizontal < 0)
		set_update_rect_x(data, 0, -horizontal);
	else
		set_update_rect_x(data, WIDTH - horizontal, WIDTH);
}

static void	move_vertical(t_data *data, int vertical)
{
	ft_memmove(data->img.data + vertical * WIDTH * (vertical > 0),
		data->img.data - vertical * WIDTH * (vertical < 0),
		WIDTH * (HEIGHT - abs(vertical)) * sizeof(int));
	if (vertical < 0)
		set_update_rect_y(data, 0, -vertical);
	else
		set_update_rect_y(data, HEIGHT - vertical, HEIGHT);
}

void	move(t_data *data, int horizontal, int vertical)
{
	data->x += horizontal;
	data->y += vertical;
	if (horizontal != 0)
		move_horizontal(data, horizontal);
	if (vertical != 0)
		move_vertical(data, vertical);
	mlx_refresh_image(data);
	reset_fractal(data);
}
