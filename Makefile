NAME		= cub3D

INC_PATH	= ./includes
SRC_PATH	= ./srcs
MLX_PATH	= ./mlx
CON_PATH	= ./config
GNL_PATH	= ./gnl
UTL_PATH	= ./utils
BNS_PATH	= ./bonus

INCS		= -I $(INC_PATH)
SRCS		= $(SRC_PATH)/main.c $(SRC_PATH)/info.c $(SRC_PATH)/close.c $(SRC_PATH)/window.c \
			  $(SRC_PATH)/key_handling.c $(SRC_PATH)/wall1.c $(SRC_PATH)/wall2.c $(SRC_PATH)/floor.c \
			  $(SRC_PATH)/sprite1.c $(SRC_PATH)/sprite2.c $(SRC_PATH)/texture.c \
			  $(CON_PATH)/config.c $(CON_PATH)/map_check.c $(CON_PATH)/map.c $(CON_PATH)/parse.c \
			  $(CON_PATH)/valid_check.c \
			  $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c \
			  $(UTL_PATH)/ft_atoi.c $(UTL_PATH)/ft_endcmp.c $(UTL_PATH)/ft_strcmp.c $(UTL_PATH)/ft_strlen.c \
			  $(UTL_PATH)/ft_strrchr.c $(UTL_PATH)/lst_add_back.c $(UTL_PATH)/utils.c \
			  $(BNS_PATH)/ui.c $(BNS_PATH)/minimap.c
OBJS		= $(SRCS:.c=.o)

CC			= gcc
CFLAGS		= -O3 -Wall -Wextra -Werror
MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit
MLX			= libmlx.dylib

.c.o:
		$(CC) $(CFLAGS) $(INCS) -c $< -o $(<:.c=.o)

$(NAME):	$(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) -L $(MLX_PATH) $(MLXFLAGS) $(OBJS)
	@install_name_tool -change libmlx.dylib @loader_path/mlx/libmlx.dylib cub3d
	@echo $(NAME) : Created

$(MLX):
	@$(MAKE) -C mlx

all:	$(NAME)

clean:
	@$(MAKE) -C mlx clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(MLX)

re:		fclean all

.PHONY: all clean fclean re
