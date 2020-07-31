#include "fractol.h"

void	show_menu(t_fract *fr)
{
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH, BLUE, "f / u -- fix / unfix julia");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 20, BLUE, "c -- color set #1");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 40, BLUE, "v -- color set #2");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 60, BLUE, "r -- reset all");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW + 300, MENU_DH, BLUE, "o -- opencl mode");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW + 300, MENU_DH + 20, BLUE,
			"+ / - -- increase / decrease iterations");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW + 300, MENU_DH + 40, BLUE, "arrows -- shift position");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW + 740, MENU_DH, BLUE, "scroll down -- zoom in");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW + 740, MENU_DH + 20, BLUE, "scroll up -- zoom out");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW + 740, MENU_DH + 40, BLUE, "esc -- quit");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, DH - MENU_DH, WHITE, "Bonus 1 - 5 -- Newton fractals");
}

void	show_newton_menu(t_fract *fr)
{
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH, WHITE, "c / v -- color sets #1 / #2 (only for 5)");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 20, WHITE,
			"+ / - -- increase / decrease iterations");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 40, WHITE, "o -- opencl mode");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 60, WHITE, "arrows -- shift position");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 80, WHITE, "scroll down -- zoom in");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 100, WHITE, "scroll up -- zoom out");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 120, WHITE, "r -- reset all");
	mlx_string_put(fr->win.mlx_ptr, fr->win.win_ptr,
		MENU_DW, MENU_DH + 140, WHITE, "esc -- quit");
}
