/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:29:26 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/12 17:57:07 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	strlen;

	strlen = ft_strlen(s);
	if (start + len > strlen)
		len = strlen - start;
	if (start > strlen)
		len = 0;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len > 0 && s[start + len - 1])
	{
		result[len - 1] = s[start + len - 1];
		len--;
	}
	return (result);
}

/* int main()
{
	char *result = ft_substr("0123456789", 5, 3);
	printf("%s\n", result);
} */