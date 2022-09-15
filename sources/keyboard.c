/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:01:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/14 12:28:56 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Keys that toggle option on or off*/
void	toggle_keys(t_utils *utils, int key)
{
	if (key == DOT)
		utils->visual_rays += 1;
	else if (key == T)
		init_camera(utils);
	else if (key == R)
		utils->render *= -1;
	else
		return ;
	if (utils->visual_rays == 3)
		utils->visual_rays = 0;
	utils->rmatrix_x = init_rmatrix_x(utils->rot.x);
	utils->rmatrix_y = init_rmatrix_y(utils->rot.y);
	utils->rmatrix_z = init_rmatrix_z(utils->rot.z);
	render_screen(utils);
}

void	fov_keys(t_utils *utils, int key)
{
	if (key == NUM_PLUS && utils->proj.fov < 120)
		utils->proj.fov += 1;
	else if (key == NUM_MINUS && utils->proj.fov > 10)
		utils->proj.fov -= 1;
	else
		return ;
	utils->proj.fov_rad = (float)(1 / tan(utils->proj.fov / 2 / 180 * PI));
	render_screen(utils);
}

static void	moving_object(t_utils *utils, t_object *sel_object, int key)
{
	if (key == UP)
		sel_object->origin = add_vectors(sel_object->origin, utils->cam.dir.forward);
	else if (key == LEFT)
		sel_object->origin = add_vectors(sel_object->origin, utils->cam.dir.left);
	else if (key == DOWN)
		sel_object->origin = add_vectors(sel_object->origin, utils->cam.dir.back);
	else if (key == RIGHT)
		sel_object->origin = add_vectors(sel_object->origin, utils->cam.dir.right);
	else
		return ;
	render_screen(utils);
}

void	moving_camera(t_utils *utils, int key)
{
	if (key == W)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.forward);
	else if (key == A)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.left);
	else if (key == S)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.back);
	else if (key == D)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.right);
	else if (key == SPACE)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.down);
	else if (key == L_SHIFT)
		utils->cam.origin = add_vectors(utils->cam.origin, utils->cam.dir.up);
	else
		return ;
	render_screen(utils);
}

int	key_down(int key, void *param)
{
	t_utils	*utils;

	utils = param;
	ft_putnbr(key);
	if (key == DEL)
		delete_sel_object(utils, &utils->objects);
	if (key == BACKSPACE)
		delete_sel_object(utils, &utils->objects);
	moving_camera(utils, key);
	if (utils->sel_object != NULL)
		moving_object(utils, utils->sel_object, key);
	fov_keys(utils, key);
	toggle_keys(utils, key);
	utils->add_object_popup = 0;
	return (0);
}

int	key_up(int key, void *param)
{
	t_utils	*utils;

	utils = param;
	(void)key;
	utils->add_object_popup = 0;
	return (0);
}
