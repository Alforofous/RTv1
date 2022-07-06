/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:50:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/06 15:38:27 by dmalesev         ###   ########.fr       */
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

t_proj	init_proj(float fov, t_2i *dim, t_2f *z_depth)
{
	t_proj	proj;

	proj.z_near = z_depth->x;
	proj.z_far = z_depth->y;
	proj.fov = fov;
	proj.asp_ratio = (float)dim->x / (float)dim->y;
	proj.fov_rad = (float)(1 / tan(fov / 2 / 180 * PI));
	return (proj);
}

t_list *init_scene()
{
	t_list		*objects;
	t_object	object[6];

	object[0] = (t_object){(t_3f){0.0f, 0.0f, -10.0f}, (t_3f){0.0f, 0.0f, 0.0f},0x880000, 4.0f, 1};
	object[1] = (t_object){(t_3f){-5.0f, 2.0f, -10.0f}, (t_3f){0.0f, 0.0f, 0.0f}, 0x004488, 100.0f, 1};
	object[2] = (t_object){(t_3f){0.0f, 0.0f, 100.0f}, (t_3f){0.0f, 0.0f, 0.0f}, 0x004422, 200.0f, 1};
	object[3] = (t_object){(t_3f){0.0f, 0.1f, 0.0f}, (t_3f){0.0f, 1.0f, 0.0f}, 0xDD7700, 0.0f, 2};
	object[4] = (t_object){(t_3f){0.0f, 0.1f, 0.0f}, (t_3f){0.0f, -1.0f, 0.0f}, 0xDDDD00, 0.0f, 2};
	object[5] = (t_object){(t_3f){0.0f, 0.0f, -10.0f}, (t_3f){0.0f, 0.0f, 0.0f},0xFFFFFF, 1.0f, 1};
	objects = ft_lstnew(&object[0], sizeof(t_object));
	ft_lstappnew(&objects, &object[1], sizeof(t_object));
	ft_lstappnew(&objects, &object[2], sizeof(t_object));
	ft_lstappnew(&objects, &object[3], sizeof(t_object));
	ft_lstappnew(&objects, &object[4], sizeof(t_object));
	ft_lstappnew(&objects, &object[5], sizeof(t_object));
	return (objects);
}

void	init_camera(t_utils *utils)
{
	utils->rot.x = 0;
	utils->rot.y = 0;
	utils->rot.z = 0;
	utils->cam.origin = (t_3f){0.0f, 0.0f, 0.0f};
}

void	init_values(t_utils *utils)
{
	utils->tick = 0;
	utils->visual_rays = 0;
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
	init_mouse(utils);
	init_values(utils);
	utils->objects = init_scene();
	init_matrix(&utils->pmatrix);
	init_matrix(&utils->rmatrix_x);
	init_matrix(&utils->rmatrix_y);
	init_matrix(&utils->rmatrix_z);
	utils->pmatrix = init_pmatrix(&utils->proj);
	utils->rmatrix_x = init_rmatrix_x(0.0f);
	utils->rmatrix_y = init_rmatrix_y(0.0f);
	utils->rmatrix_z = init_rmatrix_z(0.0f);
}
