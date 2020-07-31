#include "fractol.h"

t_complex			fractal_formula(t_fract *fr, t_complex z)
{
	if (fr->type == 1)
	{
		return (init_nbr(pow(z.re, 2.0) - pow(z.im, 2.0) + fr->c.re,
						2.0 * z.re * z.im + fr->c.im));
	}
	if (fr->type == 2)
	{
		return (init_nbr(pow(z.re, 2.0) - pow(z.im, 2.0) + fr->k.re,
						2.0 * z.re * z.im + fr->k.im));
	}
	if (fr->type == 3)
	{
		return (init_nbr(pow(z.re, 2) - pow(z.im, 2) + fr->c.re,
						-2.0 * fabs(z.re) * fabs(z.im) + fr->c.im));
	}
	return (z);
}

static t_complex	newton_basic_formula(t_complex z)
{
	return (subtract(init_nbr(z.re, z.im), divide(init_nbr(
		pow(z.re, 3) - 3 * z.re * pow(z.im, 2) - 1,
		3 * pow(z.re, 2) * z.im - pow(z.im, 3)),
		init_nbr(3 * pow(z.re, 2) - 3 * pow(z.im, 2), 6 * z.re * z.im))));
}

t_complex			newton_formula(t_fract *fr, t_complex z)
{
	if (fr->type == N_1 || fr->type == N_2)
		return (newton_basic_formula(z));
	if (fr->type == N_3)
	{
		return (subtract(init_nbr(z.re, z.im), divide(init_nbr(
			sin(z.re) * cosh(z.im) - 1,
			cos(z.re) * sinh(z.im)),
			init_nbr(cos(z.re) * cosh(z.im), -sin(z.re) * sinh(z.im)))));
	}
	if (fr->type == N_4)
	{
		return (subtract(init_nbr(z.re, z.im), init_nbr(
			-sinh(2 * z.re) / (cos(2 * z.im) - cosh(2 * z.re)),
			sin(2 * z.im) / (cos(2 * z.im) - cosh(2 * z.re)))));
	}
	if (fr->type == N_5)
	{
		return (subtract(init_nbr(z.re, z.im), divide(multiply(init_nbr(
			pow(z.re, 3) - 3 * z.re * pow(z.im, 2) - 1,
			3 * pow(z.re, 2) * z.im - pow(z.im, 3)), init_nbr(0.5, 0.25)),
			init_nbr(3 * pow(z.re, 2) - 3 * pow(z.im, 2), 6 * z.re * z.im))));
	}
	return (z);
}
