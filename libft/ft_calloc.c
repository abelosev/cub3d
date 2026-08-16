/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:01:51 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/11 12:28:41 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elem_size)
{
	void	*result;

	if (elem_size != 0 && SIZE_MAX / elem_size < nelem)
		return (NULL);
	result = malloc(nelem * elem_size);
	if (!result)
		return (NULL);
	ft_bzero(result, nelem * elem_size);
	return (result);
}
