#include "../../../includes/parsing.h"

int	allocate_map(t_map *map, int height)
{
	map->height = height;
	map->widths = ft_calloc(height, sizeof(int));
	map->cells = ft_calloc(height + 1, sizeof(int *));
	if (!map->widths || !map->cells)
	{
		map->parse_error = MALLOC_ERROR;
		return (0);
	}
	return (1);
}

void	set_cell(t_map *map, char c, int x, int y)
{
	if (c == '0')
		map->cells[y][x] = 0;
	else if (c == '1')
		map->cells[y][x] = 1;
	else if (c == ' ')
		map->cells[y][x] = -1;
	else
	{
		init_player(y, x, c, map);
		map->cells[y][x] = 0;
	}
}

int	fill_line(t_map *map, char *line, int y)
{
	int	x;

	map->widths[y] = ft_strlen(line);
	map->cells[y] = malloc(sizeof(int) * map->widths[y]);
	if (!map->cells[y])
	{
		map->parse_error = MALLOC_ERROR;
		return (0);
	}
	x = 0;
	while (line[x])
	{
		set_cell(map, line[x], x, y);
		x++;
	}
	return (1);
}

int	fill_map(t_map *map, char **lines, int start, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		if (!fill_line(map, lines[start + y], y))
		// free + error malloc
			return (0);
		y++;
	}
	return (1);
}
