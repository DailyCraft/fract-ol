/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:57:51 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/26 11:14:20 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_data *data, double factor, int mouse_x, int mouse_y)
{
	int	old[WINDOW_WIDTH * WINDOW_HEIGHT];
	int	x;
	int	y;
	int	old_x;
	int	old_y;

	ft_memcpy(old, data->img.data, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (x < old_x)
				old_x = x + (abs(x - mouse_x) - abs(x - mouse_x) / factor);
			else
				old_x = x - (abs(x - mouse_x) - abs(x - mouse_x) / factor);
			if (y < old_y)
				old_y = y + (abs(y - mouse_y) - abs(y - mouse_y) / factor);
			else
				old_y = y - (abs(y - mouse_y) - abs(y - mouse_y) / factor);
			data->img.data[y * WINDOW_WIDTH + x] = old[old_y * WINDOW_WIDTH + old_x];
			x++;
		}
		y++;
	}
}
