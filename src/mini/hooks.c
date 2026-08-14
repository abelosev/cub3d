#include "cub3d.h"

static void	set_key(t_game *game, int keycode, int value)
{
	if (keycode == KEY_W)
		game->keys.w = value;
	else if (keycode == KEY_A)
		game->keys.a = value;
	else if (keycode == KEY_S)
		game->keys.s = value;
	else if (keycode == KEY_D)
		game->keys.d = value;
	else if (keycode == KEY_LEFT)
		game->keys.left = value;
	else if (keycode == KEY_RIGHT)
		game->keys.right = value;
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		cleanup_and_exit(game);
	set_key(game, keycode, 1);
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	set_key(game, keycode, 0);
	return (0);
}

static int	close_window(t_game *game)
{
	cleanup_and_exit(game);
	return (0);
}

int	game_loop(t_game *game)
{
	update_movement(game);
	render_frame(game);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
