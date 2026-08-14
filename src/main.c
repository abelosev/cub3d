#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nusage: ./cub3D <map.cub>\n");
		return (EXIT_FAILURE);
	}
	parse_cub(argv[1], &cub);
	init_game(&game, &cub);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
