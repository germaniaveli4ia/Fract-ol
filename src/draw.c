/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 22:15:51 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/10 10:49:26 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_mlx *filler, int x, int y, int color)
{
	int		i;

	i = x * filler->bits_per_pixel / 8 + y * filler->size_line;
	filler->data_addr[i] = color;
	filler->data_addr[++i] = color >> 8;
	filler->data_addr[++i] = color >> 16;
	filler->data_addr[++i] = 0;
}

void	menu2(t_point i, t_mlx *p)
{
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
	"Mandelbar: A");
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
	"Julia: J");
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
	"Burning Ship: B");
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 30, FONT, \
	"Occult: O");
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
	"Dream catcher: D");
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
	"I see you: I");
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
	"Motion: K");
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
	"Reset: Space");
	mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
	"Exit: Esc");
}

void	draw_menu(t_mlx *p)
{
	t_point	i;

	if (!p->is_menu)
	{
		i.y = HEIGHT / 2 - 200;
		i.x = WIDTH / 2 - 75;
		mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y, FONT, "Zoom: Scroll");
		mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 30, FONT, \
		"Move: Arrows");
		mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 30, FONT,\
		"Iterations: +/-");
		mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 30, FONT, \
		"Color: 1-7");
		mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 30, FONT, \
		"Power: [ / ]");
		mlx_string_put(p->mlx_ptr, p->win_ptr, i.x, i.y += 25, FONT, \
		"Mandelbrot: M");
		menu2(i, p);
		p->is_menu = 1;
	}
	else
	{
		p->is_menu = 0;
		expose_hook((void *)p);
	}
}

void	draw(void *data)
{
	t_thread	*t;
	t_point		i;
	int			color;
	t_complex	c;

	t = (t_thread *)data;
	t->mlx->f.diametr = t->mlx->f.max.re - t->mlx->f.min.re;
	t->mlx->f.factor.re = t->mlx->f.diametr / WIDTH;
	t->mlx->f.factor.im = t->mlx->f.diametr / HEIGHT;
	i.y = t->start;
	while (i.y < t->finish)
	{
		c.im = t->mlx->f.max.im - i.y * t->mlx->f.factor.im;
		i.x = 0;
		while (i.x < WIDTH)
		{
			c.re = t->mlx->f.min.re + i.x * t->mlx->f.factor.re;
			color = get_color(t->mlx->formula[t->mlx->type](t->mlx, c), t->mlx);
			if (color >= 0)
				put_pixel(t->mlx, i.x, i.y, color);
			i.x++;
		}
		i.y++;
	}
}

void	clear_image(t_mlx *data)
{
	ft_bzero(data->data_addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
}
