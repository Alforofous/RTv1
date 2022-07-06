/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:50:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/05 16:23:03 by dmalesev         ###   ########.fr       */
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

void	init_scene(t_list *objects)
{
	t_sphere	sphere[2];
	t_plane		plane[2];

	sphere[0] = (t_sphere){(t_3f){0.0f, 0.0f, -10.0f}, 4.0f, 0x880000};
	sphere[1] = (t_sphere){(t_3f){-5.0f, 2.0f, -10.0f}, 4.0f, 0x004488};
	plane[0] = (t_plane){(t_3f){0.0f, 0.1f, 0.0f}, (t_3f){0.0f, 1.0f, 0.0f}, 0xDD7700};
	plane[0] = (t_plane){(t_3f){0.0f, 0.1f, 0.0f}, (t_3f){0.0f, -1.0f, 0.0f}, 0xDD7700};
	objects = ft_lstnew(&sphere[0], sizeof(t_sphere));
	ft_lstappnew(&objects, &sphere[1], sizeof(t_sphere));
	ft_lstappnew(&objects, &plane[0], sizeof(t_plane));
	ft_lstappnew(&objects, &plane[1], sizeof(t_plane));
}

void	init_values(t_utils *utils)
{
	utils->tick = 0;
	utils->reference = -1;
	utils->visual_rays = -1;
	utils->rot.x = 0;
	utils->rot.y = 0;
	utils->rot.z = 0;
	utils->cam.origin = (t_3f){0.0f, 0.0f, 0.0f};
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
	init_scene(utils->objects);
	init_matrix(&utils->pmatrix);
	init_matrix(&utils->rmatrix_x);
	init_matrix(&utils->rmatrix_y);
	init_matrix(&utils->rmatrix_z);
	utils->pmatrix = init_pmatrix(&utils->proj);
	utils->rmatrix_x = init_rmatrix_x(0.0f);
	utils->rmatrix_y = init_rmatrix_y(0.0f);
	utils->rmatrix_z = init_rmatrix_z(0.0f);
}
