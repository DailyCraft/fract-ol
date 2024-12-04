/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:48:17 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/04 14:48:53 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_update_rect_x(t_data *data, int min_x, int max_x)
{
	data->rect_update_min_x = ft_max(data->rect_update_min_x, ft_max(0, min_x));
	data->rect_update_max_x = ft_min(data->rect_update_max_x,
			ft_min(WIDTH, max_x));
}

void	set_update_rect_y(t_data *data, int min_y, int max_y)
{
	data->rect_update_min_y = ft_max(data->rect_update_min_y, ft_max(0, min_y));
	data->rect_update_max_y = ft_min(data->rect_update_max_y,
			ft_min(HEIGHT, max_y));
}
