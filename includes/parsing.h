#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "../src/gnl/get_next_line.h"
# include <stdbool.h>
# include <stddef.h>

/* PARSING ERRORS */

# define NO_PLAYER_ERR "Map does not have a player\n"
# define DOUBLE_PLAYER_ERR "Map has two or more players\n"
# define INVALID_CHAR_ERR "Map contains forbidden character\n"
# define INVALID_TEXTURES_ERR "Couldn't load one or more of map textures\n"
# define DOUBLE_TEXTURES_ERR "One or more textures are defined twice\n"
# define MAP_SPLIT_ERR "Map is split by a newline\n"
# define WRONG_RGB_ERR "RGB values for floor or ceiling is invalid\n"
# define DOUBLE_RGB_ERR "RGB values for floor or ceiling is defined twice\n"
# define MISSING_ASSETS_ERR "Map is missing some assets\n"
# define UNEXPECTED_ASSETS_ERR "Map contains some unknown asset\n"
# define OPEN_FAIL_ERR "Failed to open map file\n"
# define TEXTURE_LOAD_FAIL_ERR "Failed to load one or more textures\n"
# define MAP_NOT_CLOSE_ERR "Map is not enclosed by walls\n"
# define INVALID_WHITESPACE_ERR "Invalid whitespace found in map\n"
# define MALLOC_ERROR_MSG "Malloc error\n"

typedef enum e_parse_errors
{
	NO_ERROR,
	NO_PLAYER,
	DOUBLE_PLAYER,
	INVALID_CHAR,
	INVALID_TEXTURES,
	DOUBLE_TEXTURES,
	MAP_SPLIT,
	WRONG_RGB,
	DOUBLE_RGB,
	MISSING_ASSETS,
	UNEXPECTED_ASSETS,
	OPEN_FAIL,
	TEXTURE_LOAD_FAIL,
	MAP_NOT_CLOSE_FAIL,
	INVALID_WHITESPACE,
	MALLOC_ERROR
}	t_parse_errors;

/* SHARED MAP STRUCTURES */

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_texture
{
	void			*img_ptr;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
	char			*tex_path;
	bool			tex_loaded;
}					t_texture;

typedef struct s_lode_raycast
{
	double			ray_x;
	double			ray_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	double			wall_x;
	int				d;
}					t_lode_raycast;

typedef struct s_map
{
	int				floor_color[3];
	int				ceiling_color[3];
	bool			floor_found;
	bool			ceiling_found;
	t_parse_errors	parse_error;
	t_point			position;
	t_point			direction;
	t_point			plane;
	int				**cells;
	int				*widths;
	int				height;
	t_lode_raycast	lode;
	t_texture		north_tex;
	t_texture		south_tex;
	t_texture		east_tex;
	t_texture		west_tex;
	t_texture		*curr_tex;
}					t_map;

/* GET MAP */

void				init_empty_map(t_map *map);
t_map				*get_map(char *map_path);

/* PARSE FILE */

t_list				*read_lines(int fd, t_map *map);
char				**list_to_array(t_list *lst, t_map *map);
void				free_lines(char **lines);

/* PARSE CONFIG */

void				parse_color(t_map *map, int *color, bool *found,
						char *rest);
void				set_texture(t_map *map, char *id, char *rest);
int					try_parse_config(t_map *map, char *line);
void				check_config(t_map *map);

/* PARSE MAP */

void				build_map(t_map *map, char **lines, int start, int total);
int					get_cell(t_map *map, int y, int x);
int					allocate_map(t_map *map, int height);
int					fill_map(t_map *map, char **lines, int start, int height);

/* MAP VALIDATION */

void				validate_closed(t_map *map);

/* PARSE UTILS */

int					is_space(char c);
char				*skip_spaces(char *s);
int					parse_int(char *s, int *out);
int					is_blank_line(char *line);
void				strip_newline(char *line);

/* PARSER DEPENDENCIES */

void				init_player(int y, int x, char direction, t_map *map);
void				ft_free_split(char **split);

#endif