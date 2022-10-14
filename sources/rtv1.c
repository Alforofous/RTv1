/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:38 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 14:33:37 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	close_prog(void *param, char *exit_msg, int exit_code)
{
	static t_utils	*utils;

	if (utils == NULL)
	{
		utils = param;
		return ;
	}
	if (utils->win != NULL)
		mlx_destroy_window(utils->mlx, utils->win);
	free_images(utils->mlx, utils->img, IMG_COUNT);
	ft_putendl(exit_msg);
	exit (exit_code);
}

int	main(int argc, char **argv)
{
	t_utils	utils;

	if (argc > 2)
	{
		ft_putendl("Too many arguments.");
		return (1);
	}
	init(&utils);
	utils.scene = load_scene(argv[1]);
	if (utils.scene == NULL)
		perror("Scene loading error");
	image_processing(&utils, &utils.img[1], 0x000000, 0);
	render_screen(&utils);
	mlx_loop(utils.mlx);
	return (0);
}
