/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 00:04:14 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/09 15:53:27 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_hook2(int key, t_mlx *p)
{
	if (key == ONE || key == TWO || key == THREE || key == FOUR \
	|| key == FIVE || key == SIX || key == SEVEN)
	{
		change_colors(key, p);
		return ;
	}
	else if (key == M_KEY)
		p->type = 0;
	else if (key == A_KEY)
		p->type = 4;
	else if (key == O_KEY)
		p->type = 2;
	else if (key == D_KEY)
		p->type = 3;
	else if (key == I_KEY)
		p->type = 6;
	else if (key == B_KEY)
		p->type = 5;
	else if (key == J_KEY)
		p->type = 1;
	expose_hook(p);
}

int		key_hook(int key, t_mlx *p)
{
	if (key == 53)
		clean_and_exit(p);
	else if (key == 49)
		init_fractal(p);
	else if ((key == PLUS) || (key == MINUS))
		change_iteration(key, p);
	else if (key == RIGHT || key == LEFT || key == UP || key == DOWN)
		move(key, p);
	else if (key == TAB)
		draw_menu(p);
	else if (key == K)
	{
		p->f.is_motion = (!p->f.is_motion) ? 1 : 0;
		expose_hook(p);
	}
	else if (key == R_SKOBKA || key == L_SKOBKA)
		change_power(key, p);
	else
		key_hook2(key, p);
	return (0);
}

int		mouse_hook(int key, int x, int y, void *data)
{
	t_mlx	*p;

	p = (t_mlx*)data;
	if ((key == SCROLL_UP) || (key == SCROLL_DOWN))
		zoom(key, x, y, p);
	return (1);
}

int		moution_hook(int x, int y, void *data)
{
	t_mlx	*p;

	p = (t_mlx*)data;
	p->f.diametr = p->f.max.re - p->f.min.re;
	if (p->f.is_motion && (p->type == 1 || p->type == 3))
	{
		if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		{
			p->f.k.re = 4 * ((double)x / WIDTH - 0.5);
			p->f.k.im = 4 * ((double)(HEIGHT - y) / HEIGHT - 0.5);
		}
	}
	expose_hook(data);
	return (1);
}

int		expose_hook(t_mlx *p)
{
	t_thread	all_threads[THREADS];
	pthread_t	thread[THREADS];
	int			i;

	i = -1;
	clear_image(p);
	while (++i < THREADS)
	{
		all_threads[i].mlx = p;
		all_threads[i].start = i * (HEIGHT / THREADS);
		all_threads[i].finish = (i + 1) * (HEIGHT / THREADS);
		if (pthread_create(thread + i, NULL, (void *)draw, \
		(void *)(all_threads + i)))
			exit(1);
	}
	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(thread[i], NULL))
			clean_and_exit(p);
		i++;
	}
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img, 0, 0);
	return (1);
}
