/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:57:51 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/29 09:27:13 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	smooth_rgb(double value)
{
	return (ft_rgb(
			(sin(value * 0.1) + 1) * 127.5,
			(sin(value * 0.1 + M_PI / 2) + 1) * 127.5,
			(sin(value * 0.1 + M_PI) + 1) * 127.5
		));
}

int	get_color(t_data *data, int x, int y)
{
	t_point	*point;

	point = &data->fractal.points[y * WIDTH + x];
	if (point->iteration >= data->fractal.iteration)
		return (0);
	else if (data->color_index == 0)
		return (smooth_rgb(point->iteration + 1 - log2(log(cabsl(point->z)))));
	else if (data->color_index == 1)
		return (ft_rgb((point->iteration * 5) % 256,
				(point->iteration * 3) % 256, (point->iteration * 7) % 256));
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

void	render_debugs(t_data *data)
{
	char	*str;

	ft_asprintf(&str, "Open/hide debug: D  Iterations: %d  Scale: %u",
		data->fractal.iteration, (unsigned) data->scale);
	mlx_string_put(data->mlx, data->window, 10, 10, 0, str);
	free(str);
}
