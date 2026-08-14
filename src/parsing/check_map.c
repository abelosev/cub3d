#include "parsing.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	check_cell_closed(t_cub *cub, int y, int x)
{
	char	c;

	c = get_map_char(cub, y, x);
	if (!is_walkable(c))
		return ;
	if (get_map_char(cub, y - 1, x) == ' '
		|| get_map_char(cub, y + 1, x) == ' '
		|| get_map_char(cub, y, x - 1) == ' '
		|| get_map_char(cub, y, x + 1) == ' ')
		parse_error(cub, "map is not closed by walls");
}

void	check_map_closed(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (x < (int)ft_strlen(cub->map[y]))
		{
			check_cell_closed(cub, y, x);
			x++;
		}
		y++;
	}
}
