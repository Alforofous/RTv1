/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:08:09 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/10 14:11:44 by dmalesev         ###   ########.fr       */
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

static int	sel_object_keys(t_utils *utils)
{
	if (utils->sel_object != NULL)
	{
		if ((utils->bitmask_key & BITMASK_DEL) == BITMASK_DEL || (utils->bitmask_key & BITMASK_BACKSPACE) == BITMASK_BACKSPACE)
			delete_sel_object(utils, &utils->objects);
		if ((utils->bitmask_key & BITMASK_UP) == BITMASK_UP)
			utils->sel_object->origin = add_vectors(utils->sel_object->origin, scale_vector(utils->cam.dir.forward, utils->multiplier));
		if ((utils->bitmask_key & BITMASK_LEFT) == BITMASK_LEFT)
			utils->sel_object->origin = add_vectors(utils->sel_object->origin, scale_vector(utils->cam.dir.left, utils->multiplier));
		if ((utils->bitmask_key & BITMASK_DOWN) == BITMASK_DOWN)
			utils->sel_object->origin = add_vectors(utils->sel_object->origin, scale_vector(utils->cam.dir.back, utils->multiplier));
		if ((utils->bitmask_key & BITMASK_RIGHT) == BITMASK_RIGHT)
			utils->sel_object->origin = add_vectors(utils->sel_object->origin, scale_vector(utils->cam.dir.right, utils->multiplier));
		image_processing(utils, &utils->img[3], 0x000000);
		return (1);
	}
	return (0);
}

static void	keyboard_hold_key(t_utils *utils)
{
	sel_object_keys(utils);
	if ((utils->bitmask_key & BITMASK_NUM_PLUS) == BITMASK_NUM_PLUS && utils->proj.fov < 160)
		utils->proj.fov += 1;
	if ((utils->bitmask_key & BITMASK_NUM_MINUS) == BITMASK_NUM_MINUS && utils->proj.fov > 5)
		utils->proj.fov -= 1;
	if ((utils->bitmask_key & BITMASK_NUM_MINUS) == BITMASK_NUM_MINUS || (utils->bitmask_key & BITMASK_NUM_PLUS) == BITMASK_NUM_PLUS)
		utils->proj.fov_rad = (float)(1 / tan(utils->proj.fov / 2 / 180 * PI));
	if ((utils->bitmask_key & BITMASK_W) == BITMASK_W)
		utils->cam.origin = add_vectors(utils->cam.origin, scale_vector(utils->cam.dir.forward, utils->multiplier));
	if ((utils->bitmask_key & BITMASK_A) == BITMASK_A)
		utils->cam.origin = add_vectors(utils->cam.origin, scale_vector(utils->cam.dir.left,  utils->multiplier));
	if ((utils->bitmask_key & BITMASK_S) == BITMASK_S)
		utils->cam.origin = add_vectors(utils->cam.origin, scale_vector(utils->cam.dir.back, utils->multiplier));
	if ((utils->bitmask_key & BITMASK_D) == BITMASK_D)
		utils->cam.origin = add_vectors(utils->cam.origin, scale_vector(utils->cam.dir.right, utils->multiplier));
	if ((utils->bitmask_key & BITMASK_SPACE) == BITMASK_SPACE)
		utils->cam.origin = add_vectors(utils->cam.origin, (t_3f){0.0f, -1.0f * utils->multiplier, 0.0f});
	if ((utils->bitmask_key & BITMASK_L_SHIFT) == BITMASK_L_SHIFT)
		utils->cam.origin = add_vectors(utils->cam.origin, (t_3f){0.0f, 1.0f * utils->multiplier, 0.0f});
	image_processing(utils, &utils->img[2], 0x98004575);
	image_processing(utils, &utils->img[1], 0x000000);
}

static void	mouse_hold_elem(t_utils *utils, int	elem)
{
	t_2i	coords;

	if (elem == 1)
		*(utils->property[0]) -= 1.0f * utils->multiplier;
	else if (elem == 2)
		*(utils->property[0]) += 1.0f * utils->multiplier;
	else if (elem == 3)
		*(utils->property[1]) -= 1.0f * utils->multiplier;
	else if (elem == 4)
		*(utils->property[1]) += 1.0f * utils->multiplier;
	else if (elem == 5)
	{
		coords = (t_2i){utils->mouse.x, utils->mouse.y};
		coords.x -= utils->img[5].dim.start.x;
		coords.y -= utils->img[5].dim.start.y;
		coords.x = ft_max(coords.x, 0);
		coords.y = ft_max(coords.y, 0);
		coords.x = ft_min(coords.x, utils->img[5].dim.size.x - 1);
		coords.y = ft_min(coords.y, utils->img[5].dim.size.y - 1);
		utils->sel_object->rgb = rgb_slider(&utils->img[5], &coords);
		utils->sel_object->color = shade_picker(&utils->img[6], &utils->sel_object->shade_coords, utils->sel_object->rgb);
		image_processing(utils, &utils->img[6], 0x000000);
	}
	else if (elem == 6)
	{
		utils->sel_object->shade_coords = (t_2i){utils->mouse.x, utils->mouse.y};
		utils->sel_object->shade_coords.x -= utils->img[6].dim.start.x;
		utils->sel_object->shade_coords.y -= utils->img[6].dim.start.y;
		utils->sel_object->shade_coords.x = ft_max(utils->sel_object->shade_coords.x, 0);
		utils->sel_object->shade_coords.y = ft_max(utils->sel_object->shade_coords.y, 0);
		utils->sel_object->shade_coords.x = ft_min(utils->sel_object->shade_coords.x, utils->img[6].dim.size.x - 1);
		utils->sel_object->shade_coords.y = ft_min(utils->sel_object->shade_coords.y, utils->img[6].dim.size.y - 1);
		utils->sel_object->color = shade_picker(&utils->img[6], &utils->sel_object->shade_coords, utils->sel_object->rgb);
		image_processing(utils, &utils->img[6], 0x000000);
	}
	else
		return ;
	image_processing(utils, &utils->img[3], 0x000000);
	render_screen(utils);
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
	if (utils->sel_elem > 0)
		mouse_hold_elem(utils, utils->sel_elem);
	while (utils->density.x >= 0 && utils->density.y >= 0)
	{
		//pthread_create(&thread_id, NULL, &test, (void *)utils);
		//pthread_join(thread_id, NULL);
		image_processing(utils, &utils->img[0], 0xFF000000);
		put_images_to_window(utils);
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
