/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 12:58:29 by burei             #+#    #+#             */
/*   Updated: 2026/08/07 09:18:11 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/* Comment out mouse_hide to disable leaks */
void	set_hooks(t_cub3d_env *env)
{
	mlx_mouse_hide(env->mlx, env->mlx_win);
	mlx_hook(env->mlx_win, 17, 0, (void *) terminate, env);
	mlx_hook(env->mlx_win, 2, 1L << 0, (void *) key_hook, env);
	mlx_hook(env->mlx_win, 6, 1L << 6, (void *) mouse_hook, env);
}

void	error(t_parse_errors error_code)
{
	char	**err_msgs;

	err_msgs = (char *[]){
		"", NO_PLAYER_ERR, DOUBLE_PLAYER_ERR, INVALID_CHAR_ERR,
		INVALID_TEXTURES_ERR, DOUBLE_TEXTURES_ERR, MAP_SPLIT_ERR,
		WRONG_RGB_ERR, DOUBLE_RGB_ERR, MISSING_ASSETS_ERR,
		UNEXPECTED_ASSETS_ERR, OPEN_FAIL_ERR, TEXTURE_LOAD_FAIL_ERR,
		MAP_NOT_CLOSE_ERR, INVALID_WHITESPACE_ERR, MALLOC_ERROR_MSG
	};
	if (error_code != NO_ERROR)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(err_msgs[error_code], 2);
	}
}

int	main(int argc, char **argv)
{
	t_cub3d_env	env;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nIncorrect argument count.", 2);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(argv[1]) > 3
		&& ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
	{
		ft_putstr_fd("Error\nWrong filename extension.\n", 2);
		exit(EXIT_SUCCESS);
	}
	if (init_cub3d_env(argv[1], &env) == 1)
	{
		error(env.map->parse_error);
		terminate(&env);
	}
	raycast(&env);
	draw_minimap(&env);
	mlx_put_image_to_window(env.mlx, env.mlx_win, env.img.img, 0, 0);
	mlx_loop(env.mlx);
	clean_cub3d_env(&env);
}
