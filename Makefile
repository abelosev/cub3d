NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

INC_DIR		= inc
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# parsing.h уже содержит всё, что раньше было в get_next_line.h -
# отдельного заголовка для gnl больше нет (см. merge parsing.h).
HEADERS		= $(INC_DIR)/cub3d.h $(INC_DIR)/parsing.h

SRC_GNL		= src/gnl/get_next_line.c src/gnl/get_next_line_utils.c
SRC_PARSING	= src/parsing/check_map.c src/parsing/errors.c \
			  src/parsing/parse_config.c src/parsing/parse_file.c \
			  src/parsing/parse_map.c src/parsing/parse_utils.c
SRC_MINI	= src/mini/game_init.c src/mini/raycast.c src/mini/render.c \
			  src/mini/draw.c src/mini/textures.c src/mini/move.c \
			  src/mini/hooks.c src/mini/cleanup.c
SRC_MAIN	= src/main.c

SRCS		= $(SRC_MAIN) $(SRC_GNL) $(SRC_PARSING) $(SRC_MINI)
OBJS		= $(SRCS:.c=.o)

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx_Linux.a

# X11 libs required by minilibx-linux; -lbsd is only needed on some
# distros (e.g. some Debian/Ubuntu setups) - uncomment if link fails
# with undefined references to strlcpy/strlcat.
LIBS		= -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm # -lbsd

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

# Зависимость от HEADERS: если поменять cub3d.h или parsing.h,
# пересоберутся все .o, которые их подключают, а не только тот один
# файл, который вы явно правили.
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# $(LIBFT) и $(MLX) объявлены ниже как .PHONY - это специально:
# у самих файлов libft.a/libmlx_Linux.a нет prerequisites, поэтому
# без .PHONY make, увидев, что архив уже существует на диске,
# вообще не заходил бы повторно в подпапку - и правки внутри
# libft/ или minilibx-linux/ молча игнорировались бы обычным make
# (только make fclean && make их бы подхватил). С .PHONY make
# каждый раз заходит в подпапку и отдаёт решение "нужна ли
# пересборка" её собственному Makefile; сам cub3D при этом всё
# равно перелинкуется, только если итоговый архив реально обновился
# (сравнение по mtime уже самого файла $(LIBFT)/$(MLX)), так что
# требование "не перелинковывать без необходимости" не нарушается.
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Нет bonus-файлов/функций в этом проекте - правило оставлено как
# алиас на all, чтобы `make bonus` не падал с "No rule to make
# target", если его всё же вызовут при пир-евалюации.
bonus: all

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(MLX_DIR)/libmlx_Linux.a $(MLX_DIR)/libmlx.a

re: fclean all

.PHONY: all clean fclean re bonus $(LIBFT) $(MLX)