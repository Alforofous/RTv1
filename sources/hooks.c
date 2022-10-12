/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:08:09 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/12 17:10:46 by dmalesev         ###   ########.fr       */
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

int	prog_clock(void *param)
{
	t_utils		*utils;

	utils = (t_utils *)param;
	if (utils->density.x >= 0 && utils->density.y >= 0)
	{
		image_processing(utils, &utils->img[0], 0xFF000000, 0);
		put_images_to_window(utils);
		utils->density.x -= 1;
	}
	if (utils->density.y > 0 && utils->density.x < 0)
	{
		utils->density.x = 5;
		utils->density.y -= 1;
	}
	if (utils->bitmask_key != 0)
	{
		if (time_since_success(0.01, 1) >= 0.01)
		{
			keyboard_hold_key(utils->bitmask_key, utils);
			render_screen(utils);
		}
	}
	if (utils->sel_elem > 0)
	{
		mouse_hold_elem(utils, utils->sel_elem);
		mouse_move(utils->mouse.x, utils->mouse.y, (void *)utils);
	}
	return (0);
}
