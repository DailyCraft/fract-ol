/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:04:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/22 11:52:10 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define XK_MISCELLANY

# include <math.h>
# include <libft.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysymdef.h>
# include <stdio.h>
# include <string.h>

typedef struct s_vars
{
	void	*mlx;
	void	*window;
	enum
	{
		MANDELBROT,
		JULIA
	}	type;
}	t_vars;

typedef	struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;


int	key_hook(int key, t_vars *vars);
int	close_window(t_vars *vars);
int	is_in_mb(double real, double imaginary);

#endif