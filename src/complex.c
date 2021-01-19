/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 21:27:07 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/09 14:58:10 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	complex_sum(t_complex a, t_complex b)
{
	t_complex	c;

	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return (c);
}

t_complex	complex_minus(t_complex a, t_complex b)
{
	t_complex	c;

	c.re = a.re - b.re;
	c.im = a.im - b.im;
	return (c);
}

t_complex	complex_sin(t_complex c)
{
	t_complex	res;

	res.re = sin(c.re) * cosh(c.im);
	res.im = cos(c.re) * sinh(c.im);
	return (res);
}

t_complex	complex_cos(t_complex c)
{
	t_complex	res;

	res.re = cos(c.re) * cosh(c.im);
	res.im = -sin(c.re) * sinh(c.im);
	return (res);
}

t_complex	complex_tg(t_complex c)
{
	t_complex	res;

	res = complex_division(complex_sin(c), complex_cos(c));
	return (res);
}
