#include "cub3d.h"

static void	get_right_vector(t_game *game, double *rx, double *ry)
{
	*rx = game->dir_y;
	*ry = -game->dir_x;
}

static int	can_move(t_game *game, double nx, double ny)
{
	char	c;

	c = get_map_char(&game->cub, (int)ny, (int)nx);
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static double	margin(double d)
{
	if (d > 0)
		return (WALL_MARGIN);
	if (d < 0)
		return (-WALL_MARGIN);
	return (0);
}

static void	move_player(t_game *game, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = game->pos_x + dx * MOVE_SPEED;
	ny = game->pos_y + dy * MOVE_SPEED;
	if (can_move(game, nx + margin(dx), game->pos_y))
		game->pos_x = nx;
	if (can_move(game, game->pos_x, ny + margin(dy)))
		game->pos_y = ny;
}

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

void	update_movement(t_game *game)
{
	double	rx;
	double	ry;

	get_right_vector(game, &rx, &ry);
	if (game->keys.w)
		move_player(game, game->dir_x, game->dir_y);
	if (game->keys.s)
		move_player(game, -game->dir_x, -game->dir_y);
	if (game->keys.a)
		move_player(game, -rx, -ry);
	if (game->keys.d)
		move_player(game, rx, ry);
	if (game->keys.left)
		rotate_player(game, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(game, ROT_SPEED);
}
