/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:58:11 by alkapolly         #+#    #+#             */
/*   Updated: 2020/12/10 00:30:56 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "../minilibx_macos/includes/mlx.h"
# include <stdlib.h>
# include <math.h>
# include "keybord.h"
# include "colors.h"
# include <pthread.h>

# define WIDTH 500
# define HEIGHT 500
# define THREADS 8
# define MAX_ITER 1000
# define MIN_ITER 20
# define FONT 0xFFFFFF

typedef struct		s_point
{
	int			x;
	int			y;
}					t_point;

typedef struct		s_color
{
	int			r;
	int			g;
	int			b;
}					t_color;

typedef struct		s_complex
{
	double		re;
	double		im;
}					t_complex;

typedef struct		s_fractal
{
	t_complex	min;
	t_complex	max;
	t_complex	factor;
	t_complex	k;
	t_point		i;
	double		zoom;
	int			max_iter;
	int			is_motion;
	double		colors;
	double		diametr;
}					t_fractal;

/*
** main structure containing fractal type, fractal structure and drawing
** variables
*/

typedef struct		s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*data_addr;
	int			bits_per_pixel;
	int			(*formula[7])(struct s_mlx *mlx, t_complex cur);
	int			size_line;
	int			endian;
	int			type;
	int			power;
	int			is_menu;
	int			nonblack;
	t_fractal	f;
}					t_mlx;

/*
** multy-threading support structure
*/
typedef struct		s_thread
{
	t_mlx			*mlx;
	int				start;
	int				finish;
}					t_thread;

int					main(int argc, char **argv);

/*
** init
*/

int					init_image(t_mlx *mlx);
t_complex			init_complex(double re, double im);
void				init_fractal(t_mlx *mlx);
void				init_mandelbrot(t_fractal *fractal, void *mlx);

/*
** mlx hooks
*/

int					expose_hook(t_mlx *mlx);
int					mouse_hook(int key, int x, int y, void *data);
int					key_hook(int key, t_mlx *mlx);
int					moution_hook(int x, int y, void *data);

/*
** transformations
*/

void				zoom(int key, int x, int y, t_mlx *p);
void				move(int key, t_mlx *p);
int					change_colors(int key, t_mlx *p);
int					change_iteration(int key, t_mlx *p);
int					change_power(int key, t_mlx *p);

/*
** free
*/

int					clean_and_exit(t_mlx *filler);

/*
** draw
*/

void				draw(void *data);
void				put_pixel(t_mlx *filler, int x, int y, int color);
void				clear_image(t_mlx *data);
t_color				set_color(double iter, double max_iter);
int					get_color(double iter, t_mlx *mlx);
void				draw_menu(t_mlx *mlx);

/*
** fractals
*/

int					mandelbrot(t_mlx *mlx, t_complex c);
int					occult(t_mlx *mlx, t_complex c);
int					julia(t_mlx *mlx, t_complex c);
int					burning_ship(t_mlx *mlx, t_complex c);
int					mandelbar(t_mlx *mlx, t_complex c);
int					dream_catcher(t_mlx *mlx, t_complex c);
int					i_see_you(t_mlx *mlx, t_complex c);

/*
** complex math utils
*/

t_complex			complex_power(t_complex c, int power);
t_complex			complex_multiply(t_complex a, t_complex b);
t_complex			complex_division(t_complex a, t_complex b);
t_complex			complex_sum(t_complex a, t_complex b);
t_complex			complex_minus(t_complex a, t_complex b);
t_complex			complex_sin(t_complex c);
t_complex			complex_cos(t_complex c);
t_complex			complex_tg(t_complex c);

#endif
