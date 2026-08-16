/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:47:48 by vfekete           #+#    #+#             */
/*   Updated: 2026/08/07 17:09:59 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	mouse_hook(int x, int y, t_cub3d_env *env)
{
	static int	old_x = 0;
	float		to_rotate;

	(void)y;
	if (old_x == 0)
		old_x = x;
	if (x == old_x)
		return ;
	else if (x < old_x)
		to_rotate = -ROT_SPEED / 2;
	else
		to_rotate = ROT_SPEED / 2;
	rotate_player(env, to_rotate);
	old_x = x;
	mlx_destroy_image(env->mlx, env->img.img);
	init_img(env);
	raycast(env);
	draw_minimap(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img.img, 0, 0);
}
