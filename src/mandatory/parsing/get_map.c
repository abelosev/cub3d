/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 14:19:33 by anbelose          #+#    #+#             */
/*   Updated: 2026/08/18 14:19:40 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
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

char	**load_map_lines(char *map_path, t_map *map)
{
	int		fd;
	t_list	*lst;
	char	**lines;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		map->parse_error = OPEN_FAIL;
		return (NULL);
	}
	lst = read_lines(fd, map);
	close(fd);
	if (map->parse_error != NO_ERROR)
		return (NULL);
	lines = list_to_array(lst, map);
	return (lines);
}

void	parse_map(char *map_path, t_map *map)
{
	int		map_start;
	int		total;
	char	**lines;

	lines = load_map_lines(map_path, map);
	if (!lines)
		return ;
	total = count_lines(lines);
	map_start = find_map_start(map, lines);
	if (map_start >= 0)
	{
		while (total > map_start && is_blank_line(lines[total - 1]))
			total--;
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
