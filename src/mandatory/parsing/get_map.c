/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:27:09 by burei             #+#    #+#             */
/*   Updated: 2026/08/16                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int	count_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

int	find_map_end(char **lines, int start, int total)
{
	while (total > start && is_blank_line(lines[total - 1]))
		total--;
	return (total);
}

int	find_map_start(t_map *map, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_blank_line(lines[i]))
			i++;
		else if (try_parse_config(map, lines[i]))
		{
			if (map->parse_error != NO_ERROR)
				return (-1);
			i++;
		}
		else
			break ;
	}
	check_config(map);
	if (map->parse_error != NO_ERROR)
		return (-1);
	if (!lines[i])
	{
		map->parse_error = INVALID_CHAR;
		return (-1);
	}
	return (i);
}

void	parse_map(char *map_path, t_map *map)
{
	int		fd;
	int		map_start;
	int		total;
	t_list	*lst;
	char	**lines;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		map->parse_error = OPEN_FAIL;
		return ;
	}
	lst = read_lines(fd, map);
	close(fd);
	if (map->parse_error != NO_ERROR)
		return ;
	lines = list_to_array(lst, map);
	if (!lines)
		return ;
	total = count_lines(lines);
	map_start = find_map_start(map, lines);
	if (map_start >= 0)
	{
		total = find_map_end(lines, map_start, total);
		build_map(map, lines, map_start, total);
	}
	free_lines(lines);
}

t_map	*get_map(char *map_path)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_putstr_fd("Error\nMalloc error\n", 2);
		exit(EXIT_FAILURE);
	}
	init_empty_map(map);
	parse_map(map_path, map);
	if (map->parse_error != NO_ERROR)
		return (map);
	validate_closed(map);
	return (map);
}
