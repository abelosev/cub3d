#include "cub3d.h"

/*
** camera_x идёт от -1 (левый край экрана) до +1 (правый край).
** ray_dir = dir + plane * camera_x — классическая формула Lodev.
*/
static void	init_ray(t_game *game, int x, t_ray *ray)
{
	ray->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->dir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->dir_y = game->dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->pos_y) * ray->delta_dist_y;
	}
}

/*
** "Прыгаем" от одной границы клетки к другой, пока не упрёмся в стену
** ('1') или в пространство вне карты (' ' — по идее недостижимо,
** карта уже проверена на замкнутость, но проверка предотвращает
** бесконечный цикл при любой непредвиденной ошибке данных).
*/
static void	perform_dda(t_game *game, t_ray *ray)
{
	char	c;

	c = get_map_char(&game->cub, ray->map_y, ray->map_x);
	while (c != '1' && c != ' ')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		c = get_map_char(&game->cub, ray->map_y, ray->map_x);
	}
}

static void	calc_perp_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->pos_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->pos_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
}

/*
** Выбор текстуры по стороне попадания. Соглашение о координатах:
** +x = восток, +y = юг (см. game_init.c / set_direction).
*/
static void	select_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->tex_id = TEX_WE;
		else
			ray->tex_id = TEX_EA;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->tex_id = TEX_NO;
		else
			ray->tex_id = TEX_SO;
	}
}

void	cast_ray(t_game *game, int x, t_ray *ray)
{
	init_ray(game, x, ray);
	perform_dda(game, ray);
	calc_perp_dist(game, ray);
	select_texture(ray);
}
