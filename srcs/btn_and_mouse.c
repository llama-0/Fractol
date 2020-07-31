#include "fractol.h"

int	key_release(int keycode, t_fract *fr)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == N_1 || keycode == N_2 || keycode == N_3 ||
			keycode == N_4 || keycode == N_5)
		fr->type = keycode;
	if (keycode == O)
		fr->cl_on = 1;
	if (keycode == C || keycode == V)
		fr->rgb_flag = keycode;
	if (keycode == R)
		reset(fr);
	if (keycode == LEFT || keycode == RIGHT || keycode == DOWN || keycode == UP)
		move_fractal(fr, keycode);
	if (keycode == F)
		fr->is_julia_fixed = 1;
	if (keycode == U)
		fr->is_julia_fixed = 0;
	if (keycode == MINUS_SIGN)
		fr->max_iter -= 10;
	if (keycode == PLUS_SIGN)
		fr->max_iter += 10;
	new_image(fr);
	return (0);
}

int	mouse_move(int x, int y, t_fract *fr)
{
	if (!fr->is_julia_fixed)
	{
		fr->k = init_nbr(
				4 * (double)x / DW - 2,
				4 * (double)(DH - y) / DH - 2);
	}
	new_image(fr);
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_fract *fr)
{
	double	zoom;

	if (keycode == 1 || keycode == 2 || keycode == 3)
		return (0);
	zoom = ZOOM_IN;
	if (keycode == M_UP || keycode == M_DOWN)
	{
		if (keycode == M_DOWN)
			zoom = ZOOM_OUT;
		fr->mouse_pos = init_nbr(
				(x * fr->coef.re + fr->min.re),
				(fr->max.im - y * fr->coef.im));
	}
	ft_zoom(zoom, fr);
	new_image(fr);
	return (0);
}
