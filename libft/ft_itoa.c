/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:44:42 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/12 16:17:05 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	abs_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	count_necessary_chars(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	unsigned int	necessary_chars;
	char			*result;

	necessary_chars = count_necessary_chars(n);
	result = malloc(sizeof(char) * (necessary_chars + 1));
	if (!result)
		return (NULL);
	if (n == 0)
		result[0] = '0';
	if (n < 0)
		result[0] = '-';
	result[necessary_chars] = '\0';
	while (n != 0)
	{
		result[--necessary_chars] = '0' + abs_value(n % 10);
		n /= 10;
	}
	return (result);
}
