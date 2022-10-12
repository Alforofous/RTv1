/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/12 15:29:24 by dmalesev         ###   ########.fr       */
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
	t_3f	*origin;
	t_3f	offset;

	if (utils->sel_object != NULL)
	{
		origin = &utils->sel_object->origin;
		offset = scale_vector(utils->cam.dir.forward, utils->multiplier);
		*origin = add_vectors(*origin, offset);
		image_processing(utils, &utils->img[3], 0x000000, 0);
		render_screen(utils);
	}
	(void)x;
	(void)y;
}

void	scroll_wheel_down(t_utils *utils, int x, int y)
{
	t_3f	*origin;
	t_3f	offset;

	if (utils->sel_object != NULL)
	{
		origin = &utils->sel_object->origin;
		offset = scale_vector(utils->cam.dir.forward, utils->multiplier);
		*origin = subtract_vectors(*origin, offset);
		image_processing(utils, &utils->img[3], 0x000000, 0);
		render_screen(utils);
	}
	(void)x;
	(void)y;
}
