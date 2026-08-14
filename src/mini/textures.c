#include "cub3d.h"

static void	load_texture(t_game *game, char *path, t_tex *tex)
{
	tex->img.img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->img.width, &tex->img.height);
	if (!tex->img.img)
		game_error(game, "mlx: failed to load a texture file");
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
}

/*
** Порядок загрузки обязан совпадать с TEX_NO/TEX_SO/TEX_WE/TEX_EA
** из cub3d.h.
**
** Если, например, load_texture() падает на второй текстуре, первая
** уже успешно загруженная текстура (и mlx/win/screen image) не
** утекает: load_texture() зовёт game_error(), а не parse_error(),
** и game_error() корректно уничтожает всё, что уже было создано
** (см. cleanup.c). Указатели ещё не загруженных текстур в этот
** момент гарантированно NULL благодаря ft_bzero() в начале
** init_game() (см. game_init.c), так что destroy_textures() их
** просто пропустит.
*/
void	load_all_textures(t_game *game)
{
	load_texture(game, game->cub.no_path, &game->tex[TEX_NO]);
	load_texture(game, game->cub.so_path, &game->tex[TEX_SO]);
	load_texture(game, game->cub.we_path, &game->tex[TEX_WE]);
	load_texture(game, game->cub.ea_path, &game->tex[TEX_EA]);
}

int	get_tex_pixel(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (x >= tex->img.width)
		x = tex->img.width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->img.height)
		y = tex->img.height - 1;
	pixel = tex->img.addr + (y * tex->img.line_len + x * (tex->img.bpp / 8));
	return (*(unsigned int *)pixel);
}
