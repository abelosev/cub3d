SRCS_DEFAULT := ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_lstnew.c \
	ft_lstadd_back.c \
	ft_lstsize.c

SRCS_BONUS := ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c
NAME := libft.a
OBJ_DEFAULT := $(SRCS_DEFAULT:.c=.o)
OBJ_BONUS := $(SRCS_BONUS:.c=.o)
CC := cc -Wall -Wextra -Werror -I.

all : $(NAME)

$(NAME) : $(OBJ_DEFAULT)
	ar -rc $(NAME) $(OBJ_DEFAULT)

clean :
	rm -f ft_*.o

fclean : clean
	rm -f ./libft.a

bonus : $(NAME) $(OBJ_BONUS)
	ar r $(NAME) $(OBJ_BONUS)

re : fclean $(NAME)

.PHONY : clean fclean bonus re
