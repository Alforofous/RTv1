/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:49:27 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/24 20:42:18 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	mouse_move(int x, int y, void *param)
{
	t_utils	*utils;

	utils = param;
	utils->mouse.move_x = x - utils->mouse.x;
	utils->mouse.move_y = y - utils->mouse.y;
	utils->mouse.x = x;
	utils->mouse.y = y;
	if ((utils->mouse.button & RIGHT_BUTTON) == RIGHT_BUTTON)
	{
		hold_right_button(utils, x, y);
	}
	if ((utils->mouse.button & 1) == 1)
	{
		hold_left_button(utils, x, y);
	}
	if (utils->mouse.button > 0)
	{
	}
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_utils	*utils;

	utils = param;
	button = int_to_bit(button);
	utils->mouse.x = x;
	utils->mouse.y = y;
	if ((utils->mouse.button & 1) == 1)
		left_button_up(utils, x, y);
	if (button < 8)
		utils->mouse.button -= button;
	return (0);
}

int	mouse_down(int button, int x, int y, void *param)
{
	t_utils	*utils;

	utils = param;
	button = int_to_bit(button);
	utils->mouse.x = x;
	utils->mouse.y = y;
	if ((button & 8) == 8 || (button & 16) == 16)
		scroll_wheel(utils, x, y);
	if ((button & 8) == 8)
		scroll_wheel_up(utils, x, y);
	if ((button & 16) == 16)
		scroll_wheel_down(utils, x, y);
	if ((button & 1) == 1)
		left_button_down(utils, x, y);
	if ((button & 2) == 2)
		right_button_down(utils, x, y);
	if (button < 8)
		utils->mouse.button += button;
	return (0);
}
