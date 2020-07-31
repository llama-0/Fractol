# define FABS(x) ((x) < 0 ? -(x) : (x))
# define C 8
# define V 9
# define N_1 18
# define N_2 19
# define N_3 20
# define N_4 21
# define N_5 23
# define MAGENTA 0xFF00FF
# define YELLOW 0xFFFF00

typedef struct			s_complex
{
	float				re;
	float				im;
}						t_complex;

float  f_sqrt(float n);

float  f_sqrt(float n)
{
    float  lo;
    float  hi;
    float  mid;
    size_t  i;
    
    lo = 0;
    hi = n;
    i = 0;
    while(i < 1000)
    {
        mid = (lo + hi) / 2;
        if (mid * mid == n)
            return (mid);
        if (mid * mid > n)
            hi = mid;
        else
            lo = mid;
        i++;
    }
    return mid;
}


t_complex	init_nbr(float re, float im);

t_complex	init_nbr(float re, float im)
{
	return ((t_complex){re, im});
}

t_complex	subtract(t_complex a, t_complex b);

t_complex	subtract(t_complex a, t_complex b)
{
	return (init_nbr(a.re - b.re, a.im - b.im));
}

t_complex	multiply(t_complex a, t_complex b);

t_complex	multiply(t_complex a, t_complex b)
{
	return (init_nbr(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re));
}

t_complex	divide(t_complex a, t_complex b);

t_complex	divide(t_complex a, t_complex b)
{
	float divider;

	divider = b.re * b.re + b.im * b.im;
	return (init_nbr(
		(a.re * b.re + a.im * b.im) / divider,
		(a.im * b.re - a.re * b.im) / divider));
}

float		abs_complex(t_complex z);

float		abs_complex(t_complex z)
{
	return (z.re * z.re + z.im * z.im);
}

int     color(int iter, int max_iter, int rgb_0, int rgb_1, int rgb_2, int rgb_flag, int type);

int     color(int iter, int max_iter, int rgb_0, int rgb_1, int rgb_2, int rgb_flag, int type)
{
    float  t;

    t = (float)iter/(float)max_iter;
    if (rgb_flag == 0)
    {
        rgb_0 = (int)(9*(1 - t)*t*t*t*255);
        rgb_1 = (int)(15*(1 - t)*(1 - t)*t*t*255);
        rgb_2 = (int)(8.5*(1 - t)*(1 - t)*(1 - t)*t*255);
    }
    else if (rgb_flag == C)
    {
		if (type == 2)
		{
			if (iter % 2 == 0)
				return (MAGENTA);
			else
				return (YELLOW);
		}
		else
        {
			rgb_0 = (int)(8.5*(1 - t)*(1 - t)*(1 - t)*t*255);
        	rgb_1 = (int)(9*(1 - t)*t*t*t*255);
        	rgb_2 = (int)(15*(1 - t)*(1 - t)*t*t*255);
		}
    }
    else if (rgb_flag == V)
    {
        rgb_0 = (int)(15*(1 - t)*(1 - t)*t*t*255);
        rgb_1 = (int)(8.5*(1 - t)*(1 - t)*(1 - t)*t*255);
        rgb_2 = (int)(9*(1 - t)*t*t*t*255);
    }
    return ((rgb_0 << 16) | (rgb_1 << 8) | rgb_2);
}

int     color_sin(int iter, int max_iter, int rgb_0, int rgb_1, int rgb_2, int rgb_flag, int type);

int     color_sin(int iter, int max_iter, int rgb_0, int rgb_1, int rgb_2, int rgb_flag, int type)
{
    float  t;

    t = (float)iter/(float)max_iter;
    rgb_0 = (int)(15*(1 - t)*(1 - t)*t*t*255);
    rgb_1 = (int)(15*(1 - t)*t*t*t*255);
    rgb_2 = (int)(5*(1 - t)*t*t*t*255);
    return ((rgb_0 << 16) | (rgb_1 << 8) | rgb_2);
}

t_complex			newton_formula(int type, t_complex z);

t_complex			newton_formula(int type, t_complex z)
{
	if (type == N_1 || type == N_2)
    {
		return (subtract(init_nbr(z.re, z.im), divide(init_nbr(
		    pow(z.re, 3) - 3 * z.re * pow(z.im, 2) - 1,
		    3 * pow(z.re, 2) * z.im - pow(z.im, 3)),
		    init_nbr(3 * pow(z.re, 2) - 3 * pow(z.im, 2), 6 * z.re * z.im))));
    }
	if (type == N_3)
	{
		return (subtract(init_nbr(z.re, z.im), divide(init_nbr(
			sin(z.re) * cosh(z.im) - 1,
			cos(z.re) * sinh(z.im)),
			init_nbr(cos(z.re) * cosh(z.im), -sin(z.re) * sinh(z.im)))));
	}
	if (type == N_4)
	{
		return (subtract(init_nbr(z.re, z.im), init_nbr(
			-sinh(2 * z.re) / (cos(2 * z.im) - cosh(2 * z.re)),
			sin(2 * z.im) / (cos(2 * z.im) - cosh(2 * z.re)))));
	}
	if (type == N_5)
	{
		return (subtract(init_nbr(z.re, z.im), divide(multiply(init_nbr(
			pow(z.re, 3) - 3 * z.re * pow(z.im, 2) - 1,
			3 * pow(z.re, 2) * z.im - pow(z.im, 3)), init_nbr(0.5, 0.25)),
			init_nbr(3 * pow(z.re, 2) - 3 * pow(z.im, 2), 6 * z.re * z.im))));
	}
	return (z);
}

__kernel void draw_fract_cl(float k_re,
                float k_im,
                float coef_re,
                float coef_im,
                float max_im,
                float min_re,
                int max_iter,
                int width,
                int type,
                int rgb_0,
                int rgb_1,
                int rgb_2,
                int rgb_flag,
                __global int *img_arr)
{
    t_complex	z;
	float      z_im;
  	float      z_re;
    float      re;
    float      im;
	float      c_re;
	float      c_im;
	size_t      x;
	size_t      y;
	int         iter;

    x = get_global_id(0);
    y = get_global_id(1);
	c_im = max_im - (float)y * coef_im;
	c_re = min_re + (float)x * coef_re;
	z_re = c_re;
  	z_im = c_im;
    re = c_re;
    im = c_im;
	iter = 0;
    if (type == N_1)
    {
        t_complex	roots[3];
        float		t;

        roots[0] = init_nbr(1.0, 0.0);
        roots[1] = init_nbr(-0.5, f_sqrt(3) / 2);
        roots[2] = init_nbr(-0.5, -f_sqrt(3) / 2);
        t = 0.0001;
        c_re = min_re + x * coef_re;
        z = init_nbr(c_re, c_im);
        while (iter < max_iter && (abs_complex(subtract(z, roots[0]))) >= t
                && (abs_complex(subtract(z, roots[1]))) >= t
                && (abs_complex(subtract(z, roots[2]))) >= t)
        {
            if (abs_complex(z) > 0)
                z = newton_formula(type, z);
            iter++;
            if (abs_complex(subtract(z, roots[0])) < t)
                (img_arr)[(int)(x + y * width)] =
                        (((255 - iter * 15) << 16) | (0 << 8) | 0);
            if (abs_complex(subtract(z, roots[1])) <= t)
                (img_arr)[(int)(x + y * width)] =
                        ((0 << 16) | ((255 - iter * 15) << 8) | 0);
            if (abs_complex(subtract(z, roots[2])) <= t)
                (img_arr)[(int)(x + y * width)] =
                        ((0 << 16) | (0 << 8) | ((255 - iter * 15) << 0));
        }
    }
    else if (type == N_2 || type == N_3 || type == N_4 || type == N_5)
    {
        t_complex	z1;
        t_complex	delta;

        c_re = min_re + x * coef_re;
        z = init_nbr(c_re, c_im);
        iter = -1;
        delta = z;
        while (++iter < max_iter && abs_complex(z) < 1e+6
                                    && abs_complex(delta) > 1e-6)
        {
            z1 = z;
            z = newton_formula(type, z);
            delta = subtract(z1, z);
        }
        if (type == N_5)
        {
            iter = iter;
            (img_arr)[(int)(x + y * width)] = color(iter, max_iter, rgb_0, rgb_1, rgb_2, rgb_flag, type);
        }
        else if (type == N_2)
        {
            (img_arr)[(int)(x + y * width)] = (((iter % 20 * 30) << 16)
                | ((iter % 8 * 64) << 8) | (iter % 45 * 7));
        }
        else if (type == N_4)
        {
            (img_arr)[(int)(x + y * width)] = (((iter % 32 * 332) << 16)
                | ((iter % 8 * 64) << 8) | (iter % 48 * 7));
        }
        else
        {
            (img_arr)[(int)(x + y * width)] = color_sin(iter, max_iter, rgb_0, rgb_1, rgb_2, rgb_flag, type);
        }
    }
    else
    {
        while (z_re * z_re + z_im * z_im <= 4 && iter <  max_iter)
        {
            if (type == 1)
            {
                re = z_re * z_re - z_im * z_im + c_re;
                im = 2.0 * z_re * z_im + c_im;
            }
            if (type == 2)
            {
                re = z_re * z_re - z_im * z_im + k_re;
                im = 2.0 * z_re * z_im + k_im;
            }
            if (type == 3)
            {
                re = FABS(z_re * z_re) - FABS(z_im * z_im) + c_re;
                im = -2.0 * FABS(z_re * z_im) + c_im;
            }
            if (type == 4)
            {
                re = z_re * z_re - z_im * z_im + c_re;
                im = -2.0 * z_re * z_im + c_im;
            }
            z_re = re;
            z_im = im;
            iter++;
        }
        if (iter <  max_iter)
            img_arr[(int)(x + y * width)] = color(iter, max_iter, rgb_0, rgb_1, rgb_2, rgb_flag, type);
        else
            img_arr[(int)(x + y * width)] = 0x0;
    }
}