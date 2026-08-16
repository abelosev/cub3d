/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 11:57:25 by vfekete           #+#    #+#             */
/*   Updated: 2026/07/06 14:31:06 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	rd_until_nl_or_eof(int fd, t_rd *rd)
{
	int	bytes_read;

	if (fd < 0)
		return ;
	rd->start_index = rd->rd_index;
	while (!ft_strchr(rd->buf + rd->start_index, '\n'))
	{
		while (rd->size + BUFFER_SIZE >= rd->capacity)
			resize_rd_buf(rd);
		if (!rd)
			return ;
		bytes_read = read(fd, rd->buf + rd->size, BUFFER_SIZE);
		if (bytes_read > 0)
			rd->size += bytes_read;
		if (bytes_read < BUFFER_SIZE)
			break ;
	}
	if (ft_strchr(rd->buf + rd->start_index, '\n'))
		rd->nl_index = ft_strchr(rd->buf + rd->start_index, '\n') - rd->buf;
	else
		rd->nl_index = rd->size;
	rd->rd_index = rd->nl_index + 1;
}

char	*get_next_line(int fd)
{
	static t_rd	*rd = (void *)1;

	if (rd == (void *)1)
		rd = init_rd();
	if (!rd)
		return (NULL);
	rd_until_nl_or_eof(fd, rd);
	if (rd->start_index >= rd->size || fd == -1)
	{
		free(rd->buf);
		rd->buf = NULL;
		free(rd);
		rd = NULL;
		return (NULL);
	}
	return (ft_substr(rd->buf, rd->start_index, rd->rd_index
			- rd->start_index));
}
