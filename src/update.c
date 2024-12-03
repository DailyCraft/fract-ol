/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:15:57 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/03 10:50:13 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	update_default(t_data *data)
{
	data->rect_update_min_x = 0;
	data->rect_update_min_y = 0;
	data->rect_update_max_x = WIDTH;
	data->rect_update_max_y = HEIGHT;
	if (update_rect(data))
	{
		data->rect_update_max_x = 0;
		data->rect_update_max_y = 0;
		data->fractal.iteration += 2;
		return (1);
	}
	data->rect_update_max_x = 0;
	data->rect_update_max_y = 0;
	return (0);
}

int	update_centered(t_data *data)
{
	static int		i;
	static double	last_scale = -1;
	int				x;
	int				y;

	if (last_scale != (double) data->scale)
	{
		last_scale = data->scale;
		i = 1;
	}
	x = 0;
	y = ft_max(0, data->centered_update_y - HEIGHT / 20.0 * i);
	while (y < data->centered_update_y + HEIGHT / 20.0 * i)
	{
		x = ft_max(0, data->centered_update_x - WIDTH / 20.0 * i);
		while (x < data->centered_update_x + WIDTH / 20.0 * i)
		{
			if (x < WIDTH && y < HEIGHT
				&& (x <= data->centered_update_x - WIDTH / 20.0 * (i - 1)
					|| x >= data->centered_update_x + WIDTH / 20.0 * (i - 1)
					|| y <= data->centered_update_y - HEIGHT / 20.0 * (i - 1)
					|| y >= data->centered_update_y + HEIGHT / 20.0 * (i - 1)))
				update_point(data, x, y);
			x++;
		}
		y++;
	}
	i++;
	if (y >= HEIGHT && x >= WIDTH)
	{
		i = 1;
		return (1);
	}
	return (0);
}

int	update_rect(t_data *data)
{
	static double	last_x = -1;
	static double	last_y = -1;
	static int		i;
	int				x;
	int				y;

	if (last_x != data->x || last_y != data->y)
	{
		last_x = data->x;
		last_y = data->y;
		i = 0;
	}
	x = data->rect_update_min_x + WIDTH / 10.0 * i;
	while (x < ft_min(data->rect_update_max_x,
			data->rect_update_min_x + WIDTH / 10.0 * (i + 1)))
	{
		y = data->rect_update_min_y;
		while (y < data->rect_update_max_y)
		{
			update_point(data, x, y);
			y++;
		}
		x++;
	}
	i++;
	if (i == 10)
	{
		i = 0;
		return (1);
	}
	return (0);
}

void	set_update_rect_x(t_data *data, int min_x, int max_x)
{
	data->rect_update_min_x = ft_max(data->rect_update_min_x, ft_max(0, min_x));
	data->rect_update_max_x = ft_min(data->rect_update_max_x,
			ft_min(WIDTH, max_x));
}

void	set_update_rect_y(t_data *data, int min_y, int max_y)
{
	data->rect_update_min_y = ft_max(data->rect_update_min_y, ft_max(0, min_y));
	data->rect_update_max_y = ft_min(data->rect_update_max_y,
			ft_min(HEIGHT, max_y));
}
