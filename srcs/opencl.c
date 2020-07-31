#include "fractol.h"

static void	create_kernel(t_cl *cl)
{
	if (!(cl->kernel = clCreateKernel(cl->program, "draw_fract_cl", &cl->ret)))
		ft_error("Error: failed to create kernel from source file", NULL);
	if ((cl->ret = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
					CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t),
					&cl->max_work_group_size, NULL)) != CL_SUCCESS)
		ft_error("Error: failed to retrieve kernel work group info", NULL);
	cl->local[0] = (cl->max_work_group_size > 1) ?
			(cl->max_work_group_size / 32) : cl->max_work_group_size;
	cl->local[1] = cl->max_work_group_size / cl->local[0];
	cl->global[0] = ft_divide_up(DW, cl->local[0]) * cl->local[0];
	cl->global[1] = ft_divide_up(DH, cl->local[1]) * cl->local[1];
}

static void	build_program_with_buffer(char *src_file, t_cl *cl)
{
	char		*log;
	size_t		log_size;
	int			size;

	size = DW * DH;
	cl->program = clCreateProgramWithSource(cl->context, 1,
			(const char **)&src_file, NULL, &(cl->ret));
	if ((cl->ret = clBuildProgram(cl->program, 0, NULL, NULL, NULL, NULL))
			!= CL_SUCCESS)
	{
		clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		log = (char *)malloc(sizeof(log_size));
		clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		ft_putendl_fd(log, 1);
	}
	create_kernel(cl);
	cl->mem_obj = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
			sizeof(int) * size, NULL, &(cl->ret));
	ft_strdel(&src_file);
}

static t_cl	init_opencl(char *src_file)
{
	t_cl		cl;

	cl.ret = clGetPlatformIDs(1, &(cl.platform_id), NULL);
	cl.ret = clGetDeviceIDs(cl.platform_id, CL_DEVICE_TYPE_GPU,
			1, &(cl.device_id), NULL);
	cl.context = clCreateContext(0, 1, &(cl.device_id), NULL, NULL,
			&(cl.ret));
	cl.queue = clCreateCommandQueue(cl.context, cl.device_id, 0,
			&(cl.ret));
	build_program_with_buffer(src_file, &cl);
	return (cl);
}

void		opencl(t_fract *fr)
{
	fr->cl = init_opencl(get_src_file("srcs/draw.cl"));
	clSetKernelArg(fr->cl.kernel, 0, sizeof(float), &(fr->k.re));
	clSetKernelArg(fr->cl.kernel, 1, sizeof(float), &(fr->k.im));
	clSetKernelArg(fr->cl.kernel, 2, sizeof(float), &(fr->coef.re));
	clSetKernelArg(fr->cl.kernel, 3, sizeof(float), &(fr->coef.im));
	clSetKernelArg(fr->cl.kernel, 4, sizeof(float), &(fr->max.im));
	clSetKernelArg(fr->cl.kernel, 5, sizeof(float), &(fr->min.re));
	clSetKernelArg(fr->cl.kernel, 6, sizeof(int), &fr->max_iter);
	clSetKernelArg(fr->cl.kernel, 7, sizeof(int), &fr->width);
	clSetKernelArg(fr->cl.kernel, 8, sizeof(int), &fr->type);
	clSetKernelArg(fr->cl.kernel, 9, sizeof(int), &fr->rgb[0]);
	clSetKernelArg(fr->cl.kernel, 10, sizeof(int), &fr->rgb[1]);
	clSetKernelArg(fr->cl.kernel, 11, sizeof(int), &fr->rgb[2]);
	clSetKernelArg(fr->cl.kernel, 12, sizeof(int), &fr->rgb_flag);
	clSetKernelArg(fr->cl.kernel, 13, sizeof(cl_mem), &fr->cl.mem_obj);
	fr->cl.ret = clEnqueueNDRangeKernel(fr->cl.queue, fr->cl.kernel, 2,
			NULL, fr->cl.global, fr->cl.local, 0, NULL, NULL);
	fr->cl.ret = clEnqueueReadBuffer(fr->cl.queue, fr->cl.mem_obj,
			CL_TRUE, 0, sizeof(int) * (fr->width * fr->hight),
			fr->win.img_arr, 0, NULL, NULL);
	clear_opencl(fr);
}
