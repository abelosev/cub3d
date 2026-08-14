#include "cub3d.h"

/*
** Высота стены на экране обратно пропорциональна perp_wall_dist,
** а не реальной дистанции луча — именно это убирает fish-eye.
** draw_start/draw_end зажаты в границы экрана: сама стена может быть
** выше окна, но рисуем только видимую часть.
*/
static void	compute_bounds(t_ray *ray, int *start, int *end, int *line_h)
{
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	*line_h = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	*start = -(*line_h) / 2 + WIN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = (*line_h) / 2 + WIN_HEIGHT / 2;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

/*
** wall_x = точка попадания вдоль стены, в диапазоне [0,1) —
** используется как горизонтальная координата текстуры. Отражение
** tex_x для некоторых комбинаций side/direction нужно, чтобы
** текстура не была отзеркалена при взгляде с "обратной" стороны.
*/
static int	compute_tex_x(t_game *game, t_ray *ray, t_tex *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->img.width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = tex->img.width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = tex->img.width - tex_x - 1;
	return (tex_x);
}

void	draw_column(t_game *game, int x, t_ray *ray)
{
	int		start;
	int		end;
	int		line_h;
	int		tex_x;
	t_tex	*tex;
	double	step;
	double	tex_pos;
	int		y;

	compute_bounds(ray, &start, &end, &line_h);
	tex = &game->tex[ray->tex_id];
	tex_x = compute_tex_x(game, ray, tex);
	step = (double)tex->img.height / line_h;
	tex_pos = (start - WIN_HEIGHT / 2.0 + line_h / 2.0) * step;
	y = start;
	while (y <= end)
	{
		put_pixel(&game->screen, x, y,
			get_tex_pixel(tex, tex_x, (int)tex_pos % tex->img.height));
		tex_pos += step;
		y++;
	}
}
