/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:29:47 by burei             #+#    #+#             */
/*   Updated: 2026/08/05 17:00:29 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_img(t_cub3d_env *env)
{
	env->img.img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!env->img.img)
		return (ft_putstr_fd("Error\nMLX img init error\n", 2), 1);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel,
			&env->img.line_length, &env->img.endian);
	if (!env->img.addr)
		return (ft_putstr_fd("Error\nMLX img init error\n", 2), 1);
	return (0);
}

static int	init_mlx_env(t_cub3d_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		return (ft_putstr_fd("Error\nMLX init error\n", 2), 1);
	env->mlx_win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!env->mlx_win)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		env->mlx = NULL;
		return (ft_putstr_fd("Error\nMLX init error\n", 2), 1);
	}
	return (0);
}

int	init_cub3d_env(char *map_path, t_cub3d_env *env)
{
	env->map = get_map(map_path);
	if (env->map->parse_error != NO_ERROR)
		return (1);
	if (init_mlx_env(env) || init_img(env))
		return (1);
	if (!load_textures(env))
	{
		if (env->map->parse_error == NO_ERROR)
			env->map->parse_error = TEXTURE_LOAD_FAIL;
		return (1);
	}
	set_hooks(env);
	return (0);
}
