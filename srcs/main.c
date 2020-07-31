#include "fractol.h"

void		ft_error(char *s1, char *s2)
{
	ft_putendl_fd(s1, 2);
	if (s2)
		ft_putendl_fd(s2, 2);
	exit(1);
}

void		new_image(t_fract *fr)
{
	mlx_clear_window(fr->win.mlx_ptr, fr->win.win_ptr);
	if (fr->cl_on)
		opencl(fr);
	else
		draw_fractal(fr);
	mlx_put_image_to_window(fr->win.mlx_ptr, fr->win.win_ptr,
			fr->win.img_ptr, 0, 0);
	if (fr->type == 1 || fr->type == 2 || fr->type == 3)
		show_menu(fr);
	else
		show_newton_menu(fr);
}

static void	init(t_fract *fr)
{
	fr->win.mlx_ptr = mlx_init();
	fr->win.win_ptr = mlx_new_window(fr->win.mlx_ptr, DW, DH, "Fractol");
	fr->win.img_ptr = mlx_new_image(fr->win.mlx_ptr, DW, DH);
	fr->win.img_arr = (int *)mlx_get_data_addr(fr->win.img_ptr,
			&fr->win.bits_per_pixel, &fr->win.size_line, &fr->win.endian);
	new_image(fr);
	mlx_hook(fr->win.win_ptr, 2, 0, key_release, (void *)fr);
	mlx_hook(fr->win.win_ptr, 4, 0, mouse_press, (void *)fr);
	if (fr->type == 2)
		mlx_hook(fr->win.win_ptr, 6, 0, mouse_move, (void *)fr);
	mlx_loop(fr->win.mlx_ptr);
}

static int	fractal_type(char *s)
{
	if (ft_strequ(s, "Mandelbrot"))
		return (1);
	if (ft_strequ(s, "Julia"))
		return (2);
	if (ft_strequ(s, "Burning-ship"))
		return (3);
	return (-1);
}

int			main(int ac, char **av)
{
	t_fract	*fr;
	int		type;

	if (ac != 2)
		ft_error(USAGE, NULL);
	else
	{
		if ((type = fractal_type(av[1])) == -1)
			ft_error(WRONG_ARG_1, WRONG_ARG_2);
		fr = fractal_setup(type);
		init(fr);
	}
	return (0);
}
