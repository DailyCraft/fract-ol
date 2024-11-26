/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:59:56 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/26 15:25:34 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	init_type(t_data *data, int argc, char **argv)
{
	if ((argc == 2 || argc == 3) && (ft_strcmp(argv[1], "mandelbrot") == 0
			|| ft_strcmp(argv[1], "mb") == 0))
	{
		data->type.type = MANDELBROT;
		if (argc == 3)
			data->type.power = ft_atof(argv[2]);
		else
			data->type.power = 2;
	}
	else if (argc == 4 && (ft_strcmp(argv[1], "julia") == 0
			|| ft_strcmp(argv[1], "j") == 0))
	{
		data->type.type = JULIA;
		data->type.c = ft_atof(argv[2]) + ft_atof(argv[3]) * I;
	}
	else
	{
		ft_printf("%s mandelbrot|mb [power]\n", argv[0]);
		ft_printf("%s julia|j {R(c)} {Im(c)}\n", argv[0]);
		return (0);
	}
	return (1);
}

static void	init_hooks(t_data *data)
{
	mlx_hook(data->window, DestroyNotify, KeyReleaseMask,
		mlx_loop_end, data->mlx);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_hook, data);
	mlx_expose_hook(data->window, expose_hook, data);
	mlx_mouse_hook(data->window, mouse_hook, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
}

static int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fract-ol");
	data->img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.data = (int *) mlx_get_data_addr(data->img.ptr,
			&data->img.bits_per_pixel, &data->img.size_line, &data->img.endian);
	init_hooks(data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->scale = 500;
	data->x = WIDTH / -2.0;
	data->y = HEIGHT / -2.0;
	data->debug_enabled = 0;
	reset_fractal(data);
	if (init_type(data, argc, argv)
		&& init_mlx(data))
	{
	}
	free(data);
}
