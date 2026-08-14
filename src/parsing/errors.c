#include "parsing.h"

void	init_cub(t_cub *cub)
{
	cub->no_path = NULL;
	cub->so_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->floor.is_set = 0;
	cub->ceiling.is_set = 0;
	cub->map = NULL;
	cub->map_h = 0;
	cub->raw_lines = NULL;
	cub->raw_lines_total = 0;
	cub->player_found = 0;
	cub->player.x = -1;
	cub->player.y = -1;
	cub->player.dir = 0;
}

void	free_cub(t_cub *cub)
{
	int	i;

	if (cub->no_path)
		free(cub->no_path);
	if (cub->so_path)
		free(cub->so_path);
	if (cub->we_path)
		free(cub->we_path);
	if (cub->ea_path)
		free(cub->ea_path);
	if (cub->map)
	{
		i = 0;
		while (cub->map[i])
			free(cub->map[i++]);
		free(cub->map);
	}
	if (cub->raw_lines)
	{
		i = 0;
		while (i < cub->raw_lines_total)
		{
			if (cub->raw_lines[i])
				free(cub->raw_lines[i]);
			i++;
		}
		free(cub->raw_lines);
	}
	init_cub(cub);
}


void	parse_error(t_cub *cub, char *msg)
{
	printf("Error\n%s\n", msg);
	free_cub(cub);
	exit(EXIT_FAILURE);
}