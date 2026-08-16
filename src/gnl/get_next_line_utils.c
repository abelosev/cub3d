/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 10:58:42 by vfekete           #+#    #+#             */
/*   Updated: 2026/08/05 14:33:18 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define INIT_CAPACITY 4096

t_rd	*init_rd(void)
{
	t_rd	*rd;

	rd = malloc(sizeof(t_rd));
	if (!rd)
		return (NULL);
	rd->capacity = INIT_CAPACITY;
	rd->buf = ft_calloc(sizeof(char), INIT_CAPACITY + 1);
	rd->start_index = 0;
	if (!rd->buf)
		return (free(rd), NULL);
	rd->size = 0;
	rd->rd_index = 0;
	rd->nl_index = -1;
	return (rd);
}

t_rd	*resize_rd_buf(t_rd *rd)
{
	char	*tmp;

	tmp = ft_calloc(sizeof(char), rd->capacity);
	if (!tmp)
		return (free(rd->buf), free(rd), NULL);
	ft_memcpy(tmp, rd->buf, rd->size);
	free(rd->buf);
	rd->buf = ft_calloc(sizeof(char), rd->capacity * 2 + 1);
	if (!rd->buf)
	{
		free(rd);
		rd = NULL;
		return (NULL);
	}
	ft_memcpy(rd->buf, tmp, rd->capacity);
	rd->capacity *= 2;
	free(tmp);
	return (rd);
}
