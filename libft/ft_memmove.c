/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:11:52 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/15 11:24:37 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	int		i;

	if (!src && !dest)
		return (NULL);
	if (!size)
		return (dest);
	if (src < dest)
	{
		i = size;
		while (--i >= 0)
			*(char *)(dest + i) = *(char *)(src + i);
	}
	else
	{
		i = 0;
		while (i < (int) size)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dest);
}
