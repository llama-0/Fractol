#include "fractol.h"

static int	color_set_one_helper(t_fract *fr, double t)
{
	if (fr->type == 2)
	{
		if (fr->iter % 2 == 0)
			return (MAGENTA);
		else
			return (YELLOW);
	}
	else
	{
		fr->rgb[0] = (int)(8.5 * pow(1 - t, 3) * t * 255);
		fr->rgb[1] = (int)(9 * (1 - t) * pow(t, 3) * 255);
		fr->rgb[2] = (int)(15 * pow(1 - t, 2) * pow(t, 2) * 255);
	}
	return ((fr->rgb[0] << 16) | (fr->rgb[1] << 8) | fr->rgb[2]);
}

/*
** A slightly modified form of the Bernstein polynomials
** for smooth coloring
*/

int			color(t_fract *fr)
{
	double t;

	t = (double)(fr->iter) / (double)(fr->max_iter);
	if (fr->rgb_flag == 0)
	{
		fr->rgb[0] = (int)(9 * (1 - t) * pow(t, 3) * 255);
		fr->rgb[1] = (int)(15 * pow(1 - t, 2) * pow(t, 2) * 255);
		fr->rgb[2] = (int)(8.5 * pow(1 - t, 3) * t * 255);
	}
	else if (fr->rgb_flag == C)
		return (color_set_one_helper(fr, t));
	else if (fr->rgb_flag == V)
	{
		fr->rgb[0] = (int)(15 * pow(1 - t, 2) * pow(t, 2) * 255);
		fr->rgb[1] = (int)(8.5 * pow(1 - t, 3) * t * 255);
		fr->rgb[2] = (int)(9 * (1 - t) * pow(t, 3) * 255);
	}
	return ((fr->rgb[0] << 16) | (fr->rgb[1] << 8) | fr->rgb[2]);
}

void		color_newton_root(t_fract *fr, t_complex z, double x, double y)
{
	t_complex	roots[3];
	double		t;

	roots[0] = init_nbr(1.0, 0.0);
	roots[1] = init_nbr(-0.5, sqrt(3) / 2);
	roots[2] = init_nbr(-0.5, -sqrt(3) / 2);
	t = 0.0001;
	if (abs_complex(subtract(z, roots[0])) < t)
		(fr->win.img_arr)[(int)(x + y * DW)] =
			(((255 - fr->iter * 15) << 16) | (0 << 8) | 0);
	if (abs_complex(subtract(z, roots[1])) <= t)
		(fr->win.img_arr)[(int)(x + y * DW)] =
			((0 << 16) | ((255 - fr->iter * 15) << 8) | 0);
	if (abs_complex(subtract(z, roots[2])) <= t)
		(fr->win.img_arr)[(int)(x + y * DW)] =
			((0 << 16) | (0 << 8) | ((255 - fr->iter * 15) << 0));
}

void		color_newton_converge(t_fract *fr, double x, double y)
{
	double	t;

	t = (double)fr->iter / (double)fr->max_iter;
	if (fr->type == N_5)
		(fr->win.img_arr)[(int)(x + y * DW)] = color(fr);
	else if (fr->type == N_3)
	{
		(fr->win.img_arr)[(int)(x + y * DW)] =
			(((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 16) |
			((int)(15 * (1 - t) * t * t * t * 255) << 8) |
			(int)(5 * (1 - t) * t * t * t * 255));
	}
	else if (fr->type == N_4)
	{
		(fr->win.img_arr)[(int)(x + y * DW)] =
			(((fr->iter % 32 * 332) << 16) |
			((fr->iter % 8 * 64) << 8) |
			(fr->iter % 48 * 7));
	}
	else
		(fr->win.img_arr)[(int)(x + y * DW)] =
			(((fr->iter % 20 * 30) << 16) |
			((fr->iter % 8 * 64) << 8) |
			(fr->iter % 45 * 7));
}
