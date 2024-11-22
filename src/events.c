/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:20:26 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/22 10:22:02 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int key, t_vars *vars)
{
	if (key == XK_Escape)
		return (close_window(vars));
	return (0);
}

int	close_window(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}
