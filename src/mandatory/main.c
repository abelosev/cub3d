/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 12:58:29 by burei             #+#    #+#             */
/*   Updated: 2026/08/07 09:18:23 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

void	error(t_parse_errors error_code)
{
	char	**err_msgs;

	err_msgs = (char *[]){"", NO_PLAYER_ERR, DOUBLE_PLAYER_ERR,
		INVALID_CHAR_ERR, INVALID_TEXTURES_ERR, DOUBLE_TEXTURES_ERR,
		MAP_SPLIT_ERR, WRONG_RGB_ERR, DOUBLE_RGB_ERR, MISSING_ASSETS_ERR,
		UNEXPECTED_ASSETS_ERR, OPEN_FAIL_ERR, TEXTURE_LOAD_FAIL_ERR,
		MAP_NOT_CLOSE_ERR, INVALID_WHITESPACE_ERR, MALLOC_ERROR_MSG};
	if (error_code != NO_ERROR)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(err_msgs[error_code], 2);
	}
}

void	set_hooks(t_cub3d_env *env)
{
	mlx_hook(env->mlx_win, 17, 0, (void *)terminate, env);
	mlx_hook(env->mlx_win, 2, 1L << 0, (void *)key_hook, env);
}

int	main(int argc, char **argv)
{
	t_cub3d_env	env;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nIncorrect argument count.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(argv[1]) < 5
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
	{
		ft_putstr_fd("Error\nWrong filename extension.\n", 2);
		exit(EXIT_FAILURE);
	}
	env.mlx = NULL;
	env.mlx_win = NULL;
	env.img.img = NULL;
	if (init_cub3d_env(argv[1], &env) == 1)
	{
		error(env.map->parse_error);
		terminate(&env);
	}
	raycast(&env);
	mlx_put_image_to_window(env.mlx, env.mlx_win, env.img.img, 0, 0);
	mlx_loop(env.mlx);
	clean_cub3d_env(&env);
}
