/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:47:00 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/10 00:05:11 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(int key, int x, int y, t_mlx *p)
{
	t_complex	c;
	double		offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	c.im = (double)y / (HEIGHT / (p->f.max.im - p->f.min.im)) \
	* -1 + p->f.max.im;
	c.re = (double)x / (WIDTH / (p->f.max.re - p->f.min.re)) + p->f.min.re;
	if (key == SCROLL_UP)
	{
		p->f.zoom = 0.8;
		//the next line significantly slows down heavy fractals
		//p->f.max_iter > MIN_ITER ? p->f.max_iter -= 5 : 0;
	}
	else if (key == SCROLL_DOWN)
	{
		p->f.zoom = 1.2;
		//the next line significantly slows down heavy fractals
		//p->f.max_iter < MAX_ITER ? p->f.max_iter += 5 : 0;
	}
	offset = 1.0 / p->f.zoom;
	p->f.min.re = c.re + ((p->f.min.re - c.re) * offset);
	p->f.max.re = c.re + ((p->f.max.re - c.re) * offset);
	p->f.min.im = c.im + ((p->f.min.im - c.im) * offset);
	p->f.max.im = c.im + ((p->f.max.im - c.im) * offset);
	p->f.diametr *= offset;
	expose_hook((void *)p);
}

void	move(int key, t_mlx *p)
{
	if (key == LEFT)
	{
		p->f.min.re -= 0.015 * p->f.diametr;
		p->f.max.re -= 0.015 * p->f.diametr;
	}
	else if (key == RIGHT)
	{
		p->f.min.re += 0.015 * p->f.diametr;
		p->f.max.re += 0.015 * p->f.diametr;
	}
	else if (key == UP)
	{
		p->f.min.im += 0.015 * p->f.diametr;
		p->f.max.im += 0.015 * p->f.diametr;
	}
	else if (key == DOWN)
	{
		p->f.min.im -= 0.015 * p->f.diametr;
		p->f.max.im -= 0.015 * p->f.diametr;
	}
	expose_hook(p);
}

int		change_colors(int key, t_mlx *p)
{
	if (key == ONE)
		p->f.colors = 0;
	else if (key == TWO)
		p->f.colors = 1;
	else if (key == THREE)
		p->f.colors = 2;
	else if (key == FOUR)
		p->f.colors = 3;
	else if (key == FIVE)
		p->f.colors = 4;
	else if (key == SIX)
		p->nonblack = (p->nonblack == 1) ? 0 : 1;
	else if (key == SEVEN)
		p->f.colors = 6;
	expose_hook(p);
	return (0);
}

int		change_power(int key, t_mlx *p)
{
	if (key == R_SKOBKA && p->power < 7)
		p->power++;
	else if (key == L_SKOBKA && p->power > 2)
		p->power--;
	expose_hook(p);
	return (0);
}

int		change_iteration(int key, t_mlx *p)
{
	char	*str;

	str = NULL;
	if (key == PLUS && p->f.max_iter < MAX_ITER)
		p->f.max_iter += 10;
	else if (key == MINUS && p->f.max_iter > MIN_ITER)
		p->f.max_iter -= 10;
	expose_hook(p);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 5, 5, 0xffffff, \
	"Current iterations:");
	str = ft_itoa(p->f.max_iter);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 5, 20, 0xffffff, str);
	ft_strdel(&str);
	return (0);
}
