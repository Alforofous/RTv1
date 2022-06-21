/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:25:27 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/21 15:00:13 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rot_overflows(t_utils *utils)
{
	if (utils->rot.x > 360)
		utils->rot.x = 0;
	else if (utils->rot.x < 0)
		utils->rot.x = 360;
	if (utils->rot.y > 360)
		utils->rot.y = 0;
	else if (utils->rot.y < 0)
		utils->rot.y = 360;
	if (utils->rot.z > 360)
		utils->rot.z = 0;
	else if (utils->rot.z < 0)
		utils->rot.z = 360;
}

void	hold_right_button(t_utils *utils, int x, int y)
{
	utils->rot.y -= (float)utils->mouse.move_x;
	utils->rot.x += (float)utils->mouse.move_y;
	init_rmatrix_x(utils);
	init_rmatrix_y(utils);
	init_rmatrix_z(utils);
	rot_overflows(utils);
	x += 0;
	y += 0;
}

void	right_button_down(t_utils *u, int x, int y)
{
	u += 0;
	x += 0;
	y += 0;
}
