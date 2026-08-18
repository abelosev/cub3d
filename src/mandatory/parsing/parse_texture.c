/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 14:21:37 by anbelose          #+#    #+#             */
/*   Updated: 2026/08/18 14:21:39 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_texture	*get_texture(t_map *map, char *id)
{
	if (!ft_strncmp(id, "NO", 3))
		return (&map->north_tex);
	if (!ft_strncmp(id, "SO", 3))
		return (&map->south_tex);
	if (!ft_strncmp(id, "WE", 3))
		return (&map->west_tex);
	return (&map->east_tex);
}

char	*get_path(t_map *map, char *rest)
{
	char	*path;
	char	*end;

	path = skip_spaces(rest);
	if (!*path)
	{
		map->parse_error = INVALID_TEXTURES;
		return (NULL);
	}
	end = path;
	while (*end && !is_space(*end))
		end++;
	if (*end)
	{
		*end = '\0';
		if (*skip_spaces(end + 1))
		{
			map->parse_error = INVALID_TEXTURES;
			return (NULL);
		}
	}
	return (path);
}

void	set_texture(t_map *map, char *id, char *rest)
{
	t_texture	*texture;
	char		*path;

	texture = get_texture(map, id);
	if (texture->tex_path)
	{
		map->parse_error = DOUBLE_TEXTURES;
		return ;
	}
	path = get_path(map, rest);
	if (!path)
		return ;
	texture->tex_path = ft_strdup(path);
	if (!texture->tex_path)
	{
		map->parse_error = MALLOC_ERROR;
		return ;
	}
}
