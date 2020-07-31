#include "fractol.h"

char	*get_src_file(char *file_name)
{
	char	buf[BUFF_SIZE + 1];
	char	*src;
	int		fd;
	int		ret;

	if (!(fd = open(file_name, O_RDONLY)))
		ft_error("Error: opencl source file failed to open", NULL);
	ret = read(fd, buf, BUFF_SIZE);
	buf[ret] = '\0';
	src = ft_strdup(buf);
	close(fd);
	return (src);
}

int		ft_divide_up(int a, int b)
{
	return ((a % b) != 0) ? (a / b + 1) : (a / b);
}

void	clear_opencl(t_fract *fr)
{
	if ((fr->cl.ret = clReleaseMemObject(fr->cl.mem_obj)) != 0)
		ft_putendl_fd("mem_obj leaks", 2);
	if ((fr->cl.ret = clReleaseProgram(fr->cl.program)) != 0)
		ft_putendl_fd("program leaks", 2);
	if ((fr->cl.ret = clReleaseKernel(fr->cl.kernel)) != 0)
		ft_putendl_fd("kernel leaks", 2);
	if ((fr->cl.ret = clReleaseCommandQueue(fr->cl.queue)) != 0)
		ft_putendl_fd("queue leaks", 2);
	if ((fr->cl.ret = clReleaseContext(fr->cl.context)) != 0)
		ft_putendl_fd("context leaks", 2);
}
