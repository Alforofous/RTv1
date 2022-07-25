/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:01:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/25 16:41:43 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Keys that toggle option on or off*/
void	toggle_keys(t_utils *utils, int key)
{
	if (key == DOT)
		utils->visual_rays += 1;
	if (utils->visual_rays == 3)
		utils->visual_rays = 0;
	if (key == T)
		init_camera(utils);
	if (key == R)
		utils->render *= -1;
	utils->rmatrix_x = init_rmatrix_x(utils->rot.x);
	utils->rmatrix_y = init_rmatrix_y(utils->rot.y);
	utils->rmatrix_z = init_rmatrix_z(utils->rot.z);
}

void	fov_keys(t_utils *utils, int key)
{
	if (key == NUM_PLUS && utils->proj.fov < 120)
		utils->proj.fov += 1;
	else if (key == NUM_MINUS && utils->proj.fov > 10)
		utils->proj.fov -= 1;
	utils->proj.fov_rad = (float)(1 / tan(utils->proj.fov / 2 / 180 * PI));
}

static void	moving_object(t_utils *utils, t_object *sel_object, int key)
{
	if (key == UP)
		sel_object->origin = add_vectors(&sel_object->origin,
			&utils->cam.dir.forward);
	if (key == LEFT)
		sel_object->origin = add_vectors(&sel_object->origin,
			&utils->cam.dir.left);
	if (key == DOWN)
		sel_object->origin = add_vectors(&sel_object->origin,
			&utils->cam.dir.back);
	if (key == RIGHT)
		sel_object->origin = add_vectors(&sel_object->origin,
			&utils->cam.dir.right);
}

void	moving_camera(t_utils *utils, int key)
{
	if (key == W)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.forward);
	if (key == A)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.left);
	if (key == S)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.back);
	if (key == D)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.right);
	if (key == SPACE)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.down);
	if (key == L_SHIFT)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.up);
}

int	key_down(int key, void *param)
{
	t_utils	*utils;

	utils = param;
	ft_putnbr(key);
	if (key == ESC)
		close_prog(utils, "Exited program succesfully using ESC.", 1);
	moving_camera(utils, key);
	moving_object(utils, utils->sel_object, key);
	fov_keys(utils, key);
	toggle_keys(utils, key);
	render_screen(utils);
	return (0);
}
