/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:20:26 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/27 16:29:44 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_loop_end(data->mlx);
		return (0);
	}
	else if (key == XK_Left || key == XK_Right)
	{
		data->x += 2 * (-2 * (key == XK_Left) + 1);
		move(data, 2 * (-2 * (key == XK_Left) + 1), 0);
	}
	else if (key == XK_Up || key == XK_Down)
	{
		data->y += 2 * (-2 * (key == XK_Up) + 1);
		move(data, 0, 2 * (-2 * (key == XK_Up) + 1));
	}
	else if (key == XK_d)
	{
		data->debug_enabled = !data->debug_enabled;
		return (0);
	}
	else if (key == XK_c)
	{
		data->color_index = (data->color_index + 1) % 2;
		return (0);
	}
	else
		return (0);
	reset_fractal(data);
	mlx_refresh_image(data);
	return (0);
}

int	expose_hook(t_data *data)
{
	static int	min_x = 0;
	char		*str;

	if (min_x >= WIDTH)
	{
		data->fractal.iteration += 2;
		min_x = 0;
	}
	compute_fractal(data, min_x, min_x + WIDTH / 10);
	draw_pixels(data, min_x, min_x + WIDTH / 10);
	mlx_refresh_image(data);
	if (data->debug_enabled)
	{
		ft_asprintf(&str, "Open/hide debug: D  Iterations: %d  Scale: %u",
			data->fractal.iteration, (unsigned) data->scale);
		mlx_string_put(data->mlx, data->window, 10, 10, 0, str);
		free(str);
	}
	min_x += WIDTH / 10;
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	double	factor;

	if (button == 4)
		factor = 1.05;
	else if (button == 5)
		factor = 0.95;
	else
		return (0);
	data->scale *= factor;
	data->x = (x + data->x) * factor - x;
	data->y = (y + data->y) * factor - y;
	reset_fractal(data);
	zoom(data, factor, x, y);
	mlx_refresh_image(data);
	return (0);
}

int	loop_hook(t_data *data)
{
	return (expose_hook(data));
}
