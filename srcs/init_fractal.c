#include "fractol.h"

t_fract	*fractal_setup(int type)
{
	t_fract	*fr;

	fr = (t_fract *)malloc(sizeof(t_fract));
	fr->max_iter = MAX_ITER;
	fr->min = init_nbr(-2.0, -2.0);
	fr->max.re = 2.0;
	fr->max.im = fr->min.im + (fr->max.re - fr->min.re) * DH / DW;
	fr->coef = init_nbr(
		(fr->max.re - fr->min.re) / (DW - 1),
		(fr->max.im - fr->min.im) / (DH - 1));
	fr->mouse_pos = init_nbr(0.0, 0.0);
	fr->c = init_nbr(0.0, 0.0);
	fr->k = init_nbr(K_RE, K_IM);
	fr->iter = 0;
	fr->width = DW;
	fr->hight = DH;
	fr->type = type;
	fr->rgb[0] = 0;
	fr->rgb[1] = 0;
	fr->rgb[2] = 0;
	fr->rgb_flag = 0;
	fr->is_julia_fixed = 1;
	fr->cl_on = 0;
	return (fr);
}

void	reset(t_fract *fr)
{
	fr->max_iter = MAX_ITER;
	fr->min = init_nbr(-2.0, -2.0);
	fr->max.re = 2.0;
	fr->max.im = fr->min.im + (fr->max.re - fr->min.re) * DH / DW;
	fr->rgb[0] = 0;
	fr->rgb[1] = 0;
	fr->rgb[2] = 0;
	fr->coef = init_nbr(
		(fr->max.re - fr->min.re) / DW,
		(fr->max.im - fr->min.im) / DH);
	fr->iter = 0;
	fr->width = DW;
	fr->hight = DH;
	fr->rgb_flag = 0;
	fr->is_julia_fixed = 1;
	fr->cl_on = 0;
}
