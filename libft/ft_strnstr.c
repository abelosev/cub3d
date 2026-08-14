/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:14:14 by anbelose          #+#    #+#             */
/*   Updated: 2025/04/29 19:14:56 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	k;

	if (!h || !n)
		return (NULL);
	i = 0;
	while (h[i])
	{
		k = 0;
		while (n[k] && i + k < len && h[i + k] == n[k])
			k++;
		if (!n[k])
			return ((char *)h + i);
		i++;
	}
	return (NULL);
}
