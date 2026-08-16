/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:00:54 by burei             #+#    #+#             */
/*   Updated: 2026/08/10 09:46:49 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	*gnl_no_nl(int fd)
{
	char	*tmp;
	char	*res;

	tmp = get_next_line(fd);
	if (!tmp)
		return (NULL);
	res = ft_strtrim(tmp, "\n");
	return (free(tmp), res);
}

int	get_max(int *lst)
{
	int	max;
	int	i;

	max = 0;
	i = -1;
	while (lst[++i])
	{
		if (lst[i] > max)
			max = lst[i];
	}
	return (max);
}

int	get_min(int *lst)
{
	int	min;
	int	i;

	min = INT32_MAX;
	i = -1;
	while (lst[++i])
	{
		if (lst[i] < min)
			min = lst[i];
	}
	return (min);
}

t_point	add_points(t_point p1, t_point p2)
{
	t_point	ret;

	ret.x = p1.x + p2.x;
	ret.y = p1.y + p2.y;
	return (ret);
}

t_point	rotate_point(t_point p, float angleDeg)
{
	t_point	ret;
	float	rad;

	rad = angleDeg * (M_PI / 180);
	ret.x = p.x * cos(rad) - p.y * sin(rad);
	ret.y = p.x * sin(rad) + p.y * cos(rad);
	return (ret);
}
