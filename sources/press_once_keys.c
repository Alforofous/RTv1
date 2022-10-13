/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_once_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:04:21 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/13 15:55:29 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Keys that toggle option on or off*/
static int	toogle_keys(t_utils *utils, int key)
{
	if (key == R)
	{
		utils->render *= -1;
		render_screen(utils);
	}
	else if (key == L)
	{
		utils->rend_lights *= -1;
		render_screen(utils);
		image_processing(utils, &utils->img[9], 0x000000, 1);
	}
	else if (key == DOT)
	{
		utils->visual_rays += 1;
		if (utils->visual_rays >= 1)
			image_processing(utils, &utils->img[2], 0x98004575, 1);
		if (utils->visual_rays == 3)
			utils->visual_rays = 0;
	}
	else
		return (0);
	return (1);
}

static t_3f	align_axis(t_3f vector)
{
	vector.x = (float)((int)vector.x);
	vector.y = (float)((int)vector.y);
	vector.z = (float)((int)vector.z);
	return (vector);
}

static int	modify_objects_properties(t_utils *utils, int key)
{
	if (key == L_CTRL)
	{
		if (utils->sel_object != NULL)
			utils->sel_object->origin = align_axis(utils->sel_object->origin);
		else
			utils->cam.origin = align_axis(utils->cam.origin);
	}
	else if (key == T)
	{
		init_camera(utils);
		utils->rmatrix_x = init_rmatrix_x(utils->rot.x);
		utils->rmatrix_y = init_rmatrix_y(utils->rot.y);
		utils->rmatrix_z = init_rmatrix_z(utils->rot.z);
		image_processing(utils, &utils->img[1], 0x000000, 0);
		render_screen(utils);
	}
	else if (key == DEL || key == BACKSPACE)
		delete_sel_object(utils, &utils->scene);
	else
		return (0);
	return (1);
}

static int	shadow_bias(t_utils *utils, int key)
{
	if (key == Q && utils->shadow_bias > 0.0001f)
		utils->shadow_bias /= 10.0f;
	else if (key == E && utils->shadow_bias < 100.0f)
		utils->shadow_bias *= 10.0f;
	else
		return (0);
	image_processing(utils, &utils->img[1], 0x000000, 0);
	render_screen(utils);
	return (1);
}

void	press_once(t_utils *utils, int key)
{
	if (toogle_keys(utils, key))
	{
	}
	else if (modify_objects_properties(utils, key))
	{
	}
	else if (shadow_bias(utils, key))
	{
	}
	else if (key == Y)
	{
		utils->sel_object = select_last(utils->scene);
		image_processing(utils, &utils->img[3], 0x000000, 1);
		image_processing(utils, &utils->img[6], 0x000000, 0);
	}
	else if (key == C)
	{
		utils->multiplier *= 10.0f;
		if (utils->multiplier > 10.0f)
			utils->multiplier = 0.1f;
		image_processing(utils, &utils->img[1], 0x000000, 0);
	}
	else
		return ;
}
