/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:20:14 by burei             #+#    #+#             */
/*   Updated: 2026/07/07 12:11:15 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIN_WIDTH && y < WIN_HEIGHT && y >= 0 && x >= 0)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

int	rgba_to_int(unsigned char r,
				unsigned char g,
				unsigned char b,
				unsigned char a)
{
	int	result;

	result = 0;
	result = (a << 24) | (r << 16) | (g << 8) | (b);
	return (result);
}

void	draw_line(t_data *img, t_point p1, t_point p2, int rgba[4])
{
	t_line_draw	line_draw;
	int			i;

	line_draw.dx = p2.x - p1.x;
	line_draw.dy = p2.y - p1.y;
	if (abs(line_draw.dx) > abs(line_draw.dy))
		line_draw.steps = abs(line_draw.dx);
	else
		line_draw.steps = abs(line_draw.dy);
	line_draw.x_inc = line_draw.dx / (float)line_draw.steps;
	line_draw.y_inc = line_draw.dy / (float)line_draw.steps;
	line_draw.x = p1.x;
	line_draw.y = p1.y;
	i = -1;
	while (++i <= line_draw.steps)
	{
		my_mlx_pixel_put(img, round(line_draw.x), round(line_draw.y),
			rgba_to_int(rgba[0], rgba[1], rgba[2], rgba[3]));
		line_draw.x += line_draw.x_inc;
		line_draw.y += line_draw.y_inc;
	}
}
