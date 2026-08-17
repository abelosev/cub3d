/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:17:54 by burei             #+#    #+#             */
/*   Updated: 2026/08/07 16:48:21 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_data(t_map *map, t_point *sides, double *distance)
{
	if (map->lode.side == 0)
		*distance = sides->x - map->lode.delta_dist_x;
	else
		*distance = sides->y - map->lode.delta_dist_y;
	if (*distance < 0.1)
		*distance = 0.1;
	map->lode.line_height = (int)(WIN_HEIGHT / *distance);
	if (map->lode.side == 0)
		map->lode.wall_x = map->position.y + *distance * map->lode.ray_y;
	else
		map->lode.wall_x = map->position.x + *distance * map->lode.ray_x;
	map->lode.wall_x -= floor(map->lode.wall_x);
}

void	set_current_texture(t_map *map)
{
	if (map->lode.side == 0)
	{
		if (map->lode.ray_x > 0)
			map->curr_tex = &map->east_tex;
		else
			map->curr_tex = &map->west_tex;
	}
	else
	{
		if (map->lode.ray_y > 0)
			map->curr_tex = &map->south_tex;
		else
			map->curr_tex = &map->north_tex;
	}
}

void	draw_wall(int x, int start_y, t_cub3d_env *e)
{
	int	offset;
	int	color;
	int	tex_x;
	int	tex_y;

	tex_x = (int)(e->map->lode.wall_x * e->map->curr_tex->width);
	if ((e->map->lode.side == 0 && e->map->lode.ray_x < 0)
		|| (e->map->lode.side == 1 && e->map->lode.ray_y > 0))
		tex_x = e->map->curr_tex->width - tex_x - 1;
	e->map->lode.d = start_y * 256 - WIN_HEIGHT * 128
		+ e->map->lode.line_height * 128;
	tex_y = (e->map->lode.d * e->map->curr_tex->height)
		/ e->map->lode.line_height / 256;
	if (tex_x < 0 || tex_x >= e->map->curr_tex->width || tex_y < 0
		|| tex_y >= e->map->curr_tex->height)
		return ;
	offset = tex_y * e->map->curr_tex->line_len + tex_x
		* (e->map->curr_tex->bpp / 8);
	if (offset < 0 || offset + 3 >= e->map->curr_tex->height
		* e->map->curr_tex->line_len)
		return ;
	color = *(int *)(e->map->curr_tex->data + offset);
	my_mlx_pixel_put(&e->img, x, start_y, color);
}

// void	draw_vertical_strip(int x, t_cub3d_env *e)
// {
// 	int	y;
// 	int	start_y;
// 	int	end_y;

// 	start_y = -e->map->lode.line_height / 2 + WIN_HEIGHT / 2;
// 	end_y = e->map->lode.line_height / 2 + WIN_HEIGHT / 2;
// 	y = -1;
// 	if (start_y < 0)
// 		start_y = 0;
// 	if (end_y > WIN_HEIGHT)
// 		end_y = WIN_HEIGHT - 1;
// 	set_current_texture(e->map);
// 	while (++y < start_y)
// 		my_mlx_pixel_put(&(e->img), x, y,
// 			rgba_to_int(e->map->ceiling_color[0],
// 				e->map->ceiling_color[1],
// 				e->map->ceiling_color[2], 0));
// 	while (++y < end_y)
// 		draw_wall(x, y, e);
// 	while (++y < WIN_HEIGHT)
// 		my_mlx_pixel_put(&(e->img), x, y,
// 			rgba_to_int(e->map->floor_color[0],
// 				e->map->floor_color[1],
// 				e->map->floor_color[2], 0));
// }

void	draw_background(int x, int y, t_cub3d_env *e, int ceiling)
{
	int	color;

	if (ceiling)
		color = rgba_to_int(e->map->ceiling_color[0],
				e->map->ceiling_color[1],
				e->map->ceiling_color[2], 0);
	else
		color = rgba_to_int(e->map->floor_color[0],
				e->map->floor_color[1],
				e->map->floor_color[2], 0);
	my_mlx_pixel_put(&e->img, x, y, color);
}

void	draw_vertical_strip(int x, t_cub3d_env *e)
{
	int	y;
	int	start_y;
	int	end_y;

	start_y = -e->map->lode.line_height / 2 + WIN_HEIGHT / 2;
	end_y = e->map->lode.line_height / 2 + WIN_HEIGHT / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= WIN_HEIGHT)
		end_y = WIN_HEIGHT - 1;
	set_current_texture(e->map);
	y = 0;
	while (y < start_y)
		draw_background(x, y++, e, 1);
	while (y <= end_y)
		draw_wall(x, y++, e);
	while (y < WIN_HEIGHT)
		draw_background(x, y++, e, 0);
}
