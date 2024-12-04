/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:57:51 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/04 14:42:59 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_view(t_data *data)
{
	data->scale = 350;
	data->x = WIDTH / -2.0;
	data->y = HEIGHT / -2.0;
	data->centered_update_x = WIDTH / 2;
	data->centered_update_y = HEIGHT / 2;
	reset_fractal(data);
}

static int	smooth_rgb(double value, double r, double g, double b)
{
	return (ft_rgb(
			(sin(value * 0.1 + r) + 1) * 127.5,
			(sin(value * 0.1 + g) + 1) * 127.5,
			(sin(value * 0.1 + b) + 1) * 127.5
		));
}

int	get_color(t_data *data, int x, int y)
{
	t_point	*point;

	point = &data->fractal.points[y * WIDTH + x];
	if (point->iteration >= data->fractal.iteration)
		return (0);
	return (smooth_rgb(
			point->iteration + 1 - log2(log(cabsl(point->z))),
			M_PI * (data->color_index >= 9)
			/ ((data->color_index >= 18) + 1),
			M_PI * (data->color_index % 9 >= 3)
			/ ((data->color_index % 9 >= 6) + 1),
			M_PI * (data->color_index % 3 >= 1)
			/ ((data->color_index % 3 >= 2) + 1)
		));
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

void	render_debugs(t_data *data)
{
	char	*str;

	ft_asprintf(&str, "Iterations: %d  Scale: %u  Color: %d",
		data->fractal.iteration, (unsigned) data->scale, data->color_index);
	mlx_string_put(data->mlx, data->window, 10, 10,
		(data->debug_enabled - 1) * 0xffffff,
		str);
	free(str);
}
