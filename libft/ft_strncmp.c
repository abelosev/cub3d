/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:44:59 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/13 15:59:57 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t length)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (!length)
		return (0);
	while (*p1 && *p2 && *p1 == *p2 && length-- > 1)
	{
		p1++;
		p2++;
	}
	if (*p1 == *p2)
		return (0);
	else
		return (*p1 - *p2);
}
