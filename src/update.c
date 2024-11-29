/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:15:57 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/29 09:27:40 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	update_default(t_data *data)
{
	static int	min_x = 0;
	int			x;
	int			y;

	x = min_x;
	while (x < min_x + WIDTH / 10)
	{
		y = 0;
		while (y < HEIGHT)
		{
			update_point(data, x, y);
			mlx_set_pixel(data, x, y, get_color(data, x, y));
			y++;
		}
		x++;
	}
	min_x += WIDTH / 10;
	if (min_x >= WIDTH)
	{
		data->fractal.iteration += 2;
		min_x = 0;
	}
}
