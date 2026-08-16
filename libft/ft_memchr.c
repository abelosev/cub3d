/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:09:33 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/17 10:04:53 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mem_block, int searched, size_t s)
{
	size_t			i;
	unsigned char	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	ptr = (unsigned char *)mem_block;
	while (ptr[i] != (unsigned char)searched && i < s)
		i++;
	if (i != s && ptr[i] == (unsigned char)searched)
		return (ptr + i);
	return (NULL);
}
