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
