/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:04:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/26 11:20:00 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 1000

# define XK_MISCELLANY
# define XK_LATIN1

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
	long double complex	c;
}	t_type;

typedef struct s_fractal
{
	long double complex	z[WINDOW_WIDTH * WINDOW_HEIGHT];
	int					iterations[WINDOW_WIDTH * WINDOW_HEIGHT];
	int					iteration;
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
	void			*mlx;
	void			*window;
	int				debug_enabled;
	t_type			type;
	long double		scale;
	double			x;
	double			y;
	t_fractal		fractal;
	t_image			img;
}	t_data;

int		key_hook(int key, t_data *vars);
int		expose_hook(t_data *vars);
int		mouse_hook(int button, int x, int y, t_data *vars);
int		loop_hook(t_data *data);

int		get_point(long double complex c, double pow, t_data *data, int x, int y);
void	compute_fractal(t_data *data, int min_x, int max_x);
void	reset_fractal(t_data *data);

void	zoom_in(t_data *data, double factor, int mouse_x, int mouse_y);

#endif