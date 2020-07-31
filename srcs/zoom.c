#include "fractol.h"

static void	zoom_out(double *edge, double mouse_pos, double zoom)
{
	*edge += (*edge - mouse_pos) / zoom;
}

static void	zoom_in(double *edge, double mouse_pos, double zoom)
{
	*edge += -(*edge - mouse_pos) * zoom;
}

void		ft_zoom(double zoom, t_fract *fr)
{
	if (zoom == ZOOM_OUT)
	{
		zoom_out(&fr->min.re, fr->mouse_pos.re, zoom);
		zoom_out(&fr->max.re, fr->mouse_pos.re, zoom);
		zoom_out(&fr->min.im, fr->mouse_pos.im, zoom);
		zoom_out(&fr->max.im, fr->mouse_pos.im, zoom);
	}
	if (zoom == ZOOM_IN)
	{
		zoom_in(&fr->min.re, fr->mouse_pos.re, zoom);
		zoom_in(&fr->max.re, fr->mouse_pos.re, zoom);
		zoom_in(&fr->min.im, fr->mouse_pos.im, zoom);
		zoom_in(&fr->max.im, fr->mouse_pos.im, zoom);
	}
	fr->coef = init_nbr(
			(fr->max.re - fr->min.re) / (DW - 1),
			(fr->max.im - fr->min.im) / (DH - 1));
}

static void	move(double *edge, double coef, char sign)
{
	if (sign == '+')
		*edge += coef * SHIFT_COEF;
	else
		*edge -= coef * SHIFT_COEF;
}

/*
** Implemented reflected view of arrows
*/

void		move_fractal(t_fract *fr, int keycode)
{
	if (keycode == LEFT)
	{
		move(&fr->min.re, fr->coef.re, '+');
		move(&fr->max.re, fr->coef.re, '+');
	}
	if (keycode == UP)
	{
		move(&fr->min.im, fr->coef.im, '-');
		move(&fr->max.im, fr->coef.im, '-');
	}
	if (keycode == RIGHT)
	{
		move(&fr->min.re, fr->coef.re, '-');
		move(&fr->max.re, fr->coef.re, '-');
	}
	if (keycode == DOWN)
	{
		move(&fr->min.im, fr->coef.im, '+');
		move(&fr->max.im, fr->coef.im, '+');
	}
}
