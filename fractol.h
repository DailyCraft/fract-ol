/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:04:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/25 15:29:05 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define XK_MISCELLANY

# include <math.h>
# include <complex.h>
# include <libft.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysymdef.h>
# include <stdio.h>
# include <string.h>

enum e_type
{
	MANDELBROT,
	JULIA
};

typedef struct s_type
{
	int		type;
	double	power;
	complex	c;
}	t_type;

typedef struct s_fractal
{
	complex	z[1600 * 1000];
	int		iterations[1600 * 1000];
	int		iteration;
}	t_fractal;

typedef struct s_image
{
	void	*ptr;
	int		*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_type		type;
	double		scale;
	double		x;
	double		y;
	t_fractal	fractal;
	t_image		img;
}	t_data;

typedef struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;

int		key_hook(int key, t_data *vars);
int		expose_hook(t_data *vars);
int		mouse_hook(int button, int x, int y, t_data *vars);
int		loop_hook(t_data *data);

int		get_point(complex c, double pow, t_fractal *fractal, int x, int y);
void	compute_fractal(t_data *data, int min_x, int max_x);
void	reset_fractal(t_data *data);

void	zoom_in(t_data *data, double factor, int mouse_x, int mouse_y);

#endif