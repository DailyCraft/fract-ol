/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:37:46 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/27 16:07:09 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_hooks(t_data *data)
{
	mlx_hook(data->window, DestroyNotify, KeyReleaseMask,
		mlx_loop_end, data->mlx);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_hook, data);
	mlx_expose_hook(data->window, expose_hook, data);
	mlx_mouse_hook(data->window, mouse_hook, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
}

int	init_mlx(t_data *data)
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

int	mlx_refresh_image(t_data *data)
{
	return (mlx_put_image_to_window(data->mlx, data->window,
			data->img.ptr, 0, 0));
}

void	mlx_set_pixel(t_data *data, int x, int y, int color)
{
	data->img.data[(HEIGHT - 1 - y) * WIDTH + x] = color;
}
