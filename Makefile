SRCS = fdf.c parsing_map.c rotation.c translation.c utils.c drawing.c coloring.c scaling.c hooks.c
HELPERS = libft/ft_bzero.c libft/get_next_line.c libft/get_next_line_utils.c libft/ft_atoi.c libft/ft_split.c libft/ft_isdigit.c libft/ft_putstr_fd.c libft/ft_strlcpy.c libft/ft_tolower.c libft/ft_hextoi.c
BNS_SRCS = fdf_bonus.c parsing_map_bonus.c rotation_bonus.c translation_bonus.c utils_bonus.c drawing_bonus.c coloring_bonus.c scaling_bonus.c hooks_bonus.c
SPR_BNS_SRCS = fdf_super_bonus.c perlin_noise.c parsing_map_bonus.c rotation_bonus.c translation_bonus.c utils_bonus.c drawing_bonus.c coloring_bonus.c scaling_bonus.c hooks_bonus.c
OBJS = $(SRCS:.c=.o)
HELPER_OBJS = $(HELPERS:.c=.o)
BNS_OBJS = $(BNS_SRCS:.c=.o)
SPR_BNS_OBJS = $(SPR_BNS_SRCS:.c=.o)
NAME = fdf
FLAGS = -Wall -Wextra -Werror
CC = gcc
HDRS = fdf.h fdf_bonus.h
MLX_PATH = /usr/include/minilibx-linux
MLX_LIB = -L$(MLX_PATH) -lmlx
MLX_INC = -I$(MLX_PATH)
INCLUDE = -L/usr/include

.PHONY: clean fclean re all

#####################################
CUBE = cube3d.c
CUBE_OBJ = cube3d.o

cube: $(CUBE_OBJ)
	$(CC) $(CUBE_OBJ) $(MLX_LIB) $(INCLUDE) -lXext -lX11 -lm -lz -o $(NAME)
#####################################

all: $(NAME)

super_bonus: $(SPR_BNS_OBJS) $(HELPER_OBJS)
	touch super_bonus
	$(CC) $(SPR_BNS_OBJS) $(HELPER_OBJS) $(MLX_LIB) $(INCLUDE) -lXext -lX11 -lm -lz -o $(NAME)

bonus: $(BNS_OBJS) $(HELPER_OBJS)
	touch bonus
	$(CC) $(BNS_OBJS) $(HELPER_OBJS) $(MLX_LIB) $(INCLUDE) -lXext -lX11 -lm -lz -o $(NAME)

$(NAME): $(OBJS) $(HELPER_OBJS)
	$(CC) $(OBJS) $(HELPER_OBJS) $(MLX_LIB) $(INCLUDE) -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(FLAGS) $(MLX_INC) -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(HELPER_OBJS) $(OBJS) $(BNS_OBJS) $(SPR_BNS_OBJS) bonus super_bonus

fclean: clean
	rm -f $(NAME)

re: fclean all
