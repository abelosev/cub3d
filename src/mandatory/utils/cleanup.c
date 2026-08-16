/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:59:44 by burei             #+#    #+#             */
/*   Updated: 2026/08/04 15:50:55 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	clean_textures(t_cub3d_env *e)
{
	if (e->map->north_tex.tex_path)
		free(e->map->north_tex.tex_path);
	if (e->map->south_tex.tex_path)
		free(e->map->south_tex.tex_path);
	if (e->map->east_tex.tex_path)
		free(e->map->east_tex.tex_path);
	if (e->map->west_tex.tex_path)
		free(e->map->west_tex.tex_path);
	if (e->map->north_tex.tex_loaded)
		mlx_destroy_image(e->mlx, e->map->north_tex.img_ptr);
	if (e->map->south_tex.tex_loaded)
		mlx_destroy_image(e->mlx, e->map->south_tex.img_ptr);
	if (e->map->east_tex.tex_loaded)
		mlx_destroy_image(e->mlx, e->map->east_tex.img_ptr);
	if (e->map->west_tex.tex_loaded)
		mlx_destroy_image(e->mlx, e->map->west_tex.img_ptr);
}

static void	clean_map_data(t_map *map)
{
	int	i;

	if (map == NULL)
		return ;
	if (map->widths != NULL)
		free(map->widths);
	if (map->cells != NULL)
	{
		i = -1;
		while (map->cells[++i])
			free(map->cells[i]);
		free(map->cells);
	}
	free(map);
}

void	clean_map_struct(t_cub3d_env *env)
{
	clean_textures(env);
	clean_map_data(env->map);
	env->map = NULL;
}

void	clean_mlx_env(t_cub3d_env *env)
{
	if (env->mlx && env->img.img)
		mlx_destroy_image(env->mlx, env->img.img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		mlx_loop_end(env->mlx);
		free(env->mlx);
	}
}

void	clean_cub3d_env(t_cub3d_env *env)
{
	clean_map_struct(env);
	clean_mlx_env(env);
	get_next_line(-1);
}
