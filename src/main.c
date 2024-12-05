/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:59:56 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/05 15:18:27 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	parse_burning_ship(t_data *data, int argc, char **argv)
{
	data->fractal.is_burning_ship = 1;
	if (argc == 2)
		data->fractal.type = MANDELBROT;
	else if (argc == 4)
	{
		data->fractal.type = JULIA;
		data->fractal.c = ft_atof(argv[2]) + ft_atof(argv[3]) * I;
	}
	else
	{
		print_burning_ship_help(argv[0]);
		return (0);
	}
	return (1);
}

static int	parse_args(t_data *data, int argc, char **argv)
{
	if (argc == 1)
	{
		print_welcome(argv[0]);
		return (0);
	}
	if (ft_strcmp(argv[1], "mb") == 0 && argc <= 3)
	{
		data->fractal.type = MANDELBROT;
		if (argc == 3)
			data->fractal.power = ft_atof(argv[2]);
		return (1);
	}
	if (ft_strcmp(argv[1], "j") == 0 && argc <= 4)
	{
		data->fractal.type = JULIA;
		if (argc == 4)
			data->fractal.c = ft_atof(argv[2]) + ft_atof(argv[3]) * I;
		else
			print_julia_help(argv[0]);
		return (argc == 4);
	}
	else if (ft_strcmp(argv[1], "bs") == 0 && argc <= 4)
		return (parse_burning_ship(data, argc, argv));
	print_welcome(argv[0]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	reset_view(data);
	data->fractal.power = 2;
	data->fractal.is_burning_ship = 0;
	data->debug_enabled = 0;
	data->color_index = 7;
	data->rect_update_min_x = 0;
	data->rect_update_min_y = 0;
	data->rect_update_max_x = 0;
	data->rect_update_max_y = 0;
	if (parse_args(data, argc, argv)
		&& init_mlx(data))
	{
	}
	free(data);
}
