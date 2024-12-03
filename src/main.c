/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:59:56 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/29 11:31:34 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	init_type(t_data *data, int argc, char **argv)
{
	if ((argc == 2 || argc == 3) && (ft_strcmp(argv[1], "mandelbrot") == 0
			|| ft_strcmp(argv[1], "mb") == 0))
	{
		data->fractal.type = MANDELBROT;
		if (argc == 3)
			data->fractal.power = ft_atof(argv[2]);
		else
			data->fractal.power = 2;
	}
	else if (argc == 4 && (ft_strcmp(argv[1], "julia") == 0
			|| ft_strcmp(argv[1], "j") == 0))
	{
		data->fractal.type = JULIA;
		data->fractal.c = ft_atof(argv[2]) + ft_atof(argv[3]) * I;
	}
	else
	{
		ft_printf("%s mandelbrot|mb [power]\n", argv[0]);
		ft_printf("%s julia|j {R(c)} {Im(c)}\n", argv[0]);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->scale = 350;
	data->x = WIDTH / -2.0;
	data->y = HEIGHT / -2.0;
	data->debug_enabled = 0;
	data->color_index = 0;
	data->centered_update_x = WIDTH / 2;
	data->centered_update_y = HEIGHT / 2;
	data->rect_update_min_x = 0;
	data->rect_update_min_y = 0;
	data->rect_update_max_x = 0;
	data->rect_update_max_y = 0;
	reset_fractal(data);
	if (init_type(data, argc, argv)
		&& init_mlx(data))
	{
	}
	free(data);
}
