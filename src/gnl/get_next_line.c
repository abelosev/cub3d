/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:35:03 by anbelose          #+#    #+#             */
/*   Updated: 2025/08/01 20:45:52 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_line1(char *remain)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!remain || !*remain)
		return (NULL);
	if (!ft_strchr(remain, '\n'))
	{
		line = ft_strndup(remain, ft_strlen(remain));
		if (!line)
			return (NULL);
		return (line);
	}
	while (remain[i] != '\n')
		i++;
	line = ft_strndup(remain, i + 1);
	return (line);
}

void	get_new_remain(char **remain, char *line)
{
	char	*new_remain;
	int		len;

	if (!*remain || !**remain)
		return ;
	if (!ft_strchr((*remain), '\n'))
		return (safe_free(remain));
	len = ft_strlen(line);
	new_remain = ft_strndup(*remain + len, ft_strlen(*remain) - len);
	if (!new_remain)
		return (safe_free(remain));
	free(*remain);
	*remain = new_remain;
}

ssize_t	reading(int fd, char **remain)
{
	ssize_t	read_res;
	char	*buf;
	char	*tmp;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	read_res = read(fd, buf, BUFFER_SIZE);
	if (read_res < 0)
		return (free(buf), safe_free(remain), read_res);
	while (read_res > 0)
	{
		buf[read_res] = '\0';
		tmp = ft_strjoin(*remain, buf);
		if (!tmp)
			return (free(buf), safe_free(remain), -1);
		free(*remain);
		*remain = tmp;
		if (ft_strchr(*remain, '\n'))
			break ;
		read_res = read(fd, buf, BUFFER_SIZE);
	}
	return (free(buf), read_res);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;
	ssize_t		read_res;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!remain)
	{
		remain = malloc(1);
		if (!remain)
			return (NULL);
		remain[0] = '\0';
	}
	read_res = 1;
	if (!ft_strchr(remain, '\n'))
	{
		read_res = reading(fd, &remain);
		if (read_res < 0)
			return (safe_free(&remain), NULL);
	}
	line = get_line1(remain);
	if (!line && remain)
		return (safe_free(&remain), NULL);
	get_new_remain(&remain, line);
	return (line);
}
