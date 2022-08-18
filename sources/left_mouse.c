/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/18 15:49:26 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	hold_left_button(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}

void	left_button_down(t_utils *utils, int x, int y)
{
	if (coords_in_img(&utils->img5, x, y))
	{
		delete_sel_object(utils, &utils->objects);
	}
	else if (coords_in_img(&utils->img, x, y))
	{
		x -= utils->img.dim.x0;
		y -= utils->img.dim.y0;
		ray_plotting(utils, &utils->img, (t_2i){x, y});
		if (utils->sel_object == utils->closest_object)
		{
			utils->sel_object = NULL;
			image_processing(utils, &utils->img2, 0x000000);
		}
		else
		{
			ft_putstr("TEST\n");
			utils->sel_object = utils->closest_object;
			image_processing(utils, &utils->img4, 0x000000);
			image_processing(utils, &utils->img5, 0x000000);
			utils->closest_object = NULL;
		}
	}
}

void	left_button_up(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}
