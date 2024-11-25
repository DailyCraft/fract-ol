/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:57:51 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/25 15:33:09 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_data *data, double factor, int mouse_x, int mouse_y)
{
	int	old[1600 * 1000];
	int	x;
	int	y;
	int	old_x;
	int	old_y;

	ft_memcpy(old, data->img.data, 1600 * 1000 * sizeof(int));
	y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1600)
		{
			if (x < old_x)
				old_x = x + (abs(x - mouse_x) - abs(x - mouse_x) / factor);
			else
				old_x = x - (abs(x - mouse_x) - abs(x - mouse_x) / factor);
			if (y < old_y)
				old_y = y + (abs(y - mouse_y) - abs(y - mouse_y) / factor);
			else
				old_y = y - (abs(y - mouse_y) - abs(y - mouse_y) / factor);
			data->img.data[y * 1600 + x] = old[old_y * 1600 + old_x];
			x++;
		}
		y++;
	}
}
