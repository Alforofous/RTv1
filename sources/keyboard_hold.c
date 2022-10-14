/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_hold.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:26:29 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 15:01:04 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	move_camera(long int bmk, t_utils *utils, t_3f *origin, t_dir *dir)
{
	float		multiplier;
	long int	bitmask_move;

	multiplier = utils->multiplier;
	bitmask_move = (BITMASK_W | BITMASK_A | BITMASK_S | BITMASK_D);
	bitmask_move |= (BITMASK_SPACE | BITMASK_L_SHIFT);
	if ((bmk & BITMASK_W) == BITMASK_W)
		*origin = add_vectors(*origin, scale_vector(dir->forward, multiplier));
	if ((bmk & BITMASK_A) == BITMASK_A)
		*origin = add_vectors(*origin, scale_vector(dir->left, multiplier));
	if ((bmk & BITMASK_S) == BITMASK_S)
		*origin = add_vectors(*origin, scale_vector(dir->back, multiplier));
	if ((bmk & BITMASK_D) == BITMASK_D)
		*origin = add_vectors(*origin, scale_vector(dir->right, multiplier));
	if ((bmk & BITMASK_SPACE) == BITMASK_SPACE)
		*origin = add_vectors(*origin, (t_3f){0.0f, multiplier, 0.0f});
	if ((bmk & BITMASK_L_SHIFT) == BITMASK_L_SHIFT)
		*origin = add_vectors(*origin, (t_3f){0.0f, -multiplier, 0.0f});
	if (utils->visual_rays >= 1)
		image_processing(utils, &utils->img[2], 0x98004575, 0);
	if ((bmk & bitmask_move) != 0)
		image_processing(utils, &utils->img[1], 0x000000, 0);
	put_images_to_window(utils);
}

static void	move_object(long int bmk, t_utils *utils, t_3f *origin, t_dir *dir)
{
	float	multiplier;

	multiplier = utils->multiplier;
	if ((bmk & BITMASK_UP) == BITMASK_UP)
		*origin = add_vectors(*origin, scale_vector(dir->forward, multiplier));
	if ((bmk & BITMASK_LEFT) == BITMASK_LEFT)
		*origin = add_vectors(*origin, scale_vector(dir->left, multiplier));
	if ((bmk & BITMASK_DOWN) == BITMASK_DOWN)
		*origin = add_vectors(*origin, scale_vector(dir->back, multiplier));
	if ((bmk & BITMASK_RIGHT) == BITMASK_RIGHT)
		*origin = add_vectors(*origin, scale_vector(dir->right, multiplier));
	image_processing(utils, &utils->img[3], 0x000000, 1);
}

static void	change_fov(float *fov, float *fov_rad, float value)
{
	*fov += value;
	*fov_rad = 1.0f / tanf(*fov / 2.0f / 180.0f * (float)PI);
}

void	keyboard_hold_key(long int bmk, t_utils *utils, t_dir *dir)
{
	if (utils->sel_object != NULL)
		move_object(bmk, utils, &utils->sel_object->origin, dir);
	if ((bmk & BITMASK_NUM_PLUS) == BITMASK_NUM_PLUS && utils->proj.fov < 160)
		change_fov(&utils->proj.fov, &utils->proj.fov_rad, 1.0f);
	if ((bmk & BITMASK_NUM_MINUS) == BITMASK_NUM_MINUS && utils->proj.fov > 5)
		change_fov(&utils->proj.fov, &utils->proj.fov_rad, -1.0f);
	move_camera(bmk, utils, &utils->cam.origin, dir);
	image_processing(utils, &utils->img[1], 0x000000, 0);
}
