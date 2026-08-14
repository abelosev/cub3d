#include "cub3d.h"

static void	set_direction(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
		game->plane_x = PLANE_LEN;
		game->plane_y = 0;
	}
	else if (dir == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
		game->plane_x = -PLANE_LEN;
		game->plane_y = 0;
	}
	else if (dir == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = PLANE_LEN;
	}
	else
	{
		game->dir_x = -1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = -PLANE_LEN;
	}
}

static void	init_player(t_game *game)
{
	game->pos_x = game->cub.player.x + 0.5;
	game->pos_y = game->cub.player.y + 0.5;
	set_direction(game, game->cub.player.dir);
}

static void	init_image(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen.img)
		parse_error(&game->cub, "mlx: failed to create screen image");
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bpp,
			&game->screen.line_len,
			&game->screen.endian);
	game->screen.width = WIN_WIDTH;
	game->screen.height = WIN_HEIGHT;
}

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		game_error(game, "mlx: failed to initialize");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		game_error(game, "mlx: failed to create window");
}

void	init_game(t_game *game, t_cub *cub)
{
	ft_bzero(game, sizeof(t_game));
	game->cub = *cub;
	init_mlx(game);
	init_image(game);
	load_all_textures(game);
	init_player(game);
}
