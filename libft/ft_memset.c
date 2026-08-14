/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:06:36 by anbelose          #+#    #+#             */
/*   Updated: 2025/04/29 19:06:40 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	i = 0;
	if (n == 0)
		return (s);
	s1 = (unsigned char *)s;
	while (i < n)
	{
		s1[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
