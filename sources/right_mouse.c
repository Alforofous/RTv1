/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:25:27 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 15:26:40 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rot_overflows(t_utils *utils)
{
	if (utils->rot.x > 90)
		utils->rot.x = 90;
	else if (utils->rot.x < -90)
		utils->rot.x = -90;
	if (utils->rot.y > 360)
		utils->rot.y = 0;
	else if (utils->rot.y < 0)
		utils->rot.y = 360;
	if (utils->rot.z > 360)
		utils->rot.z = 0;
	else if (utils->rot.z < 0)
		utils->rot.z = 360;
}

void	move_right_button(t_utils *utils, int x, int y)
{
	utils->rot.y -= (float)utils->mouse.move_x / 4;
	utils->rot.x += (float)utils->mouse.move_y / 4;
	utils->rmatrix_x = init_rmatrix_x(utils->rot.x);
	utils->rmatrix_y = init_rmatrix_y(utils->rot.y);
	utils->rmatrix_z = init_rmatrix_z(utils->rot.z);
	rot_overflows(utils);
	x += 0;
	y += 0;
	render_screen(utils);
	utils->add_object_menu = 0;
}

void	right_button_down(t_utils *u, int x, int y)
{
	u += 0;
	x += 0;
	y += 0;
}
