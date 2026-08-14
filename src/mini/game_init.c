#include "cub3d.h"

/*
** Направление и "камера" (plane) в системе координат, где +x = восток,
** +y = юг (совпадает с тем, как хранится карта: строки идут вниз).
** Длина plane регулирует FOV (см. PLANE_LEN в cub3d.h).
*/
static void	set_direction(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
		game->plane_x = PLANE_LEN;
		game->plane_y = 0;
	}
	else if (dir == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
		game->plane_x = -PLANE_LEN;
		game->plane_y = 0;
	}
	else if (dir == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = PLANE_LEN;
	}
	else
	{
		game->dir_x = -1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = -PLANE_LEN;
	}
}

/*
** Позиция игрока хранится как double в центре клетки (+0.5), чтобы
** raycasting и коллизии работали с непрерывными координатами.
*/
static void	init_player(t_game *game)
{
	game->pos_x = game->cub.player.x + 0.5;
	game->pos_y = game->cub.player.y + 0.5;
	set_direction(game, game->cub.player.dir);
}

static void	init_image(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen.img)
		parse_error(&game->cub, "mlx: failed to create screen image");
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bpp,
			&game->screen.line_len,
			&game->screen.endian);
	game->screen.width = WIN_WIDTH;
	game->screen.height = WIN_HEIGHT;
}

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		game_error(game, "mlx: failed to initialize");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		game_error(game, "mlx: failed to create window");
}

/*
** cub уже полностью распарсен и провалидирован (parse_cub). Здесь мы
** просто копируем его в t_game и поднимаем графическую часть поверх.
**
** ft_bzero() ДО копирования cub обязателен и должен идти первой
** строкой: он гарантированно обнуляет game->mlx, game->win,
** game->screen.img и все четыре game->tex[i].img.img ещё до того,
** как что-либо из этого может провалиться.
**
** Без этого, если t_game лежит на стеке main() без явной
** инициализации, эти указатели содержат мусор — и если, например,
** вторая текстура из четырёх не загрузится, game_error() /
** destroy_textures() попытаются вызвать mlx_destroy_image() по
** случайным адресам для ещё не тронутых 3-й/4-й текстур (garbage
** != NULL), что напрямую ведёт к undefined behavior.
*/
void	init_game(t_game *game, t_cub *cub)
{
	ft_bzero(game, sizeof(t_game));
	game->cub = *cub;
	init_mlx(game);
	init_image(game);
	load_all_textures(game);
	init_player(game);
}
