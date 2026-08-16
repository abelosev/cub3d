/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:45:04 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/17 09:52:01 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *string, int searched)
{
	int	strlen;

	strlen = ft_strlen(string);
	if (!(char) searched)
		return ((char *)(string + strlen));
	if (!*string)
		return (NULL);
	while (strlen-- >= 0)
	{
		if (string[strlen] == (unsigned char)searched)
			return ((char *)(string + strlen));
	}
	return (NULL);
}
