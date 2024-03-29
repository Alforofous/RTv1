/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:45:40 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 14:37:42 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	create_window(t_utils *utils)
{
	utils->mlx = mlx_init();
	if (utils->mlx == NULL)
		close_prog(utils, "Failed to connect software to display...", -2);
	if (SCREEN_X < 200 || SCREEN_X > 2560 || SCREEN_Y < 200 || SCREEN_Y > 1440)
		close_prog(utils, "Window size out of scope...", -2);
	else
		utils->win = mlx_new_window(utils->mlx, SCREEN_X, SCREEN_Y, "RTv1");
	if (utils->win == NULL)
		close_prog(utils, "Failed to open window...", -2);
	mlx_do_key_autorepeatoff(utils->mlx);
}

static void	init_hooks(t_utils *utils)
{
	mlx_hook(utils->win, 2, 1L << 0, &key_down, utils);
	mlx_hook(utils->win, 3, 1L << 1, &key_up, utils);
	mlx_hook(utils->win, 4, 1L << 2, &mouse_down, utils);
	mlx_hook(utils->win, 5, 1L << 3, &mouse_up, utils);
	mlx_hook(utils->win, 6, 1L << 6, &mouse_move, utils);
	mlx_hook(utils->win, 17, 0, &on_destroy, utils);
	mlx_hook(utils->win, 12, 0, &put_images_to_window, utils);
	mlx_loop_hook(utils->mlx, &prog_clock, utils);
}

void	init_mlx(t_utils *utils)
{
	create_window(utils);
	init_hooks(utils);
}
