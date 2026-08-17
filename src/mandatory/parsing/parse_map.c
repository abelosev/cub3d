#include "parsing.h"

int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_line(t_map *map, char *line, int *player_count)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!is_allowed(line[x]))
		{
			map->parse_error = INVALID_CHAR;
			return (0);
		}
		if (is_player(line[x]))
			(*player_count)++;
		x++;
	}
	return (1);
}

int	validate_map_lines(t_map *map, char **lines,
	int start, int height)
{
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < height)
	{
		if (is_blank_line(lines[start + y]))
			return (map->parse_error = MAP_SPLIT, 0);
		if (!validate_line(map, lines[start + y], &player_count))
			return (0);
		y++;
	}
	if (player_count == 0)
		return (map->parse_error = NO_PLAYER, 0);
	if (player_count > 1)
		return (map->parse_error = DOUBLE_PLAYER, 0);
	return (1);
}

void	build_map(t_map *map, char **lines, int start, int total)
{
	int	height;

	height = total - start;
	if (height <= 0)
	{
		map->parse_error = INVALID_CHAR;
		return ;
	}
	if (!validate_map_lines(map, lines, start, height))
		return ;
	if (!allocate_map(map, height))
		return ;
	if (!fill_map(map, lines, start, height))
		return ;
}
