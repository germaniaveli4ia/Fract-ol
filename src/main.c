/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:50:36 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/09 15:56:18 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fractal(t_mlx *mlx)
{
	mlx_key_hook(mlx->win_ptr, key_hook, (void*)mlx);
	mlx_hook(mlx->win_ptr, 6, 1L << 6, moution_hook, (void*)mlx);
	mlx_mouse_hook(mlx->win_ptr, mouse_hook, (void*)mlx);
	mlx_expose_hook(mlx->win_ptr, expose_hook, (void*)mlx);
	mlx_hook(mlx->win_ptr, 17, 0, clean_and_exit, (void*)mlx);
	mlx_loop(mlx->mlx_ptr);
}

int			set_type(char *name, t_mlx *mlx)
{
	if (!ft_strcmp(name, "Mandelbrot"))
		mlx->type = 0;
	else if (!ft_strcmp(name, "Julia"))
		mlx->type = 1;
	else if (!ft_strcmp(name, "Occult"))
		mlx->type = 2;
	else if (!ft_strcmp(name, "Dream_catcher"))
		mlx->type = 3;
	else if (!ft_strcmp(name, "Mandelbar"))
		mlx->type = 4;
	else if (!ft_strcmp(name, "Burning_ship"))
		mlx->type = 5;
	else if (!ft_strcmp(name, "I_see_you"))
		mlx->type = 6;
	else
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2 || !set_type(argv[1], &mlx))
	{
		ft_putendl("Usage: ./fractol [name]");
		ft_putendl("Availible fractals: Mandelbrot, Julia, Occult,");
		ft_putendl("Dream_catcher, Mandelbar, Burning_ship, I_see_you");
	}
	else if (!init_image(&mlx))
		clean_and_exit(&mlx);
	else
	{
		init_fractal(&mlx);
		fractal(&mlx);
	}
	return (1);
}
