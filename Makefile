NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=gnu17

INC_DIR		= inc
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

MLX_REPO	= https://github.com/42paris/minilibx-linux.git
MLX_BRANCH	= fedora

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

HEADERS		= $(INC_DIR)/cub3d.h \
			  $(INC_DIR)/parsing.h

SRC_GNL		= src/gnl/get_next_line.c \
			  src/gnl/get_next_line_utils.c

SRC_PARSING	= src/parsing/check_map.c \
			  src/parsing/errors.c \
			  src/parsing/parse_config.c \
			  src/parsing/parse_file.c \
			  src/parsing/parse_map.c \
			  src/parsing/parse_utils.c

SRC_MINI	= src/mini/game_init.c \
			  src/mini/raycast.c \
			  src/mini/render.c \
			  src/mini/draw.c \
			  src/mini/textures.c \
			  src/mini/move.c \
			  src/mini/hooks.c \
			  src/mini/cleanup.c

SRC_MAIN	= src/main.c

SRCS		= $(SRC_MAIN) \
			  $(SRC_GNL) \
			  $(SRC_PARSING) \
			  $(SRC_MINI)

OBJS		= $(SRCS:.c=.o)

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx_Linux.a
MLX_MAKEFILE	= $(MLX_DIR)/Makefile

LIBS		= -L$(MLX_DIR) \
			  -lmlx_Linux \
			  -lXext \
			  -lX11 \
			  -lm \
			  -lbsd

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_MAKEFILE):
	rm -rf $(MLX_DIR)
	git clone --branch $(MLX_BRANCH) --single-branch $(MLX_REPO) $(MLX_DIR)

$(MLX): $(MLX_MAKEFILE)
	$(MAKE) -C $(MLX_DIR)

bonus: all

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -f "$(MLX_MAKEFILE)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re bonus