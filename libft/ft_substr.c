/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:18:03 by anbelose          #+#    #+#             */
/*   Updated: 2025/04/29 19:39:01 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	len_res;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s || len == 0)
	{
		res = (char *)malloc(1);
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	len_res = len_s - start;
	if (len_res > len)
		len_res = len;
	res = (char *)malloc(sizeof(char) * (len_res + 1));
	if (!res)
		return (NULL);	
	ft_strlcpy(res, s + start, len_res + 1);
	return (res);
}
