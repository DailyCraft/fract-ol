/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:12:34 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/22 12:21:28 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_in_mb(double real, double imaginary)
{
	double	zn_real;
	double	zn_imaginary;
	int	i;
	double	temp;
	double	last_mod;
	double	current_mod;
	
	zn_real = real;
	zn_imaginary = imaginary;
	last_mod = -1;
	current_mod = sqrt(real * real + imaginary * imaginary);	
	i = 0;
	while (i < 1000)
	{
		temp = zn_real;
		zn_real = zn_real * zn_real - zn_imaginary * zn_imaginary + real;
		zn_imaginary = temp * zn_imaginary + temp * zn_imaginary + imaginary;
		i++;
		last_mod = current_mod;
		current_mod = sqrt(zn_real * zn_real + zn_imaginary * zn_imaginary);
	}
	if (last_mod - current_mod > -1000000 && last_mod - current_mod < 1000000)
		return (1);
	return (0);
}
