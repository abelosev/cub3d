/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:44:46 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/17 10:05:13 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searched)
{
	unsigned int	counter;

	if (!(char) searched)
		return ((char *)(string + ft_strlen(string)));
	counter = 0;
	while (*(string + counter))
	{
		if (*(string + counter) == (unsigned char)searched)
			return ((char *)(string + counter));
		counter++;
	}
	return (NULL);
}
