#include "parsing.h"

int	match_id(char *line, char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (0);
	return (line[len] == '\0' || is_space(line[len]));
}

int	try_parse_config(t_map *map, char *line)
{
	if (match_id(line, "NO"))
		set_texture(map, "NO", line + 2);
	else if (match_id(line, "SO"))
		set_texture(map, "SO", line + 2);
	else if (match_id(line, "WE"))
		set_texture(map, "WE", line + 2);
	else if (match_id(line, "EA"))
		set_texture(map, "EA", line + 2);
	else if (match_id(line, "F"))
		parse_color(map, map->floor_color, &map->floor_found, line + 1);
	else if (match_id(line, "C"))
		parse_color(map, map->ceiling_color, &map->ceiling_found, line + 1);
	else
		return (0);
	return (1);
}

void	check_config(t_map *map)
{
	if (map->parse_error != NO_ERROR)
		return ;
	if (!map->north_tex.tex_path || !map->south_tex.tex_path
		|| !map->west_tex.tex_path || !map->east_tex.tex_path
		|| !map->floor_found || !map->ceiling_found)
		map->parse_error = MISSING_ASSETS;
}
