#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strndup(const char *s, size_t n);
void	safe_free(char **p);
char	*get_next_line(int fd);

# define CUB_EXT ".cub"

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		is_set;
}	t_color;

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

typedef struct s_cub
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_color		floor;
	t_color		ceiling;
	char		**map;
	int			map_h;
	t_player	player;
	int			player_found;
	char		**raw_lines;
	int			raw_lines_total;
}	t_cub;

int		parse_cub(char *filename, t_cub *cub);
int		open_cub_file(char *filename, t_cub *cub);
t_list	*read_lines(int fd, t_cub *cub);
char	**list_to_array(t_list *lst);
void	strip_newline(char *line);
void	split_config_and_map(t_cub *cub, char **lines);

int		try_parse_config(t_cub *cub, char *line);
void	check_config_complete(t_cub *cub);
int		is_blank_line(char *line);

void	validate_map_chars(t_cub *cub);
void	find_player(t_cub *cub);
int		map_max_width(t_cub *cub);
char	get_map_char(t_cub *cub, int y, int x);

void	check_map_closed(t_cub *cub);

int		is_space_char(char c);
int		parse_int_strict(char *s, int *out);
char	*skip_spaces(char *s);

void	parse_error(t_cub *cub, char *msg);
void	free_cub(t_cub *cub);
void	init_cub(t_cub *cub);

#endif
