SRCS = mandatory/fdf.c mandatory/parsing_map.c \
	mandatory/rotation.c mandatory/translation.c \
	mandatory/utils.c mandatory/drawing.c mandatory/coloring.c \
	mandatory/scaling.c mandatory/hooks.c mandatory/freeing.c
HELPERS = libft/ft_bzero.c libft/get_next_line.c \
	libft/get_next_line_utils.c libft/ft_atoi.c \
	libft/ft_split.c libft/ft_isdigit.c libft/ft_putstr_fd.c \
	libft/ft_strlcpy.c libft/ft_tolower.c libft/ft_hextoi.c \
	libft/ft_strncmp.c
BNS_SRCS = bonus_files/fdf_bonus.c bonus_files/parsing_map_bonus.c \
	bonus_files/rotation_bonus.c bonus_files/translation_bonus.c \
	bonus_files/utils_bonus.c bonus_files/utils2_bonus.c \
	bonus_files/drawing_bonus.c bonus_files/coloring_bonus.c \
	bonus_files/scaling_bonus.c bonus_files/hooks_bonus.c \
	bonus_files/projection_bonus.c bonus_files/freeing_bonus.c
OBJS = $(SRCS:.c=.o)
HELPER_OBJS = $(HELPERS:.c=.o)
BNS_OBJS = $(BNS_SRCS:.c=.o)
NAME = fdf
BNS_NAME = fdf_bonus
FLAGS = -Wall -Wextra -Werror
CC = cc
HDRS = mandatory/fdf.h bonus_files/fdf_bonus.h
MLX_PATH = /usr/include/minilibx-linux
MLX_LIB = -L$(MLX_PATH) -lmlx
MLX_INC = -I$(MLX_PATH)
INCLUDE = -L/usr/include

.PHONY: clean fclean re all

all: $(NAME)

bonus: $(BNS_OBJS) $(HELPER_OBJS)
	touch bonus
	$(CC) $(BNS_OBJS) $(HELPER_OBJS) $(MLX_LIB) $(INCLUDE) -lXext -lX11 -lm -lz -o $(BNS_NAME)

$(NAME): $(OBJS) $(HELPER_OBJS)
	$(CC) $(OBJS) $(HELPER_OBJS) $(MLX_LIB) $(INCLUDE) -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(FLAGS) $(MLX_INC) -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(HELPER_OBJS) $(OBJS) $(BNS_OBJS) bonus

fclean: clean
	rm -f $(NAME) $(BNS_NAME)

re: fclean all
