/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 14:20:41 by anbelose          #+#    #+#             */
/*   Updated: 2026/08/18 14:20:42 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_commas(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

int	parse_rgb(char *token, int *out)
{
	char	*start;
	char	*end;

	start = skip_spaces(token);
	end = start + ft_strlen(start);
	while (end > start && is_space(end[-1]))
		end--;
	*end = '\0';
	return (parse_int(start, out));
}

int	get_rgb(char *rest, int val[3])
{
	char	**tab;
	int		i;

	if (count_commas(rest) != 2)
		return (0);
	tab = ft_split(rest, ',');
	if (!tab)
		return (-1);
	i = 0;
	while (tab[i])
		i++;
	if (i != 3
		|| !parse_rgb(tab[0], &val[0])
		|| !parse_rgb(tab[1], &val[1])
		|| !parse_rgb(tab[2], &val[2]))
	{
		ft_free_split(tab);
		return (0);
	}
	ft_free_split(tab);
	return (1);
}

void	parse_color(t_map *map, int *color, bool *found, char *rest)
{
	int	val[3];
	int	res;

	if (*found)
	{
		map->parse_error = DOUBLE_RGB;
		return ;
	}
	res = get_rgb(skip_spaces(rest), val);
	if (res == -1)
	{
		map->parse_error = MALLOC_ERROR;
		return ;
	}
	if (res == 0)
	{
		map->parse_error = WRONG_RGB;
		return ;
	}
	color[0] = val[0];
	color[1] = val[1];
	color[2] = val[2];
	*found = true;
}
