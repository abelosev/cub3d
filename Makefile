NAME   		:= cub3D
NAME_BONUS	:= cub3D_bonus
CFLAGS 		:= -Wall -Wextra -Werror
CC			:= cc

### DEPENDENCIES ###
LIBMLX 		:= ./mlx_linux/libmlx_Linux.a
LIBFT  		:= ./libft/libft.a

### SOURCES ###
GNL_SRCS			:= 	src/gnl/get_next_line_utils.c \
						src/gnl/get_next_line.c

MANDATORY_MAIN := src/mandatory/main.c
BONUS_MAIN := src/bonus/main_bonus.c

MANDATORY_EXCLUSIVE := src/mandatory/init/hooks.c

SHARED_SRCS		:= 		src/mandatory/parsing/get_map.c \
						src/mandatory/parsing/init_map.c \
						src/mandatory/parsing/check_map.c \
						src/mandatory/parsing/parse_config.c \
						src/mandatory/parsing/parse_color.c \
						src/mandatory/parsing/parse_texture.c \
						src/mandatory/parsing/parse_file.c \
						src/mandatory/parsing/parse_map.c \
						src/mandatory/parsing/fill_map.c \
						src/mandatory/parsing/parse_utils.c \
						src/mandatory/init/init_player.c \
						src/mandatory/init/init.c \
						src/mandatory/init/texture_init.c \
						src/mandatory/display/draw.c \
						src/mandatory/player/player.c \
						src/mandatory/player/textures.c \
						src/mandatory/utils/cleanup_2.c \
						src/mandatory/utils/cleanup.c \
						src/mandatory/utils/utils.c \
						$(GNL_SRCS) \

BONUS_SRCS			:=	src/bonus/mouse.c \
						src/bonus/minimap.c \
						src/bonus/minimap_utils.c \
						src/bonus/hooks.c \

OBJS_MANDATORY 		:= $(MANDATORY_MAIN:.c=.o) $(SHARED_SRCS:.c=.o) $(MANDATORY_EXCLUSIVE:.c=.o)
OBJS_BONUS 			:= $(BONUS_MAIN:.c=.o) $(SHARED_SRCS:.c=.o) $(BONUS_SRCS:.c=.o)

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

$(LIBMLX) : ./mlx_linux
	cd mlx_linux; make;

$(NAME) : $(LIBFT) $(LIBMLX) $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(LIBFT) -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -o $(NAME)

$(LIBFT) :
	cd libft; make bonus;

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(LIBFT) $(LIBMLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -o $(NAME_BONUS)

clean :
	cd libft; make clean;
	rm -f $(OBJS_MANDATORY)
	rm -f $(OBJS_BONUS)

fclean : clean
	rm -f libft/libft.a
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -rf mlx_linux

mlx_linux :
	git clone https://github.com/42paris/minilibx-linux.git mlx_linux;

re : fclean all

.PHONY : all clean fclean re bonus