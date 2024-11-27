/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:57:51 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/27 16:22:11 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*void	zoom(t_data *data, double factor, int mouse_x, int mouse_y)
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
}

void	move(t_data *data, int horizontal, int vertical)
{
	int	y;

	(void) vertical;
	y = 0;
	while (y < HEIGHT)
	{
		ft_memmove(data->img.data + WIDTH * y - horizontal * (horizontal < 0),
			data->img.data + WIDTH * y + horizontal * (horizontal > 0),
			(WIDTH - abs(horizontal)) * sizeof(int));
		y++;
	}
	ft_memmove(data->img.data - vertical * WIDTH * (vertical < 0),
		data->img.data + vertical * WIDTH * (vertical > 0),
		WIDTH * (HEIGHT - abs(vertical)) * sizeof(int));
}*/

int	smooth_rgb(double value)
{
	return (ft_rgb(
			(sin(value * 0.1) + 1) * 127.5,
			(sin(value * 0.1 + M_PI / 2) + 1) * 127.5,
			(sin(value * 0.1 + M_PI) + 1) * 127.5
		));
}

int get_color(t_data *data, int x, int y)
{
	t_point	*point;

	point = &data->fractal.points[y * WIDTH + x];
	if (point->iteration >= data->fractal.iteration)
		return (0);
	else if (data->color_index == 0)
		return (smooth_rgb(point->iteration + 1 - log(log(cabsl(point->z))) / log(2)));
	else if (data->color_index == 1)
		return (ft_rgb((point->iteration * 5) % 256, (point->iteration * 3) % 256, (point->iteration * 7) % 256));
	return (-1);
}

void	draw_pixels(t_data *data, int min_x, int max_x)
{
	int	x;
	int	y;

	x = min_x;
	while (x < max_x)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_set_pixel(data, x, y, get_color(data, x, y));
			y++;
		}
		x++;
	}
}
