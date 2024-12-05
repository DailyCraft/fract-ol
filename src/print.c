/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:18:02 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/05 16:24:07 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_welcome(char *prog)
{
	ft_printf("\e[1;32mWelcome to the dvan-hum's fract-ol project!\e[0m\n\n");
	ft_printf("\e[1mMandelbrot set:    \e[0;36m%s mb [power]\e[0m\n", prog);
	ft_printf("\e[1mJulia Sets:        ");
	ft_printf("\e[0;36m%s j {Re(c)} {Im(c)}\e[0m\n", prog);
	ft_printf("\e[1mBurning Ship Sets: ");
	ft_printf("\e[0;36m%s bs [{Re(c)} {Im(c)}]\e[0m\n\n", prog);
	ft_printf("\e[1;33mCommands:\e[0m\n");
	ft_printf("\e[34mMouse scroll:\e[0m zoom in / zoom out\n");
	ft_printf("\e[34mArrow keys:\e[0m move the view\n");
	ft_printf("\e[34mC key:\e[0m change colors\n");
	ft_printf("\e[34mR key:\e[0m reset scale and position\n");
	ft_printf("\e[34mD key:\e[0m show debug info\n");
}

void	print_julia_help(char *prog)
{
	ft_printf("\n\t\e[1;32mJulia Sets\e[0m\n\n");
	ft_printf("\e[36m%s j {Re(c)} {Im(c)}\e[0m\n\n", prog);
	ft_printf("\e[1;33m---------- Suggested values for c ");
	ft_printf("----------\e[0m\n");
	ft_printf("%19s | %13s | %13s\n%19s | %13s | %13s\n%19s | %13s | %13s\n",
		"-0.70176 + 0.3842i", "0.285 + 0.01i", "0 + 0.8i",
		"-0.7269 + 0.1889i", "-0.8 + 0.156i", "-0.4 + 0.6i",
		"-0.835 + 0.2321i", "0.35 + 0.35i", "0.4 + 0.4i");
	ft_printf("%19s | %13s | %13s\n%19s | %13s | %13s\n",
		"-0.101 + 0.956i", "-0.76 + 0.12i", "-1.310 + 0i",
		"-0.74543 + 0.11301i", "-0.75 + 0.11i", "-0.1 + 0.651i");
	ft_printf("\n\033[1mThe Basilica:\033[0m  -1 + 0i\n");
	ft_printf("\033[1mDouady Rabbit:\033[0m -0.122 + 0.744i\n");
	ft_printf("\033[1mThe Airplane:\033[0m  -1.7548 + 0i\n");
}

void	print_burning_ship_help(char *prog)
{
	ft_printf("\n\t\e[1;32mBurning Ship Sets\e[0m\n\n");
	ft_printf("\e[36m%s bs [{Re(c)} {Im(c)}]\e[0m\n\n", prog);
	ft_printf("If no c values are provided, the default Burning Ship\n");
	ft_printf("set will be used.\n\n");
	ft_printf("\e[1;33m-------------- Suggested values for c ");
	ft_printf("--------------\e[0m\n");
	ft_printf("%15s | %10s | %13s | %12s\n%15s | %10s | %13s | %12s\n",
		"-1.764 - 0.06i", "0 + 0.297i", "0.425 + 0.25i", "0.87 - 1.52i",
		"-0.75 - 0.09i", "-1 - 1i", "0.675 - 1.15i", "-0.8 + 0.1i");
	ft_printf("%15s | %10s | %13s | %12s\n",
		"0.975 - 1.175i", "0 - 1i", "0.29 - 0.29i", "-1.15 - 0.4i");
}
