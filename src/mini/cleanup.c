#include "cub3d.h"

static void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img.img)
			mlx_destroy_image(game->mlx, game->tex[i].img.img);
		i++;
	}
}

static void	destroy_mlx_resources(t_game *game)
{
	destroy_textures(game);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	cleanup_and_exit(t_game *game)
{
	destroy_mlx_resources(game);
	free_cub(&game->cub);
	exit(EXIT_SUCCESS);
}

void	game_error(t_game *game, char *msg)
{
	printf("Error\n%s\n", msg);
	destroy_mlx_resources(game);
	free_cub(&game->cub);
	exit(EXIT_FAILURE);
}
