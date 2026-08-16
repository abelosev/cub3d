#include "../../../includes/parsing.h"

void	init_empty_texts(t_map	*map)
{
	map->floor_color[0] = -1;
	map->floor_color[1] = -1;
	map->floor_color[2] = -1;
	map->ceiling_color[0] = -1;
	map->ceiling_color[1] = -1;
	map->ceiling_color[2] = -1;
	map->ceiling_found = false;
	map->floor_found = false;
	map->north_tex.tex_path = NULL;
	map->south_tex.tex_path = NULL;
	map->east_tex.tex_path = NULL;
	map->west_tex.tex_path = NULL;
	map->north_tex.img_ptr = NULL;
	map->south_tex.img_ptr = NULL;
	map->east_tex.img_ptr = NULL;
	map->west_tex.img_ptr = NULL;
	map->north_tex.tex_loaded = false;
	map->south_tex.tex_loaded = false;
	map->east_tex.tex_loaded = false;
	map->west_tex.tex_loaded = false;
	map->curr_tex = NULL;
}

void	init_empty_map(t_map	*map)
{
	map->parse_error = NO_ERROR;
	map->position.x = 0;
	map->position.y = 0;
	map->direction.x = 0;
	map->direction.y = 0;
	map->plane.x = 0;
	map->plane.y = 0;
	map->height = 0;
	map->widths = NULL;
	map->cells = NULL;
	init_empty_texts(map);
}
