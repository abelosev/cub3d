#include "parsing.h"

static int	is_allowed_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	validate_map_chars(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (!is_allowed_char(cub->map[y][x]))
				parse_error(cub, "map contains an invalid character");
			x++;
		}
		y++;
	}
}

int	map_max_width(t_cub *cub)
{
	int	y;
	int	len;
	int	max;

	max = 0;
	y = 0;
	while (cub->map[y])
	{
		len = (int)ft_strlen(cub->map[y]);
		if (len > max)
			max = len;
		y++;
	}
	return (max);
}

/*
** Любые координаты за пределами реальных данных карты (отрицательные,
** за последней строкой, за длиной конкретной, возможно короткой,
** строки) трактуются точно так же, как явный пробел — оба варианта
** означают "открыто наружу" для проверки замкнутости.
*/
char	get_map_char(t_cub *cub, int y, int x)
{
	if (y < 0 || y >= cub->map_h)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(cub->map[y]))
		return (' ');
	return (cub->map[y][x]);
}

static int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	find_player(t_cub *cub)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (is_spawn_char(cub->map[y][x]))
			{
				count++;
				cub->player.x = x;
				cub->player.y = y;
				cub->player.dir = cub->map[y][x];
			}
			x++;
		}
		y++;
	}
	if (count == 0)
		parse_error(cub, "no player start position found on the map");
	if (count > 1)
		parse_error(cub, "multiple player start positions found on the map");
	cub->player_found = 1;
}