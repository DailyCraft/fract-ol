/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:59:56 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/04 16:15:18 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_julia_suggestions(void)
{
	ft_printf("\n---------------------------------------------------\n");
	ft_printf("\033[1;33mDifferent values for c for the Julia set:\033[0m\n");
	ft_printf("%19s | %13s | %13s\n%19s | %13s | %13s\n%19s | %13s | %13s\n",
		"-0.70176 + 0.3842i", "0.285 + 0.01i", "0 + 0.8i",
		"-0.7269 + 0.1889i", "-0.8 + 0.156i", "-0.4 + 0.6i",
		"-0.835 + 0.2321i", "0.35 + 0.35i", "0.4 + 0.4i");
	ft_printf("%19s | %13s | %13s\n%19s | %13s | %13s\n",
		"-0.101 + 0.956i", "-0.76 + 0.12i", "-1.310 + 0i",
		"-0.74543 + 0.11301i", "-0.75 + 0.11i", "-0.1 + 0.651i");
	ft_printf("\n\033[1mThe basilica:\033[0m  -1 + 0i\n");
	ft_printf("\033[1mDouady rabbit:\033[0m -0.122 + 0.744i\n");
	ft_printf("\033[1mThe airplane:\033[0m  -1.7548 + 0i\n");
}

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
		ft_printf("\033[1;31mInvalid arguments!\033[0m\n");
		ft_printf("\033[36m%s mandelbrot|mb [power]\n", argv[0]);
		ft_printf("%s julia|j {R(c)} {Im(c)}\033[0m\n", argv[0]);
		print_julia_suggestions();
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	reset_view(data);
	data->debug_enabled = 0;
	data->color_index = 7;
	data->rect_update_min_x = 0;
	data->rect_update_min_y = 0;
	data->rect_update_max_x = 0;
	data->rect_update_max_y = 0;
	if (init_type(data, argc, argv)
		&& init_mlx(data))
	{
	}
	free(data);
}
