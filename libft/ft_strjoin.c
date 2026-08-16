/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:35:55 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/11 12:27:00 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*result;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (*s1)
	{
		result[i] = *(s1++);
		i++;
	}
	while (*s2)
	{
		result[i] = *(s2++);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/* #include <stdio.h>
int	main(void)
{
	char *result = ft_strjoin("coucou je ", "deteste brigitte macron");
	printf("%s\n", result);
} */