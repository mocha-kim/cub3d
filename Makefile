NAME		= cub3D
BONUS		= cub3D_bonus

INC_PATH	= ./includes
SRC_PATH	= ./srcs
MMS_PATH	= ./mlx_beta
MLX_PATH	= ./mlx
CON_PATH	= ./config
GNL_PATH	= ./gnl
UTL_PATH	= ./utils
BNS_PATH	= ./bonus

INCS		= -I $(INC_PATH)
SRCS		= $(SRC_PATH)/main.c $(SRC_PATH)/info.c $(SRC_PATH)/close.c $(SRC_PATH)/window.c \
			  $(SRC_PATH)/key_handling.c $(SRC_PATH)/wall1.c $(SRC_PATH)/wall2.c $(SRC_PATH)/floor.c \
			  $(SRC_PATH)/sprite1.c $(SRC_PATH)/sprite2.c $(SRC_PATH)/texture.c \
			  $(SRC_PATH)/save_bmp.c \
			  $(CON_PATH)/config.c $(CON_PATH)/map_check.c $(CON_PATH)/map.c $(CON_PATH)/parse.c \
			  $(CON_PATH)/valid_check.c \
			  $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c \
			  $(UTL_PATH)/ft_atoi.c $(UTL_PATH)/ft_endcmp.c $(UTL_PATH)/ft_strcmp.c $(UTL_PATH)/ft_strlen.c \
			  $(UTL_PATH)/ft_itoa.c $(UTL_PATH)/ft_strrchr.c $(UTL_PATH)/lst_add_back.c $(UTL_PATH)/utils.c
OBJS		= $(SRCS:.c=.o)

BNS_SRCS	= $(BNS_PATH)/main_bonus.c $(SRC_PATH)/info.c $(SRC_PATH)/close.c $(SRC_PATH)/window.c \
			  $(SRC_PATH)/key_handling.c $(SRC_PATH)/wall1.c $(SRC_PATH)/wall2.c $(SRC_PATH)/floor.c \
			  $(SRC_PATH)/sprite1.c $(SRC_PATH)/sprite2.c $(SRC_PATH)/texture.c \
			  $(SRC_PATH)/save_bmp.c \
			  $(CON_PATH)/config.c $(CON_PATH)/map_check.c $(CON_PATH)/map.c $(CON_PATH)/parse.c \
			  $(CON_PATH)/valid_check.c \
			  $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c \
			  $(UTL_PATH)/ft_atoi.c $(UTL_PATH)/ft_endcmp.c $(UTL_PATH)/ft_strcmp.c $(UTL_PATH)/ft_strlen.c \
			  $(UTL_PATH)/ft_itoa.c $(UTL_PATH)/ft_strrchr.c $(UTL_PATH)/lst_add_back.c $(UTL_PATH)/utils.c \
			  $(BNS_PATH)/score_bonus.c $(BNS_PATH)/minimap_bonus.c
BNS_OBJS	= $(BNS_SRCS:.c=.o)

CC			= gcc
CFLAGS		= -O3 -Wall -Wextra -Werror
MLXFLAGS	= -Lmlx -lm -Lmlx_beta -lmlx -framework OpenGL -framework AppKit
MMS			= libmlx.dylib
MLX			= m

.c.o:
		$(CC) $(CFLAGS) $(INCS) -c $< -o $(<:.c=.o)

$(NAME):	$(MLX) $(OBJS) $(MMS)
	mv $(MLX_PATH)/libmlx.a $(MLX_PATH)/libm.a
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) -L $(MLX_PATH) $(MLXFLAGS) $(OBJS)
	@echo $(NAME) : Created

$(MLX):
	@$(MAKE) -C mlx
	@$(MAKE) -C mlx_beta
	cp $(MMS_PATH)/$(MMS) .

$(BONUS):	$(MLX) $(BNS_OBJS) $(MMS)
	mv $(MLX_PATH)/libmlx.a $(MLX_PATH)/libm.a
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) -L $(MLX_PATH) $(MLXFLAGS) $(BNS_OBJS)
	@echo $(BONUS) : Created

all:	$(NAME)

bonus:	$(BONUS)

clean:
	@$(MAKE) -C mlx clean
	rm -f $(OBJS) $(BNS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS) $(MLX)

re:		fclean all

.PHONY: all clean fclean re
