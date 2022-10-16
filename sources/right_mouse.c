/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:25:27 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/16 13:09:54 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rot_overflows(t_utils *utils)
{
	if (utils->cam.rot.x > 90)
		utils->cam.rot.x = 90;
	else if (utils->cam.rot.x < -90)
		utils->cam.rot.x = -90;
	if (utils->cam.rot.y > 360)
		utils->cam.rot.y = 0;
	else if (utils->cam.rot.y < 0)
		utils->cam.rot.y = 360;
	if (utils->cam.rot.z > 360)
		utils->cam.rot.z = 0;
	else if (utils->cam.rot.z < 0)
		utils->cam.rot.z = 360;
}

void	move_right_button(t_utils *utils, int x, int y)
{
	utils->cam.rot.y -= (double)utils->mouse.move.x / 4;
	utils->cam.rot.x -= (double)utils->mouse.move.y / 4;
	rot_overflows(utils);
	if (utils->visual_rays >= 1)
		image_processing(utils, &utils->img[2], 0x98004575, 1);
	render_screen(utils);
	utils->add_object_menu = 0;
	x += 0;
	y += 0;
}
