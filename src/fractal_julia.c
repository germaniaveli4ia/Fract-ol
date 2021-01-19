/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:46:58 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/09 02:42:33 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		julia(t_mlx *mlx, t_complex c)
{
	int			iter;
	t_complex	z;

	iter = 0;
	z = init_complex(c.re, c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 \
		&& iter < mlx->f.max_iter)
	{
		z = complex_power(z, mlx->power);
		z = complex_sum(z, mlx->f.k);
		iter++;
	}
	return (iter);
}
