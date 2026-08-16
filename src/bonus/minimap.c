/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:52:23 by vfekete           #+#    #+#             */
/*   Updated: 2026/07/11 18:36:45 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

#define MINIMAP_OFF 100
#define CELL_LEN 20
#define CELL_COUNT 10

t_point	*apply_offset(t_point arrow_p[4])
{
	arrow_p[0] = add_points(arrow_p[0], (t_point){MINIMAP_OFF + pow(CELL_COUNT,
				2) / 2, MINIMAP_OFF + pow(CELL_COUNT, 2) / 2});
	arrow_p[1] = add_points(arrow_p[1], (t_point){MINIMAP_OFF + pow(CELL_COUNT,
				2) / 2, MINIMAP_OFF + pow(CELL_COUNT, 2) / 2});
	arrow_p[2] = add_points(arrow_p[2], (t_point){MINIMAP_OFF + pow(CELL_COUNT,
				2) / 2, MINIMAP_OFF + pow(CELL_COUNT, 2) / 2});
	arrow_p[3] = add_points(arrow_p[3], (t_point){MINIMAP_OFF + pow(CELL_COUNT,
				2) / 2, MINIMAP_OFF + pow(CELL_COUNT, 2) / 2});
	return (arrow_p);
}

void	draw_square(t_data *img, int square_num, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < CELL_LEN)
	{
		j = -1;
		while (++j < CELL_LEN)
			my_mlx_pixel_put(img, (square_num % CELL_COUNT) * CELL_LEN
				+ MINIMAP_OFF / 2 + i, (square_num / CELL_COUNT) * CELL_LEN
				+ MINIMAP_OFF / 2 + j, color);
	}
}

int	select_color(t_cub3d_env *env, t_point_int curr, t_point_int start)
{
	if (is_out_of_bounds(env, start.x + curr.x, start.y + curr.y))
		return (0x000000FF);
	else if (env->map->cells[start.y + curr.y][start.x + curr.x] == 1)
		return (0x00FF0000);
	else if (start.y + curr.y == (int)env->map->position.y && start.x
		+ curr.x == (int)env->map->position.x)
		return (0x0000FF00);
	else
		return (0x00000000);
}

void	draw_minimap(t_cub3d_env *env)
{
	t_point_int	curr;
	t_point_int	start;
	int			square_num;
	int			color;

	square_num = 0;
	start.y = (int)(env->map->position.y) - 5;
	start.x = (int)(env->map->position.x) - 5;
	curr.y = 0;
	while (curr.y < CELL_COUNT)
	{
		curr.x = 0;
		while (curr.x < CELL_COUNT)
		{
			color = select_color(env, curr, start);
			draw_square(&env->img, square_num++, color);
			curr.x++;
		}
		curr.y++;
	}
}
