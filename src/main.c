/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:59:56 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/22 12:11:25 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	init_type(t_vars *vars, int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("%s {mandelbrot/julia}\n", argv[0]);
		ft_printf("%s {mb/j}\n", argv[0]);
		return (0);
	}
	if (ft_strcmp(argv[1], "mandelbrot") == 0 || ft_strcmp(argv[1], "mb") == 0)
		vars->type = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0 || ft_strcmp(argv[1], "j") == 0)
		vars->type = JULIA;
	else
	{
		ft_printf("%s {mandelbrot/julia}\n", argv[0]);
		ft_printf("%s {mb/j}\n", argv[0]);
		return (0);
	}
	return (1);
}

static int	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->window = mlx_new_window(vars->mlx, 1600, 1000, "fract-ol");
	mlx_hook(vars->window, DestroyNotify, KeyReleaseMask, close_window, vars);
	mlx_key_hook(vars->window, key_hook, vars);

	for (int x = 0; x < 1600; x++)
	{
		for (int y = 0; y < 1000; y++)
		{
			if (is_in_mb((x - 800) / 500.0, (y - 500) / 500.0))
				mlx_pixel_put(vars->mlx, vars->window, x, y, 0);
			else
				mlx_pixel_put(vars->mlx, vars->window, x, y, 0xffffff);
		}
	}
	
	mlx_loop(vars->mlx);
	mlx_destroy_window(vars->mlx, vars->window);
	free(vars->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (init_type(vars, argc, argv)
		&& init_mlx(vars))
	{
	}
	free(vars);
}
