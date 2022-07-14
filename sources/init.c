/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:50:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/14 14:33:22 by dmalesev         ###   ########.fr       */
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

void	print_node(t_list *node)
{
	t_object	*object;

	object = (t_object *)node->content;
	if (object->type == 1)
		ft_putstr("Type: Sphere");
	if (object->type == 2)
		ft_putstr("Type: Plane");
	ft_putstr("\tOrigin: [");
	ft_putnbr((int)object->origin.x);
	ft_putchar(' ');
	ft_putnbr((int)object->origin.y);
	ft_putchar(' ');
	ft_putnbr((int)object->origin.z);
	ft_putchar(']');
}

t_list *init_scene()
{
	t_list	*objects;

	objects = ft_lstnew(&(t_object){(t_3f){0.0f, 0.0f, -10.0f}, (t_3f){0.0f, 0.0f, 0.0f},0x880000, 4.0f, 1}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){(t_3f){-25.0f, -20.0f, -10.0f}, (t_3f){0.0f, 0.0f, 0.0f}, 0xFFFFFF, 100.0f, 1}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){(t_3f){-10.0f, -2.0f, -10.0f}, (t_3f){0.0f, 0.0f, 0.0f}, 0x004488, 10.0f, 1}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){(t_3f){5.0f, -10.0f, 10.0f}, (t_3f){0.0f, 0.0f, 0.0f}, 0x004488, 50.0f, 1}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){(t_3f){0.0f, 0.0f, 100.0f}, (t_3f){0.0f, 0.0f, 0.0f}, 0x004422, 200.0f, 1}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){(t_3f){0.0f, 0.1f, 0.0f}, (t_3f){0.0f, -1.0f, 0.0f}, 0xFFFFFF, 0.0f, 2}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){(t_3f){0.0f, 0.1f, 0.0f}, (t_3f){0.0f, 1.0f, 0.0f}, 0xFFFFFF, 0.0f, 2}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){(t_3f){0.0f, 0.0f, -10.0f}, (t_3f){0.0f, 0.0f, 0.0f},0xFFFFFF, 1.0f, 1}, sizeof(t_object));
	ft_lstappnew(&objects, &(t_object){(t_3f){0.0f, 0.0f, -20.0f}, (t_3f){0.0f, 0.0f, -1.0f}, 0xDD3300, 0.0f, 2}, sizeof(t_object));
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
	utils->curr_object = NULL;
	utils->tick = 0;
	utils->visual_rays = 0;
	utils->render = -1;
	utils->elapsed_time = 0;
	clock_gettime(CLOCK_MONOTONIC, &utils->time);
	utils->light[0].color.x = 0.0f;
	utils->light[0].color.y = 1.0f;
	utils->light[0].color.z = 1.0f;
	utils->light[0].lumen = 50.0;
	utils->light[0].origin = (t_3f){0.0f, 0.0f, 0.0f};
	utils->light[1].color.x = 1.0f;
	utils->light[1].color.y = 0.0f;
	utils->light[1].color.z = 0.0f;
	utils->light[1].lumen = 20.0;
	utils->light[1].origin = (t_3f){5.0f, 0.0f, 0.0f};
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
	init_matrix(&utils->pmatrix);
	init_matrix(&utils->rmatrix_x);
	init_matrix(&utils->rmatrix_y);
	init_matrix(&utils->rmatrix_z);
	utils->pmatrix = init_pmatrix(&utils->proj);
	utils->rmatrix_x = init_rmatrix_x(0.0f);
	utils->rmatrix_y = init_rmatrix_y(0.0f);
	utils->rmatrix_z = init_rmatrix_z(0.0f);
}
