/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:54:54 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/16 12:40:19 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	strlen;
	char	*result;

	strlen = ft_strlen(str);
	result = malloc(strlen + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, strlen + 1);
	return (result);
}
