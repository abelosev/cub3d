/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:13:09 by burei             #+#    #+#             */
/*   Updated: 2026/07/07 12:12:17 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	set_default_player_angle(int x, int y, char direction, t_map *map)
{
	map->direction.x = 0;
	map->direction.y = 0;
	map->position.x = x + 0.5;
	map->position.y = y + 0.5;
	map->direction.x += (direction == 'E') + (direction == 'W') * -1;
	map->direction.y += (direction == 'S') + (direction == 'N') * -1;
}

void	set_default_player_plane(t_map *map)
{
	if (map->direction.x == 1)
	{
		map->plane.x = 0;
		map->plane.y = 0.66;
	}
	else if (map->direction.x == -1)
	{
		map->plane.x = 0;
		map->plane.y = -0.66;
	}
	else if (map->direction.y == 1)
	{
		map->plane.x = -0.66;
		map->plane.y = 0;
	}
	else if (map->direction.y == -1)
	{
		map->plane.x = 0.66;
		map->plane.y = 0;
	}
}

void	init_player(int y, int x, char direction, t_map *map)
{
	set_default_player_angle(x, y, direction, map);
	set_default_player_plane(map);
}
