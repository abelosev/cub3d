/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 02:15:48 by vfekete           #+#    #+#             */
/*   Updated: 2026/07/07 02:17:47 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

bool	is_out_of_bounds(t_cub3d_env *env, int x, int y)
{
	return (y >= env->map->height || y < 0 || x >= env->map->widths[y]
		|| x < 0);
}
