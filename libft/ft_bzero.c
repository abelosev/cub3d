/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:58:30 by anbelose          #+#    #+#             */
/*   Updated: 2025/04/29 19:00:44 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	i = 0;
	if (n == 0)
		return ;
	s1 = (unsigned char *)s;
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
}
