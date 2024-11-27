/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:04:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/27 16:28:26 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1000
# define HEIGHT 1000

# define XK_MISCELLANY
# define XK_LATIN1

# include <math.h>
# include <complex.h>
# include <libft.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysymdef.h>
//# include <stdio.h>
//# include <string.h>

typedef long double complex	t_lcomplex;

enum e_type
{
	MANDELBROT,
	JULIA
};

typedef struct s_point
{
	t_lcomplex	z;
	int			iteration;
}	t_point;


typedef struct s_fractal
{
	enum e_type	type;
	double		power;
	t_lcomplex	c;
	t_point		points[WIDTH * HEIGHT];
	int			iteration;
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
	int			debug_enabled;
	int			color_index;
	long double	scale;
	double		x;
	double		y;
	t_fractal	fractal;
	t_image		img;
}	t_data;

int		key_hook(int key, t_data *vars);
int		expose_hook(t_data *vars);
int		mouse_hook(int button, int x, int y, t_data *vars);
int		loop_hook(t_data *data);

void	get_point(t_lcomplex c, double pow, t_data *data, complex pos);
void	compute_fractal(t_data *data, int min_x, int max_x);
void	reset_point(t_data *data, int x, int y);
void	reset_fractal(t_data *data);

void	zoom(t_data *data, double factor, int mouse_x, int mouse_y);
void	move(t_data *data, int horizontal, int vertical);
int		smooth_rgb(double value);
void	draw_pixels(t_data *data, int min_x, int max_x);

int		init_mlx(t_data *data);
int		mlx_refresh_image(t_data *data);
void	mlx_set_pixel(t_data *data, int x, int y, int color);

#endif