#include "parsing.h"

int	get_cell(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (-1);
	if (x < 0 || x >= map->widths[y])
		return (-1);
	return (map->cells[y][x]);
}

int	cell_closed(t_map *map, int y, int x)
{
	if (map->cells[y][x] != 0)
		return (1);
	if (get_cell(map, y - 1, x) == -1
		|| get_cell(map, y + 1, x) == -1
		|| get_cell(map, y, x - 1) == -1
		|| get_cell(map, y, x + 1) == -1)
		return (0);
	return (1);
}

void	validate_closed(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->widths[y])
		{
			if (!cell_closed(map, y, x))
			{
				map->parse_error = MAP_NOT_CLOSE_FAIL;
				return ;
			}
			x++;
		}
		y++;
	}
}
