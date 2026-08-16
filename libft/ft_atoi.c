/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:44:14 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/12 16:36:03 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *src)
{
	int				result;
	unsigned int	sign;

	sign = 1;
	result = 0;
	while (*src == ' ' || (*src >= 9 && *src <= 13))
		src++;
	if (*src == '-' || *src == '+')
	{
		if (*src == '-')
			sign = -1;
		src++;
	}
	while (*src >= '0' && *src <= '9')
	{
		result = result * 10 + *src++ - '0';
	}
	return (result * sign);
}
