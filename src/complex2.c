/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 21:27:07 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/09 14:57:56 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	complex_multiply(t_complex a, t_complex b)
{
	t_complex	c;

	c.re = a.re * b.re - a.im * b.im;
	c.im = a.re * b.im + a.im * b.re;
	return (c);
}

t_complex	complex_division(t_complex a, t_complex b)
{
	t_complex	c;

	c.re = (a.re * b.re + a.im * b.im) / ((b.re * b.re) + (b.im * b.im));
	c.im = (b.re * a.im - a.re * b.im) / ((b.re * b.re) + (b.im * b.im));
	return (c);
}

t_complex	complex_power(t_complex c, int power)
{
	t_complex	save;
	int			i;

	save = c;
	i = 1;
	while (i++ < power)
		c = complex_multiply(c, save);
	return (c);
}
