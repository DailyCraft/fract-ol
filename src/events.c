/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:20:26 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/29 09:19:31 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int key, t_data *data)
{
	if (key == XK_Escape)
		mlx_loop_end(data->mlx);
	else if (key == XK_Left || key == XK_Right)
	{
		data->x += 2 * (-2 * (key == XK_Left) + 1);
		move(data, 2 * (-2 * (key == XK_Left) + 1), 0);
	}
	else if (key == XK_Up || key == XK_Down)
	{
		data->y += 2 * (-2 * (key == XK_Down) + 1);
		move(data, 0, 2 * (-2 * (key == XK_Down) + 1));
	}
	else if (key == XK_d)
		data->debug_enabled = !data->debug_enabled;
	else if (key == XK_c)
		data->color_index = (data->color_index + 1) % 2;
	return (0);
}

int	expose_hook(t_data *data)
{
	update_default(data);
	mlx_refresh_image(data);
	if (data->debug_enabled)
		render_debugs(data);
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
	data->y = ((HEIGHT - 1 - y) + data->y) * factor - (HEIGHT - 1 - y);
	reset_fractal(data);
	zoom(data, factor, x, y);
	mlx_refresh_image(data);
	return (0);
}

int	loop_hook(t_data *data)
{
	return (expose_hook(data));
}
