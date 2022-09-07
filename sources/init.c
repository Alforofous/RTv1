/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:50:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/07 15:48:28 by dmalesev         ###   ########.fr       */
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
	t_read_obj	obj;
	
	obj.cone = cone_prop((t_3f){0.0f, 0.0f, 20.0f}, 5.0f);
	if (obj.cone == NULL)
		return (NULL);
	obj.cylinder = cylinder_prop((t_3f){0.0f, 0.0f, 20.0f}, 50.0);
	if (obj.cylinder == NULL)
		return (NULL);
	obj.plane = plane_prop((t_3f){0.0f, 1.0f, 0.0f});
	if (obj.plane == NULL)
		return (NULL);
	obj.light = light_prop(5000.0f);
	if (obj.light == NULL)
		return (NULL);
	objects = ft_lstnew(&(t_object){obj.cone, (t_3f){500.0f, 0.0f, 0.0f}, 0xCF0076, 3}, sizeof(t_object));
	if (objects == NULL)
		return (NULL);
	if (ft_lstappnew(&objects, &(t_object){obj.cylinder, (t_3f){500.0f, -500.0f, 0.0f}, 0x055289, 4}, sizeof(t_object)) == 0)
		return (NULL);
	if (ft_lstappnew(&objects, &(t_object){obj.plane, (t_3f){0.0f, 5.0f, 0.0f}, 0xFFFFFF, 2}, sizeof(t_object)) == 0)
		return (NULL);
	if (ft_lstappnew(&objects, &(t_object){obj.light, (t_3f){250.0f, -200.0f, 0.0f}, 0xFFFF00, 0}, sizeof(t_object)) == 0)
		return (NULL);
	obj.light = light_prop(5000.0f);
	if (obj.light == NULL)
		return (NULL);
	if (ft_lstappnew(&objects, &(t_object){obj.light, (t_3f){0.0f, -10.0f, 0.0f}, 0x7C7CFF, 0}, sizeof(t_object)) == 0)
		return (NULL);
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
	if (utils->objects == NULL)
		close_prog(utils, "Failed to create scene...", -1);
	utils->pmatrix = init_pmatrix(&utils->proj);
	utils->rmatrix_x = init_rmatrix_x(0.0f);
	utils->rmatrix_y = init_rmatrix_y(0.0f);
	utils->rmatrix_z = init_rmatrix_z(0.0f);
}
