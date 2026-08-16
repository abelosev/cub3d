/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:00:37 by burei             #+#    #+#             */
/*   Updated: 2026/07/07 12:12:17 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	if (!*split)
		return (free(split));
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
