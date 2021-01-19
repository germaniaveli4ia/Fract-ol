/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_i_see_you.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:46:58 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/10 00:01:37 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		i_see_you(t_mlx *mlx, t_complex c)
{
	int			iter;
	t_complex	z;
	t_complex	y;

	iter = 0;
	z = init_complex(c.re, c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 \
		&& iter < mlx->f.max_iter)
	{
		y = complex_sin(z);
		z.re *= -2.8;
		z.im *= 2.5;
		z = complex_multiply(y, z);
		z = complex_tg(z);
		z = complex_power(z, mlx->power);
		iter++;
	}
	if (iter >= mlx->f.max_iter && !mlx->nonblack)
		return (-1);
	return (iter);
}
