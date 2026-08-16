/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:22:15 by burei             #+#    #+#             */
/*   Updated: 2026/08/04 12:23:40 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

/* MINIMAP */
void	draw_minimap(t_cub3d_env *env);
bool	is_out_of_bounds(t_cub3d_env *env, int x, int y);

/* Mous hook */
void	mouse_hook(int x, int y, t_cub3d_env *env);

#endif