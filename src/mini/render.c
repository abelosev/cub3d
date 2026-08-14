#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = (unsigned int)color;
}

int	get_color(t_color *c)
{
	return ((c->r << 16) | (c->g << 8) | c->b);
}

/*
** Потолок и пол закрашиваются одним цветом сразу на весь экран;
** стены (draw_column) дорисуются поверх нужного диапазона по y.
** Fish-eye уже исправлен на этапе raycast.c (perp_wall_dist, а не
** евклидово расстояние), так что здесь только геометрия высоты стены.
*/
static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(&game->screen, x, y, get_color(&game->cub.ceiling));
			else
				put_pixel(&game->screen, x, y, get_color(&game->cub.floor));
			x++;
		}
		y++;
	}
}

void	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	draw_background(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(game, x, &ray);
		draw_column(game, x, &ray);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
