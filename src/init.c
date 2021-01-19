/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:31:44 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/09 23:58:56 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_image(t_mlx *mlx)
{
	mlx->is_menu = 0;
	mlx->bits_per_pixel /= 8;
	if (!(mlx->mlx_ptr = mlx_init()))
	{
		ft_putendl("Failed to create mlx pointer");
		return (0);
	}
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, \
	"Fractol by wmarya")))
	{
		ft_putendl("Failed to create new window");
		return (0);
	}
	if (!(mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT)))
	{
		ft_putendl("Failed to create new image");
		return (0);
	}
	if (!(mlx->data_addr = mlx_get_data_addr(mlx->img, \
	&(mlx->bits_per_pixel), &(mlx->size_line), &(mlx->endian))))
	{
		ft_putendl("Failed to get data address");
		return (0);
	}
	return (1);
}

void		init_fractal(t_mlx *mlx)
{
	mlx->f.min = init_complex(-2.0, -2.0);
	mlx->f.max.re = 2.0;
	mlx->f.diametr = mlx->f.max.re - mlx->f.min.re;
	mlx->f.max.im = mlx->f.min.im + mlx->f.diametr;
	mlx->f.factor.re = mlx->f.diametr / WIDTH;
	mlx->f.factor.im = mlx->f.diametr / HEIGHT;
	mlx->f.max_iter = mlx->type == 2 ? 90 : 40;
	mlx->f.is_motion = 0;
	mlx->f.zoom = 1.0;
	mlx->f.k = init_complex(-0.55, -0.55);
	mlx->formula[0] = &mandelbrot;
	mlx->formula[1] = &julia;
	mlx->formula[2] = &occult;
	mlx->formula[3] = &dream_catcher;
	mlx->formula[4] = &mandelbar;
	mlx->formula[5] = &burning_ship;
	mlx->formula[6] = &i_see_you;
	mlx->f.colors = mlx->type;
	mlx->power = 2;
	mlx->nonblack = 0;
	expose_hook((void *)mlx);
}

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}
