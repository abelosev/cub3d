/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:17 by anbelose          #+#    #+#             */
/*   Updated: 2025/04/29 19:16:01 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strnew(size_t size)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	ft_bzero((void *)res, size + 1);
	return (res);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!src || !dest)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (end == 0)
		return (ft_strnew(0));
	end--;
	while (s1[start] && ft_strchr(set, (int)s1[start]))
		start++;
	if (start > end)
		return (ft_strnew(0));
	while (ft_strchr(set, (int)s1[end]))
		end--;
	res = ft_strnew(end - start + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, s1 + start, end - start + 1);
	return (res);
}
