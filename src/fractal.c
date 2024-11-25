/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:12:34 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/25 15:30:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* int ft_rgb_smooth(double value)
{
    int red = (int)((sin(value * 0.1) + 1) * 127.5);
    int green = (int)((sin(value * 0.1 + M_PI / 2) + 1) * 127.5);
    int blue = (int)((sin(value * 0.1 + M_PI) + 1) * 127.5);
	
    return ft_rgb(red, green, blue);
} */

int	get_point(complex c, double pow, t_fractal *fractal, int x, int y)
{
	int		*i;
	complex	*z;

	z = &fractal->z[y * 1600 + x];
	i = &fractal->iterations[y * 1600 + x];
	while (*i < fractal->iteration)
	{
		*z = cpow(*z, pow) + c;
		(*i)++;
		if (cabs(*z) > 2)
			return (ft_rgb((*i * 5) % 256, (*i * 3) % 256, (*i * 7) % 256));
	}
	return (0);
}

void	compute_fractal(t_data *data, int min_x, int max_x)
{
	int		x;
	int		y;
	complex	z;
	int		in_mb;

	x = min_x;
	while (x < max_x)
	{
		y = 0;
		while (y < 1000)
		{
			z = (x + data->x) / data->scale + (y + data->y) / data->scale * I;
			if (data->type.type == MANDELBROT)
				in_mb = get_point(z, data->type.power, &data->fractal, x, y);
			else
				in_mb = get_point(data->type.c, 2, &data->fractal, x, y);
			data->img.data[y * 1600 + x] = in_mb;
			y++;
		}
		x++;
	}
}

void	reset_fractal(t_data *data)
{
	int	x;
	int	y;

	data->fractal.iteration = 50;
	ft_bzero(data->fractal.iterations, 1600 * 1000 * sizeof(int));
	x = 0;
	while (x < 1600)
	{
		y = 0;
		while (y < 1000)
		{
			data->fractal.z[y * 1600 + x] = (x + data->x) / data->scale
				+ (y + data->y) / data->scale * I;
			y++;
		}
		x++;
	}
}
