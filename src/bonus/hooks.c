/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:20:42 by burei             #+#    #+#             */
/*   Updated: 2026/08/04 12:01:43 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	handle_rotation(int k, t_cub3d_env *env)
{
	float			to_rotate_deg;

	if (k == 65363)
		to_rotate_deg = ROT_SPEED;
	else
		to_rotate_deg = -ROT_SPEED;
	rotate_player(env, to_rotate_deg);
}

static void	set_movements_deltas(int k, double *dx,
	double *dy, t_cub3d_env *env)
{
	if (k == 'w')
	{
		*dx += env->map->direction.x * 0.1;
		*dy += env->map->direction.y * 0.1;
	}
	if (k == 's')
	{
		*dx -= env->map->direction.x * 0.1;
		*dy -= env->map->direction.y * 0.1;
	}
	if (k == 'd')
	{
		*dx += env->map->plane.x * 0.1;
		*dy += env->map->plane.y * 0.1;
	}
	if (k == 'a')
	{
		*dx -= env->map->plane.x * 0.1;
		*dy -= env->map->plane.y * 0.1;
	}
}

// static void	handle_movement(int k, t_cub3d_env *env)
// {
// 	double	dx;
// 	double	dy;
// 	double	buf_x;
// 	double	buf_y;

// 	dx = 0;
// 	dy = 0;
// 	set_movements_deltas(k, &dx, &dy, env);
// 	buf_x = ((dx > 0) - (dx < 0)) * 0.25;
// 	buf_y = ((dy > 0) - (dy < 0)) * 0.25;
// 	if (dx == 0)
// 		buf_x = 0;
// 	if (dy == 0)
// 		buf_y = 0;
// 	if (env->map->cells[(int)env->map->position.y]
// 		[(int)(env->map->position.x + dx + buf_x)] != 1)
// 		env->map->position.x += dx;
// 	if (env->map->cells[(int)(env->map->position.y + dy + buf_y)]
// 		[(int)env->map->position.x] != 1)
// 		env->map->position.y += dy;
// }

static void	handle_movement(int k, t_cub3d_env *env)
{
	double	dx;
	double	dy;
	double	buf_x;
	double	buf_y;

	dx = 0;
	dy = 0;
	set_movements_deltas(k, &dx, &dy, env);
	buf_x = ((dx > 0) - (dx < 0)) * 0.25;
	buf_y = ((dy > 0) - (dy < 0)) * 0.25;
	if (get_cell(env->map, (int)env->map->position.y,
			(int)(env->map->position.x + dx + buf_x)) == 0)
		env->map->position.x += dx;
	if (get_cell(env->map, (int)(env->map->position.y + dy + buf_y),
		(int)env->map->position.x) == 0)
		env->map->position.y += dy;
}

void	terminate(t_cub3d_env *env)
{
	clean_cub3d_env(env);
	exit(0);
}

int	key_hook(int k, t_cub3d_env *env)
{
	if (k == 65363 || k == 65361)
		handle_rotation(k, env);
	if (k == 'w' || k == 'a' || k == 's' || k == 'd')
		handle_movement(k, env);
	if (k == 65307)
		terminate(env);
	mlx_destroy_image(env->mlx, env->img.img);
	if (init_img(env))
		terminate(env);
	raycast(env);
	draw_minimap(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img.img, 0, 0);
	return (0);
}
