/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:22:15 by burei             #+#    #+#             */
/*   Updated: 2026/08/10 08:48:57 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../src/gnl/get_next_line.h"
# include "parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_HEIGHT 768
# define WIN_WIDTH 1024
# define GRID_SIZE 25
# define X_MARGIN 150
# define Y_MARGIN 50
# define M_PI 3.14159265358979323846
# define ROT_SPEED 3.5

typedef struct s_point_int
{
	int				x;
	int				y;
}					t_point_int;

typedef struct s_line_draw
{
	int				dx;
	int				dy;
	int				steps;
	float			x_inc;
	float			y_inc;
	float			x;
	float			y;
}					t_line_draw;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_cub3d_env
{
	t_map			*map;
	void			*mlx;
	void			*mlx_win;
	t_data			img;
}					t_cub3d_env;

/* INIT */

int					init_cub3d_env(char *map_path, t_cub3d_env *env);
int					init_img(t_cub3d_env *env);
void				init_player(int y, int x, char direction, t_map *map);
bool				load_textures(t_cub3d_env *e);

/* DRAWING TO SCREEN */

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				draw_line(t_data *img, t_point p1, t_point p2, int rgba[4]);
int					rgba_to_int(unsigned char r, unsigned char g,
						unsigned char b, unsigned char a);

/* MAP */

t_map				*get_map(char *map_filepath);

/* UTILS */

char				*gnl_no_nl(int fd);
char				*gnl_no_nl_no_ws(int fd);
void				ft_free_split(char **split);
int					skip_whitespaces_tabs(char *str);
t_point				add_points(t_point p1, t_point p2);
t_point				rotate_point(t_point p, float angleDeg);

/* CLEANUP */

void				clean_map_struct(t_cub3d_env *env);
void				clean_cub3d_env(t_cub3d_env *env);
void				clean_mlx_env(t_cub3d_env *env);

/* RAY GEOMETRY */

void				raycast(t_cub3d_env *env);
void				draw_vertical_strip(int x, t_cub3d_env *e);
void				get_wall_data(t_map *map, t_point *sides, double *distance);

/* HOOKS */

void				set_hooks(t_cub3d_env *env);
int					key_hook(int keycode, t_cub3d_env *env);
void				rotate_player(t_cub3d_env *env, float deg);
void				terminate(t_cub3d_env *env);

#endif