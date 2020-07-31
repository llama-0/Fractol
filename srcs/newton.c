#include "fractol.h"

static void	draw_newton_root(t_fract *fr, double x, double y)
{
	t_complex	roots[3];
	t_complex	z;
	double		t;
	int			iter;

	roots[0] = init_nbr(1.0, 0.0);
	roots[1] = init_nbr(-0.5, sqrt(3) / 2);
	roots[2] = init_nbr(-0.5, -sqrt(3) / 2);
	t = 0.0001;
	fr->c.re = fr->min.re + x * fr->coef.re;
	z = init_nbr(fr->c.re, fr->c.im);
	iter = 0;
	while (iter < fr->max_iter && (abs_complex(subtract(z, roots[0]))) >= t
			&& (abs_complex(subtract(z, roots[1]))) >= t
			&& (abs_complex(subtract(z, roots[2]))) >= t)
	{
		if (abs_complex(z) > 0)
			z = newton_formula(fr, z);
		iter++;
	}
	fr->iter = iter;
	color_newton_root(fr, z, x, y);
}

static void	draw_newton_converge(t_fract *fr, double x, double y)
{
	t_complex	z;
	t_complex	z1;
	t_complex	delta;
	int			iter;

	fr->c.re = fr->min.re + x * fr->coef.re;
	z = init_nbr(fr->c.re, fr->c.im);
	iter = -1;
	delta = z;
	while (++iter < fr->max_iter && abs_complex(z) < 1e+6
								&& abs_complex(delta) > 1e-6)
	{
		z1 = z;
		z = newton_formula(fr, z);
		delta = subtract(z1, z);
	}
	fr->iter = iter;
	color_newton_converge(fr, x, y);
}

void		draw_newton_fractal(t_fract *fr, double x, double y)
{
	if (fr->type == N_1)
		draw_newton_root(fr, x, y);
	else
		draw_newton_converge(fr, x, y);
}
