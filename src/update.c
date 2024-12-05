/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:15:57 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/05 18:32:37 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	update_default(t_data *data)
{
	data->rect_update_min_x = 0;
	data->rect_update_max_x = WIDTH;
	if (update_rect(data))
	{
		data->rect_update_max_x = 0;
		data->fractal.iteration += 2;
		return (1);
	}
	data->rect_update_max_x = 0;
	return (0);
}

static int	update_centered_x(t_data *data, int i, int y)
{
	int	x;

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
	return (x);
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
		x = update_centered_x(data, i, y);
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

static void	update_rect_iter(int min, int i, int minor_max, t_data *data)
{
	int	major;
	int	minor;
	int	max;

	if (data->rect_update_max_x != 0)
		max = ft_min(data->rect_update_max_x,
				data->rect_update_min_x + WIDTH / 10.0 * (i + 1));
	else
		max = ft_min(data->rect_update_max_y,
				data->rect_update_min_y + HEIGHT / 10.0 * (i + 1));
	major = min;
	while (major < max)
	{
		minor = 0;
		while (minor < minor_max)
		{
			if (data->rect_update_max_x != 0)
				update_point(data, major, minor);
			else
				update_point(data, minor, major);
			minor++;
		}
		major++;
	}
}

int	update_rect(t_data *data)
{
	static double	last_x = -1;
	static double	last_y = -1;
	static int		i;

	if (last_x != data->x || last_y != data->y)
	{
		last_x = data->x;
		last_y = data->y;
		i = 0;
	}
	if (data->rect_update_max_x != 0)
		update_rect_iter(data->rect_update_min_x + WIDTH / 10.0 * i,
			i, HEIGHT, data);
	else
		update_rect_iter(data->rect_update_min_y + HEIGHT / 10.0 * i,
			i, WIDTH, data);
	i++;
	if (i == 10)
	{
		i = 0;
		return (1);
	}
	return (0);
}
