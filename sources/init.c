/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:50:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/14 16:20:01 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_hooks(t_utils *utils)
{
	mlx_hook(utils->win, 2, 1L << 0, &key_down, utils);
	mlx_hook(utils->win, 6, 1L << 6, &mouse_move, utils);
	mlx_hook(utils->win, 5, 1L << 3, &mouse_up, utils);
	mlx_hook(utils->win, 4, 1L << 2, &mouse_down, utils);
	mlx_hook(utils->win, 17, 0, &on_destroy, utils);
	mlx_loop_hook(utils->mlx, &prog_clock, utils);
}

void	init_proj(t_utils *utils)
{
	utils->proj.z_near = 0.1f;
	utils->proj.z_far = 1000;
	utils->proj.fov = 90;
	utils->proj.asp_ratio = (float)utils->img.dim.height
	/ (float)utils->img.dim.width;
	utils->proj.fov_rad = (float)(1 / tan((utils->proj.fov) / 2 / 180 * PI));
}

void	init_values(t_utils *utils)
{
	utils->tick = 0;
	utils->reference = -1;
	utils->visual_rays = -1;
	utils->rot.x = 0;
	utils->rot.y = 0;
	utils->rot.z = 0;
}

void	init_mouse(t_utils *utils)
{
	utils->mouse.move_x = 0;
	utils->mouse.move_y = 0;
	utils->mouse.zoom = 20;
	utils->mouse.x = SCREEN_X / 2;
	utils->mouse.y = SCREEN_Y / 2;
}

void	init(t_utils *utils)
{
	utils->mlx = NULL;
	utils->win = NULL;
	init_proj(utils);
	init_mouse(utils);
	init_values(utils);
	init_matrix(&utils->pmatrix);
	init_matrix(&utils->rmatrix_x);
	init_matrix(&utils->rmatrix_y);
	init_matrix(&utils->rmatrix_z);
	init_pmatrix(utils);
	init_rmatrix_x(utils);
	init_rmatrix_y(utils);
	init_rmatrix_z(utils);
}
