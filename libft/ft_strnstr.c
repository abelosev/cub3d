/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:45:01 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/11 12:23:07 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verify_concordance(const char *hay, const char *nee, size_t l)
{
	while (*hay == *nee && l > 0)
	{
		hay++;
		nee++;
		if (!(*nee))
			return (1);
		l--;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t length)
{
	if (!(*needle))
		return ((char *)(haystack));
	while (*haystack && length > 0)
	{
		if (*needle == *haystack)
		{
			if (verify_concordance(haystack, needle, length))
				return ((char *)haystack);
			if (length == 0 || !(*haystack))
				return (NULL);
		}
		length--;
		haystack++;
	}
	return (NULL);
}

/* int main()
{
	char *haystack = "bobonbonjour";
	char *needle = "bonjour";
	char *res = ft_strnstr(haystack, needle, 12);
	if (!res)
	{
		printf("strnstr returned NULL\n");
	}
	else
		printf("%s\n", res);
} */
