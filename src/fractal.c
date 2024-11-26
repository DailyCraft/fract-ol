/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:12:34 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/26 10:47:30 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_rgb_smooth(double value)
{
	return ft_rgb(
			(sin(value * 0.1) + 1) * 127.5,
			(sin(value * 0.1 + M_PI / 2) + 1) * 127.5,
			(sin(value * 0.1 + M_PI) + 1) * 127.5
		);
}

static long double complex	fast_cpowl(long double complex z, double pow)
{
	if ((int) pow != pow)
		return (cpowl(z, pow));
	while (pow > 1)
	{
		z = z * z;
		pow--;
	}
	return (z);
}

int	get_point(long double complex c, double pow, t_data *data, int x, int y)
{
	int					*i;
	long double complex	*z;

	z = &data->fractal.z[y * WINDOW_WIDTH + x];
	i = &data->fractal.iterations[y * WINDOW_WIDTH + x];
	if (*i < data->fractal.iteration - 2 && *i >= 10)
		return (data->img.data[y * WINDOW_WIDTH + x]);
	while (*i < data->fractal.iteration)
	{
		*z = fast_cpowl(*z, pow) + c;
		(*i)++;
		if (cabsl(*z) > 2)
			return (ft_rgb_smooth(*i + 1 - log(log(cabsl(*z))) / log(2)));
			//return (ft_rgb((*i * 5) % 256, (*i * 3) % 256, (*i * 7) % 256));
	}
	return (0);
}

void	compute_fractal(t_data *data, int min_x, int max_x)
{
	int					x;
	int					y;
	long double complex	z;
	int					in_mb;

	x = min_x;
	while (x < max_x)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			z = (x + data->x) / data->scale + (y + data->y) / data->scale * I;
			if (data->type.type == MANDELBROT)
				in_mb = get_point(z, data->type.power, data, x, y);
			else
				in_mb = get_point(data->type.c, 2, data, x, y);
			data->img.data[y * WINDOW_WIDTH + x] = in_mb;
			y++;
		}
		x++;
	}
}

void	reset_fractal(t_data *data)
{
	int	x;
	int	y;

	data->fractal.iteration = fminl(data->scale / 25, 500);
	ft_bzero(data->fractal.iterations, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			data->fractal.z[y * WINDOW_WIDTH + x] = (x + data->x) / data->scale
				+ (y + data->y) / data->scale * I;
			y++;
		}
		x++;
	}
}
