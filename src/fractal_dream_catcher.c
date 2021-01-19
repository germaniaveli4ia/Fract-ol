/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_dream_catcher.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:46:58 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/10 00:01:25 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		dream_catcher(t_mlx *mlx, t_complex c)
{
	int			iter;
	t_complex	z;
	t_complex	y;

	iter = 0;
	z = init_complex(c.re, c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 \
		&& iter < mlx->f.max_iter)
	{
		z = complex_power(z, mlx->power);
		y = complex_sin(z);
		z = complex_tg(z);
		z = complex_division(z, y);
		z = complex_minus(z, mlx->f.k);
		iter++;
	}
	if (iter >= mlx->f.max_iter && !mlx->nonblack)
		return (-1);
	return (iter);
}
