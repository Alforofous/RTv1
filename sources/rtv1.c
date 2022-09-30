/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:38 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/30 16:57:10 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	create_window(t_utils *utils)
{

	utils->mlx = mlx_init();
	if (utils->mlx == NULL)
		close_prog(utils, "Failed to connect software to display...", -2);
	utils->win = mlx_new_window(utils->mlx, SCREEN_X, SCREEN_Y, "RTv1");
	if (utils->win == NULL)
		close_prog(utils, "Failed to open window...", -2);
	mlx_do_key_autorepeatoff(utils->mlx);
}

void	close_prog(t_utils *utils, char *exit_msg, int exit_code)
{
	if (utils->win != NULL)
		mlx_destroy_window(utils->mlx, utils->win);
	free_images(utils->mlx, utils->img, IMG_COUNT);
	ft_putendl(exit_msg);
	exit (exit_code);
}

static void	draw_images(t_utils *utils, t_img *img)
{
	image_processing(utils, &img[6], 0x006543);
	image_processing(utils, &img[7], 0x000000);
	image_processing(utils, &img[9], 0x000000);
	image_processing(utils, &img[10], 0x000000);
	image_processing(utils, &img[11], 0x000000);
	image_processing(utils, &img[12], 0x000000);
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
	utils.objects = load_scene(argv[1]);
	if (utils.objects == NULL)
		perror("Error");
	create_window(&utils);
	utils.img = create_images(utils.mlx, IMG_COUNT);
	if (utils.img == NULL)
		close_prog(&utils, "Failed to create images...", -2);
	utils.proj = init_proj(80.0f,
		&(t_2i){utils.img[0].dim.size.x, utils.img[0].dim.size.y},
		&(t_2f){0.1f, 1000.0f});
	draw_images(&utils, utils.img);
	init_hooks(&utils);
	render_screen(&utils);
	mlx_loop(utils.mlx);
	return (0);
}
