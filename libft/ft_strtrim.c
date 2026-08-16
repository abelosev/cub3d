/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:45:33 by vfekete           #+#    #+#             */
/*   Updated: 2026/08/10 08:51:33 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*result;
	unsigned int	start;
	unsigned int	end;

	if (*set == '\0')
		return (ft_strdup(s1));
	if (*s1 == '\0')
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (is_in_set(s1[start], set) && s1[start])
		start++;
	while (is_in_set(s1[end], set) && end > start)
		end--;
	result = ft_substr(s1, start, end - start + 1);
	if (!result)
		return (NULL);
	return (result);
}

char	*ft_strtrim_end(char const *s1, char const *set)
{
	char			*result;
	unsigned int	end;

	if (*set == '\0')
		return (ft_strdup(s1));
	if (*s1 == '\0')
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (is_in_set(s1[end], set) && end > 0)
		end--;
	result = ft_substr(s1, 0, end + 1);
	if (!result)
		return (NULL);
	return (result);
}

/* int main(int ac, char **av)
{
	(void) ac;

	char *result = ft_strtrim(av[1], av[2]);
	printf("result is %s\n", result);
} */