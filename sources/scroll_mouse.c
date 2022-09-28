/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/28 09:47:34 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scroll_wheel(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}

void	scroll_wheel_up(t_utils *utils, int x, int y)
{
	if (utils->sel_object != NULL)
	{
		utils->sel_object->origin = add_vectors(utils->sel_object->origin, scale_vector(utils->cam.dir.forward, utils->multiplier));
		render_screen(utils);
	}
	x += 0;
	y += 0;
}

void	scroll_wheel_down(t_utils *utils, int x, int y)
{
	if (utils->sel_object != NULL)
	{
		utils->sel_object->origin = add_vectors(utils->sel_object->origin, scale_vector(utils->cam.dir.back, utils->multiplier));
		render_screen(utils);
	}
	x += 0;
	y += 0;
}
