/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:20:26 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/25 15:31:54 by dvan-hum         ###   ########.fr       */
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
		data->x += 100 * (-2 * (key == XK_Left) + 1);
	else if (key == XK_Up || key == XK_Down)
		data->y += 100 * (-2 * (key == XK_Up) + 1);
	else
		return (0);
	expose_hook(data);
	return (0);
}

int	expose_hook(t_data *data)
{
	(void) data;
	/* compute_fractal(data, 0, 1600);
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0); */
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4) // SCROLL_UP
	{
		data->scale *= 1.2;
		data->x = (x + data->x) * 1.2 - x;
		data->y = (y + data->y) * 1.2 - y;
	}
	else if (button == 5) // SCROLL_DOWN
	{
		data->scale *= 0.8;
		data->x = (x + data->x) * 0.8 - x;
		data->y = (y + data->y) * 0.8 - y;
	}
	else
		return (0);
	reset_fractal(data);
	zoom_in(data, 1.2, x, y);
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	return (0);
}

int	loop_hook(t_data *data)
{
	static int	min_x = 0;
	char		*str;

	if (min_x >= 1600)
	{
		data->fractal.iteration += 2;
		min_x = 0;
	}
	compute_fractal(data, min_x, min_x + 160);
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	str = ft_itoa(data->fractal.iteration);
	mlx_string_put(data->mlx, data->window, 10, 10, 0xffffff, str);
	free(str);
	min_x += 160;
	return (0);
}
