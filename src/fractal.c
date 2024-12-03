/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:12:34 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/03 09:52:08 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_lcomplex	fast_cpowl(t_lcomplex z, double pow)
{
	t_lcomplex	original;

	if ((int) pow != pow)
		return (cpowl(z, pow));
	original = z;
	while (pow > 1)
	{
		z *= original;
		pow--;
	}
	return (z);
}

int	get_point(t_lcomplex c, double pow, t_data *data, int pos)
{
	t_point	*point;

	point = data->fractal.points + pos;
	if (point->iteration < data->fractal.iteration - 2 && point->iteration >= 5)
		return (0);
	while (point->iteration < data->fractal.iteration)
	{
		point->z = fast_cpowl(point->z, pow) + c;
		point->iteration++;
		if (cabsl(point->z) > 2)
			return (1);
	}
	return (1);
}

void	update_point(t_data *data, int x, int y)
{
	t_lcomplex	z;
	int			updated;

	updated = 0;
	if (data->fractal.type == MANDELBROT)
	{
		z = (x + data->x) / data->scale + (y + data->y) / data->scale * I;
		updated = get_point(z, data->fractal.power, data, y * WIDTH + x);
	}
	else if (data->fractal.type == JULIA)
		updated = get_point(data->fractal.c, 2, data, y * WIDTH + x);
	if (updated)
		mlx_set_pixel(data, x, y, get_color(data, x, y));
}

void	reset_point(t_data *data, int x, int y)
{
	t_point	*point;

	point = &data->fractal.points[y * WIDTH + x];
	point->iteration = 0;
	point->z = (x + data->x) / data->scale + (y + data->y) / data->scale * I;
}

void	reset_fractal(t_data *data)
{
	int	x;
	int	y;

	data->fractal.iteration = fminl(data->scale / 25, 250);
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			reset_point(data, x, y);
			y++;
		}
		x++;
	}
}
