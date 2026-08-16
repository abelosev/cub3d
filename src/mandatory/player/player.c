/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:03:47 by burei             #+#    #+#             */
/*   Updated: 2026/08/07 16:16:31 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_dda(t_map *map, t_point *side_dists)
{
	map->lode.map_x = (int)map->position.x;
	map->lode.map_y = (int)map->position.y;
	map->lode.delta_dist_x = fabs(1 / map->lode.ray_x);
	map->lode.delta_dist_y = fabs(1 / map->lode.ray_y);
	map->lode.step_x = -(map->lode.ray_x < 0) + (map->lode.ray_x >= 0);
	map->lode.step_y = -(map->lode.ray_y < 0) + (map->lode.ray_y >= 0);
	if (map->lode.ray_x < 0)
		side_dists->x = (map->position.x - map->lode.map_x)
			* map->lode.delta_dist_x;
	else
		side_dists->x = (map->lode.map_x + 1.0 - map->position.x)
			* map->lode.delta_dist_x;
	if (map->lode.ray_y < 0)
		side_dists->y = (map->position.y - map->lode.map_y)
			* map->lode.delta_dist_y;
	else
		side_dists->y = (map->lode.map_y + 1.0 - map->position.y)
			* map->lode.delta_dist_y;
}

void	increase_side_dists(t_map *map, t_point *side_dists)
{
	if (side_dists->x < side_dists->y)
	{
		side_dists->x += map->lode.delta_dist_x;
		map->lode.map_x += map->lode.step_x;
		map->lode.side = 0;
	}
	else
	{
		side_dists->y += map->lode.delta_dist_y;
		map->lode.map_y += map->lode.step_y;
		map->lode.side = 1;
	}
}

int	run_dda(t_map *map, t_point *side_dists)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		increase_side_dists(map, side_dists);
		if (map->lode.map_y < 0 || map->lode.map_y >= map->height
			|| map->lode.map_x < 0
			|| map->lode.map_x >= map->widths[map->lode.map_y])
		{
			hit = 1;
			break ;
		}
		if (map->cells[map->lode.map_y][map->lode.map_x] == 1)
			hit = 1;
	}
	return (map->lode.side);
}

void	rotate_player(t_cub3d_env *env, float deg)
{
	env->map->direction = rotate_point(env->map->direction, deg);
	env->map->plane = rotate_point(env->map->plane, deg);
}

void	raycast(t_cub3d_env *env)
{
	int		x;
	double	cam_x;
	t_point	sides;
	double	dist;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		cam_x = 2 * x / ((double)WIN_WIDTH) - 1;
		env->map->lode.ray_x = env->map->direction.x + env->map->plane.x
			* cam_x;
		env->map->lode.ray_y = env->map->direction.y + env->map->plane.y
			* cam_x;
		init_dda(env->map, &sides);
		run_dda(env->map, &sides);
		get_wall_data(env->map, &sides, &dist);
		draw_vertical_strip(x, env);
	}
}
