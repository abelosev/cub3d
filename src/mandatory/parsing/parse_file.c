/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 14:21:03 by anbelose          #+#    #+#             */
/*   Updated: 2026/08/18 14:21:20 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_line_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
}

t_list	*read_lines(int fd, t_map *map)
{
	t_list	*lst;
	t_list	*node;
	char	*line;

	lst = NULL;
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			free_line_list(lst);
			map->parse_error = MALLOC_ERROR;
			return (NULL);
		}
		ft_lstadd_back(&lst, node);
		line = get_next_line(fd);
	}
	return (lst);
}

char	**list_to_array(t_list *lst, t_map *map)
{
	char	**arr;
	t_list	*tmp;
	int		n;
	int		i;

	n = ft_lstsize(lst);
	arr = malloc(sizeof(char *) * (n + 1));
	if (!arr)
	{
		free_line_list(lst);
		map->parse_error = MALLOC_ERROR;
		return (NULL);
	}
	i = 0;
	while (lst)
	{
		arr[i++] = (char *)lst->content;
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	arr[i] = NULL;
	return (arr);
}

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}
