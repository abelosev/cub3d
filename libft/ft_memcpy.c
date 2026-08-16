/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:44:08 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/13 14:39:52 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (!dst && !src)
		return (NULL);
	while (counter < size)
	{
		*(unsigned char *)(dst + counter) = *(unsigned char *)(src + counter);
		counter++;
	}
	return (dst);
}
