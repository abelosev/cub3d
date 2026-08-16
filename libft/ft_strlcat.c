/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:44:50 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/11 12:31:44 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	dst += dstlen;
	i = 0;
	while (src[i] != '\0' && i < dstsize - dstlen - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i != dstsize - dstlen)
		dst[i] = '\0';
	return (dstlen + srclen);
}

/* #include <string.h>
#include <bsd/string.h>

int	main(void)
{
	char    *src = "to append";
	char    *dst1;
	char    *dst2;
	size_t     r2;
	size_t     r1;
	for (size_t i = 0; i < 23; i++)
	{
		dst1 = malloc(sizeof(char) * 50);
		dst2 = malloc(sizeof(char) * 50);
		strcpy(dst1, "test string ");
		strcpy(dst2, "test string ");
		r1 = ft_strlcat(dst1, src, i);
		r2 = strlcat(dst2, src, i);
		printf("ft_strlcat  : %s for size = %zu returns %zu\n", dst1, i, r1);
		printf("strlcat     : %s for size = %zu returns %zu\n", dst2, i, r2);
	}
} */