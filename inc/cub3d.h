#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "parsing.h"
# include "../minilibx-linux/mlx.h"

# define WIN_WIDTH		1024
# define WIN_HEIGHT		768
# define PLANE_LEN		0.66
# define MOVE_SPEED		0.05
# define ROT_SPEED		0.045
# define WALL_MARGIN	0.2

# define KEY_ESC		65307
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_LEFT		65361
# define KEY_RIGHT		65363

# define TEX_NO	0
# define TEX_SO	1
# define TEX_WE	2
# define TEX_EA	3

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_tex
{
	t_img	img;
}	t_tex;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	camera_x;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_x;
	int		tex_id;
}	t_ray;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	t_cub	cub;
	void	*mlx;
	void	*win;
	t_img	screen;
	t_tex	tex[4];
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	t_keys	keys;
}	t_game;

void	init_game(t_game *game, t_cub *cub);

void	cast_ray(t_game *game, int x, t_ray *ray);

void	put_pixel(t_img *img, int x, int y, int color);
int		get_color(t_color *c);
void	render_frame(t_game *game);

void	draw_column(t_game *game, int x, t_ray *ray);

void	load_all_textures(t_game *game);
int		get_tex_pixel(t_tex *tex, int x, int y);

void	update_movement(t_game *game);

void	setup_hooks(t_game *game);
int		game_loop(t_game *game);

void	cleanup_and_exit(t_game *game);
void	game_error(t_game *game, char *msg);

#endif