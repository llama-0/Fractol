#include "fractol.h"

static int	draw(t_fract *fr, double x)
{
	t_complex	z;
	int			iter;

	fr->c.re = fr->min.re + x * fr->coef.re;
	z = init_nbr(fr->c.re, fr->c.im);
	iter = 0;
	while (z.re * z.re + z.im * z.im <= 4 && iter < fr->max_iter)
	{
		z = fractal_formula(fr, z);
		iter++;
	}
	return (iter);
}

void		draw_fractal(t_fract *fr)
{
	double	x;
	double	y;

	y = 0;
	while (y < DH)
	{
		fr->c.im = fr->max.im - y * fr->coef.im;
		x = 0;
		while (x < DW)
		{
			if (fr->type == N_1 || fr->type == N_2 ||
				fr->type == N_3 || fr->type == N_4 || fr->type == N_5)
			{
				draw_newton_fractal(fr, x, y);
			}
			else
			{
				fr->iter = draw(fr, x);
				(fr->win.img_arr)[(int)(x + y * DW)] = color(fr);
			}
			x++;
		}
		y++;
	}
}
