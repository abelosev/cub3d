/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:48:35 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/11 12:27:10 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			s_len;
	char			*result;
	unsigned int	index;

	s_len = ft_strlen(s);
	result = malloc(s_len + 1);
	if (!result)
		return (NULL);
	index = 0;
	while (s[index])
	{
		result[index] = f(index, s[index]);
		index++;
	}
	result[index] = '\0';
	return (result);
}

/* char    shift_by_index(unsigned int x, char c)
{
	return (c + x);
}
#include <stdio.h>

int	main(int ac, char **av)
{
	char    *result = ft_strmapi(av[1], shift_by_index);
	printf("%s\n", result);
} */