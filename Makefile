# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: koparker <koparker@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 22:10:26 by koparker          #+#    #+#              #
#    Updated: 2020/02/23 15:28:12 by koparker         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

DEBUG = -g

WFLAGS = -Wall -Wextra -Werror

GFLAGS = -lmlx -framework OpenGL -framework AppKit -framework OpenCL

MLX = tools/minilibx_macos

LIBMLX = -L $(MLX) $(GFLAGS)

SRC_DIR = srcs

SRCS = complex.c \
	   init_fractal.c \
	   color.c \
	   zoom.c \
	   newton.c \
	   draw.c \
       btn_and_mouse.c \
	   fractal_formulas.c \
	   menu.c \
	   opencl_helpers.c \
	   opencl.c \
	   main.c

LIBFT = -L libft -lft

OBJ_DIR = objs

SRC = $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

INCLUDES = -I includes -I libft/includes -I tools/minilibx_macos

HDR = includes/fractol.h

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling..."
	@make -C libft
	@make -C $(MLX)
	@gcc $(WFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBMLX)
	@echo "Fractol is ready."

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	@mkdir -p $(OBJ_DIR)
	@gcc $(WFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@make -C $(MLX) clean

re: fclean all
