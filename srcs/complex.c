#include "fractol.h"

t_complex	init_nbr(double re, double im)
{
	return ((t_complex){re, im});
}

/*
** t_complex	add(t_complex a, t_complex b)
** {
** 	return (init_nbr(a.re + b.re, a.im + b.im));
** }
*/

t_complex	subtract(t_complex a, t_complex b)
{
	return (init_nbr(a.re - b.re, a.im - b.im));
}

t_complex	multiply(t_complex a, t_complex b)
{
	return (init_nbr(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re));
}

t_complex	divide(t_complex a, t_complex b)
{
	double divider;

	divider = b.re * b.re + b.im * b.im;
	return (init_nbr(
		(a.re * b.re + a.im * b.im) / divider,
		(a.im * b.re - a.re * b.im) / divider));
}

double		abs_complex(t_complex z)
{
	return (z.re * z.re + z.im * z.im);
}
