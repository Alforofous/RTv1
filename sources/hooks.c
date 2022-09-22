/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:08:09 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 12:26:41 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	on_destroy(void *param)
{
	t_utils	*utils;

	utils = (t_utils *)param;
	close_prog(utils, "Exited program succesfully using [X]", 1);
	return (0);
}

static void	keyboard_hold_key(t_utils *utils)
{
	if ((utils->bitmask_key & BITMASK_NUM_PLUS) == BITMASK_NUM_PLUS && utils->proj.fov < 120)
		utils->proj.fov += 1;
	if ((utils->bitmask_key & BITMASK_NUM_MINUS) == BITMASK_NUM_MINUS && utils->proj.fov > 10)
		utils->proj.fov -= 1;
	if ((utils->bitmask_key & BITMASK_NUM_MINUS) == BITMASK_NUM_MINUS || (utils->bitmask_key & BITMASK_NUM_PLUS) == BITMASK_NUM_PLUS)
		utils->proj.fov_rad = (float)(1 / tan(utils->proj.fov / 2 / 180 * PI));
	if (utils->sel_object != NULL)
	{
		if ((utils->bitmask_key & BITMASK_DEL) == BITMASK_DEL || (utils->bitmask_key & BITMASK_BACKSPACE) == BITMASK_BACKSPACE)
			delete_sel_object(utils, &utils->objects);
		if ((utils->bitmask_key & BITMASK_UP) == BITMASK_UP)
			utils->sel_object->origin = add_vectors(utils->sel_object->origin, utils->cam.dir.forward);
		if ((utils->bitmask_key & BITMASK_LEFT) == BITMASK_LEFT)
			utils->sel_object->origin = add_vectors(utils->sel_object->origin, utils->cam.dir.left);
		if ((utils->bitmask_key & BITMASK_DOWN) == BITMASK_DOWN)
			utils->sel_object->origin = add_vectors(utils->sel_object->origin, utils->cam.dir.back);
		if ((utils->bitmask_key & BITMASK_RIGHT) == BITMASK_RIGHT)
			utils->sel_object->origin = add_vectors(utils->sel_object->origin, utils->cam.dir.right);
	}
	if ((utils->bitmask_key & BITMASK_W) == BITMASK_W)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.forward);
	if ((utils->bitmask_key & BITMASK_A) == BITMASK_A)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.left);
	if ((utils->bitmask_key & BITMASK_S) == BITMASK_S)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.back);
	if ((utils->bitmask_key & BITMASK_D) == BITMASK_D)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.right);
	if ((utils->bitmask_key & BITMASK_SPACE) == BITMASK_SPACE)
		utils->cam.origin = add_vectors(utils->cam.origin, (t_3f){0.0f, -1.0f, 0.0f});
	if ((utils->bitmask_key & BITMASK_L_SHIFT) == BITMASK_L_SHIFT)
		utils->cam.origin = add_vectors(utils->cam.origin, (t_3f){0.0f, 1.0f, 0.0f});
}

int	prog_clock(void *param)
{
	t_utils		*utils;
	//pthread_t	thread_id;

	utils = (t_utils *)param;
	if (utils->bitmask_key != 0)
	{
		keyboard_hold_key(utils);
		utils->rmatrix_x = init_rmatrix_x(utils->rot.x);
		utils->rmatrix_y = init_rmatrix_y(utils->rot.y);
		utils->rmatrix_z = init_rmatrix_z(utils->rot.z);
		render_screen(utils);
	}
	while (utils->density.x >= 0 && utils->density.y >= 0)
	{
		//pthread_create(&thread_id, NULL, &test, (void *)utils);
		//pthread_join(thread_id, NULL);
		image_processing(utils, &utils->img[0], 0xFF000000);
		put_screen(utils);
		utils->density.x -= 1;
	}
	if (utils->density.y > 0 && utils->density.x < 0)
	{
		utils->density.x = 9;
		utils->density.y -= 1;
	}
	if (utils->tick == 0)
	{
	}
	if (utils->tick == 100)
		utils->tick = 0;
	else
		utils->tick += 1;
	return (0);
}
