/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:30:22 by burei             #+#    #+#             */
/*   Updated: 2026/07/12 11:41:46 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool	check_texture_file_open(t_texture *text)
{
	int		fd;
	bool	ret;

	fd = open(text->tex_path, O_RDONLY);
	ret = (fd != -1);
	if (fd != -1)
		close(fd);
	return (ret);
}

bool	load_texture(t_cub3d_env *e, t_texture *text)
{
	if (!check_texture_file_open(text))
		return (false);
	text->img_ptr = mlx_xpm_file_to_image(e->mlx,
			text->tex_path,
			&text->width,
			&text->height);
	if (text->img_ptr == NULL)
		return (false);
	text->data = mlx_get_data_addr(text->img_ptr,
			&text->bpp,
			&text->line_len,
			&text->endian);
	text->tex_loaded = true;
	return (true);
}

bool	load_textures(t_cub3d_env *e)
{
	if (!load_texture(e, &e->map->north_tex)
		|| !load_texture(e, &e->map->south_tex)
		|| !load_texture(e, &e->map->east_tex)
		|| !load_texture(e, &e->map->west_tex))
		return (false);
	return (true);
}
