/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:50:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/07 13:55:07 by dmalesev         ###   ########.fr       */
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

	objects = ft_lstnew(&(t_object){cone_prop((t_3f){0.0f,0.0f, 20.0f}, 5.0f), (t_3f){500.0f, 0.0f, -500.0f}, 0xCF0076, 3}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){plane_prop((t_3f){0.0f, 1.0f, 0.0f}), (t_3f){0.0f, 5.0f, 0.0f}, 0xFFFFFF, 2}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){light_prop(500000000000000.0f), (t_3f){0.0f, 0.0f, 0.0f}, 0xFFFF00, 0}, sizeof(t_object));
	ft_lstprint(objects, &print_node);
	return (objects);
}

void	init_camera(t_utils *utils)
{
	utils->rot.x = 0;
	utils->rot.y = 0;
	utils->rot.z = 0;
	utils->cam.origin = (t_3f){0.0f, 0.0f, 0.0f};
	utils->cam.dir.forward = (t_3f){0.0f, 0.0f, -1.0f};
}

void	init_values(t_utils *utils)
{
	utils->closest_object = NULL;
	utils->sel_object = NULL;
	utils->tick = 0;
	utils->visual_rays = 0;
	utils->render = -1;
	utils->elapsed_time = 0;
	utils->font = load_font("libraries/dm_bdf_render/examples/bdf_files/cascadia_code_semi_bold-16.bdf");
	utils->font2 = load_font("libraries/dm_bdf_render/examples/bdf_files/cascadia_code-12.bdf");
	clock_gettime(CLOCK_MONOTONIC, &utils->time);
	utils->add_object_popup = 0;
	utils->dot_radius = 2;
}

void	init_mouse(t_utils *utils)
{
	utils->mouse.move_x = 0;
	utils->mouse.move_y = 0;
	utils->mouse.zoom = 20;
	utils->mouse.x = SCREEN_X / 2;
	utils->mouse.y = SCREEN_Y / 2;
	utils->mouse.button = 0;
}

void	init(t_utils *utils)
{
	utils->mlx = NULL;
	utils->win = NULL;
	init_mouse(utils);
	init_values(utils);
	init_camera(utils);
	utils->objects = init_scene();
	utils->pmatrix = init_pmatrix(&utils->proj);
	utils->rmatrix_x = init_rmatrix_x(0.0f);
	utils->rmatrix_y = init_rmatrix_y(0.0f);
	utils->rmatrix_z = init_rmatrix_z(0.0f);
}
