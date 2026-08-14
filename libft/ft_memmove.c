/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:19:06 by anbelose          #+#    #+#             */
/*   Updated: 2025/04/29 19:19:13 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dest || !n)
		return (NULL);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		d = (unsigned char *)dest;
		s = (unsigned char *)src;
		i = n - 1;
		while (i > 0)
		{
			d[i] = s[i];
			i--;
		}
		d[0] = s[0];
	}
	return (dest);
}

// ПЕРЕДЕЛАТЬ ТАК:

// В стандартной реализации memmove обычно:

// Если dest < src, копируют вперёд (как memcpy).

// Если dest > src, копируют назад, начиная с конца, чтобы избежать перезаписи.
