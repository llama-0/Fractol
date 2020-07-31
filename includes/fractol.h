#ifndef FRACTOL_H
# define FRACTOL_H

/*
** Adjust graphical libraries for MacOS Mojave 10.14+
*/

# define CL_SILENCE_DEPRECATION

# include <fcntl.h>
# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <OpenGL/OpenGL.h>
# include <OpenCL/OpenCL.h>

# define USAGE "usage: ./fractol [Mandelbrot] [Julia] [Burning-ship]"
# define WRONG_ARG_1 "Error: provide a valid fractal name:"
# define WRONG_ARG_2 "[Mandelbrot] [Julia] [Burning-ship]"

# define DW 1024
# define DH 1024 // make 800 for small screens like 13-inch for the best experience

# define MENU_DW 32
# define MENU_DH 32

# define K_RE -0.70176
# define K_IM -0.3842

# define ZOOM_IN 0.1
# define ZOOM_OUT 8.1

# define SHIFT_COEF 12
# define MAX_ITER 50

# define BLACK  0x0
# define WHITE  0xFFFFFF
# define RED  0xFF
# define GREEN  0x00FF00
# define BLUE  0x0000FF
# define MAGENTA 0xFF00FF
# define YELLOW 0xFFFF00

/*
** keycodes
*/

# define ESC 53
# define N_1 18
# define N_2 19
# define N_3 20
# define N_4 21
# define N_5 23
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define O 31
# define C 8
# define V 9
# define R 15
# define F 3
# define U 32
# define MINUS_SIGN 27
# define PLUS_SIGN 24
# define M_UP 4
# define M_DOWN 5

typedef	struct			s_win
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	int					*img_arr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
}						t_win;

typedef struct			s_complex
{
	double				re;
	double				im;
}						t_complex;

typedef struct			s_cl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				mem_obj;
	cl_int				ret;
	size_t				max_work_group_size;
	size_t				global[2];
	size_t				local[2];
}						t_cl;

typedef struct			s_fract
{
	t_win				win;
	t_complex			min;
	t_complex			max;
	t_complex			coef;
	t_complex			mouse_pos;
	t_complex			c;
	t_complex			k;
	int					width;
	int					hight;
	int					iter;
	int					max_iter;
	int					type;
	int					rgb[3];
	int					rgb_flag;
	int					is_julia_fixed;
	int					cl_on;
	t_cl				cl;
}						t_fract;

t_complex				init_nbr(double re, double im);
t_fract					*fractal_setup(int type);
void					draw_fractal(t_fract *fr);
int						color(t_fract *fr);

t_complex				fractal_formula(t_fract *fr, t_complex z);

int						key_release(int keycode, t_fract *fr);
int						mouse_press(int keycode, int x, int y, t_fract *fr);
int						mouse_move(int x, int y, t_fract *fr);

void					ft_zoom(double zoom, t_fract *fr);
void					move_fractal(t_fract *fr, int keycode);

void					reset(t_fract *fr);
void					new_image(t_fract *fr);

char					*get_src_file(char *file_name);
int						ft_divide_up(int a, int b);
void					clear_opencl(t_fract *fr);
void					opencl(t_fract *fr);

void					show_menu(t_fract *fr);
void					ft_error(char *s1, char *s2);

t_complex				subtract(t_complex a, t_complex b);
t_complex				multiply(t_complex a, t_complex b);
t_complex				divide(t_complex a, t_complex b);

t_complex				newton_formula(t_fract *fr, t_complex z);
void					color_newton_root(t_fract *fr, t_complex z,
							double x, double y);
void					color_newton_converge(t_fract *fr, double x, double y);
double					abs_complex(t_complex z);
void					draw_newton_fractal(t_fract *fr, double x, double y);
void					show_newton_menu(t_fract *fr);

#endif
