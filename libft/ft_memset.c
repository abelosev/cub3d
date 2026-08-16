/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:44:11 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/11 12:30:34 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t			counter;
	unsigned char	*ptr;

	ptr = (unsigned char *)pointer;
	counter = 0;
	while (counter < count)
	{
		*(ptr + counter) = (unsigned char)value;
		counter++;
	}
	return (pointer);
}
