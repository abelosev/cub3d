/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:18:25 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/13 09:33:54 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t s)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (!s)
		return (0);
	ptr1 = (unsigned char *)p1;
	ptr2 = (unsigned char *)p2;
	while (s > 0 && *ptr1 == *ptr2)
	{
		ptr1++;
		ptr2++;
		s--;
	}
	if (s == 0)
		return (0);
	return (*ptr1 - *ptr2);
}
