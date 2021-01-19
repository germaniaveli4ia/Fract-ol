/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:50:22 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/09 15:22:29 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_color_palette2(int type, int palette[6])
{
	const int		smoke[6] = {BLACK, WHITE, DARK_GREY, DARK_GREY, BLACK, \
	WHITE};
	const int		i_see_you[6] = {YELLOW, BLUE, YELLOW, YELLOW, BLUE, YELLOW};

	if (type == 4)
		ft_memcpy(palette, smoke, sizeof(int) * 6);
	else if (type == 5)
		ft_memcpy(palette, smoke, sizeof(int) * 6);
	else if (type == 6)
		ft_memcpy(palette, i_see_you, sizeof(int) * 6);
}

void	set_color_palette(int type, int palette[6])
{
	const int		mandelbrot[6] = {CHARCOAL, PERSIAN_G, PALE_SEPIA, \
	DEEP_ORANGE, BURNT_SIENNA, ROSSO_CORSA};
	const int		julia[6] = {LIGHT_PINK, CHAMPAGNE, LEMON, TEA, \
	CELESTE, BABY_BLUE};
	const int		occult[6] = {GRAY, LIGHT_GRAY, VIOLET, LILAC, PINK, BORDO};
	const int		dream_catcher[6] = {GUNMETAL, BOG, CYAN, PURPLE, CYAN, \
	LIGHT};

	if (!type)
		ft_memcpy(palette, mandelbrot, sizeof(int) * 6);
	else if (type == 1)
		ft_memcpy(palette, julia, sizeof(int) * 6);
	else if (type == 2)
		ft_memcpy(palette, occult, sizeof(int) * 6);
	else if (type == 3)
		ft_memcpy(palette, dream_catcher, sizeof(int) * 6);
	else
		set_color_palette2(type, palette);
}

int		get_rgb(int strt, int end, float saturation)
{
	return ((int)((1 - saturation) * strt + saturation * end));
}

int		get_gradient(int strt, int end, double saturation)
{
	int		red;
	int		green;
	int		blue;

	if (strt == end)
		return (strt);
	red = get_rgb((strt >> 16) & 0xFF, (end >> 16) & 0xFF,
	saturation);
	green = get_rgb((strt >> 8) & 0xFF, (end >> 8) & 0xFF,
	saturation);
	blue = get_rgb(strt & 0xFF, end & 0xFF, saturation);
	return ((red << 16) | (green << 8) | blue);
}

int		get_color(double iter, t_mlx *mlx)
{
	int			palette[6];
	double		delta;

	delta = (double)mlx->f.max_iter / 6;
	if (iter < 0)
		return (-1);
	else
	{
		set_color_palette(mlx->f.colors, palette);
		if (iter < delta)
			return (get_gradient(palette[0], palette[1], iter / delta));
		else if (iter < delta * 2)
			return (get_gradient(palette[1], palette[2], \
			(iter - delta) / delta));
		else if (iter < delta * 3)
			return (get_gradient(palette[2], palette[3], \
			(iter - 2 * delta) / delta));
		else if (iter < delta * 4)
			return (get_gradient(palette[3], palette[4], \
			(iter - 3 * delta) / delta));
		else
			return (get_gradient(palette[4], palette[5], \
			(iter - 4 * delta) / delta));
	}
	return (-1);
}
