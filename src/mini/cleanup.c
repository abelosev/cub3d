#include "cub3d.h"

static void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img.img)
			mlx_destroy_image(game->mlx, game->tex[i].img.img);
		i++;
	}
}

/*
** Общая часть очистки графических ресурсов MLX, используемая и при
** нормальном выходе (cleanup_and_exit), и при ошибке, возникшей уже
** после mlx_init() (game_error). Каждый указатель проверяется на
** NULL перед уничтожением, поэтому функция безопасна в ЛЮБОЙ момент
** инициализации — независимо от того, сколько ресурсов успело
** быть создано на момент вызова.
*/
static void	destroy_mlx_resources(t_game *game)
{
	destroy_textures(game);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/*
** Единая точка выхода из графической части: вызывается и по ESC,
** и по закрытию окна (красный крестик). free_cub уже умеет корректно
** освобождать всё, что накопил парсер (пути текстур, карту и т.д.).
*/
void	cleanup_and_exit(t_game *game)
{
	destroy_mlx_resources(game);
	free_cub(&game->cub);
	exit(EXIT_SUCCESS);
}

/*
** Точка выхода для ошибок, которые могут произойти уже ПОСЛЕ
** mlx_init() — окно, screen image, текстуры (например, повреждённый
** XPM-файл, обнаруженный уже после того как одна или несколько
** других текстур успели успешно загрузиться).
**
** В отличие от parse_error() (который умеет освобождать только
** t_cub и используется в чистом парсинге, до появления любых
** MLX-ресурсов), game_error() дополнительно уничтожает всё, что уже
** успело быть создано в t_game на момент ошибки.
**
** Это безопасно на любом этапе init_game(), потому что все
** MLX-указатели в t_game гарантированно обнулены в самом начале
** init_game() через ft_bzero (см. game_init.c) — значит "ещё не
** созданный" ресурс всегда равен NULL, а не мусору со стека, и
** destroy_mlx_resources() корректно его пропустит.
*/
void	game_error(t_game *game, char *msg)
{
	printf("Error\n%s\n", msg);
	destroy_mlx_resources(game);
	free_cub(&game->cub);
	exit(EXIT_FAILURE);
}
