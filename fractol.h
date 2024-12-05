/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:04:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/05 15:48:19 by dvan-hum         ###   ########.fr       */
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
	int			is_burning_ship;
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

	int			centered_update_x;
	int			centered_update_y;
	int			rect_update_min_x;
	int			rect_update_min_y;
	int			rect_update_max_x;
	int			rect_update_max_y;
}	t_data;

int		key_hook(int key, t_data *vars);
int		expose_hook(t_data *vars);
int		mouse_hook(int button, int x, int y, t_data *vars);
int		loop_hook(t_data *data);

int		get_point(t_lcomplex c, double pow, t_data *data, int pos);
void	update_point(t_data *data, int x, int y);
void	reset_point(t_data *data, int x, int y);
void	reset_fractal(t_data *data);

int		init_mlx(t_data *data);
int		mlx_refresh_image(t_data *data);
void	mlx_set_pixel(t_data *data, int x, int y, int color);

void	zoom(t_data *data, double factor, int mouse_x, int mouse_y);
void	move(t_data *data, int horizontal, int vertical);

void	print_welcome(char *prog);
void	print_julia_help(char *prog);
void	print_burning_ship_help(char *prog);

void	reset_view(t_data *data);
int		get_color(t_data *data, int x, int y);
void	draw_pixels(t_data *data, int min_x, int max_x);
void	render_debugs(t_data *data);

int		update_default(t_data *data);
int		update_centered(t_data *data);
int		update_rect(t_data *data);
void	set_update_rect_x(t_data *data, int min_x, int max_x);
void	set_update_rect_y(t_data *data, int min_y, int max_y);

#endif