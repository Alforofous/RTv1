/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/24 11:30:34 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	add_object_popup(t_utils *utils, int x, int y)
{
	if (coords_in_img(&utils->img7, x, y))
		ft_lstappnew(&utils->objects, &(t_object){utils->cam.origin, (t_3f){0.0f, 0.0f, 0.0f}, 0xDD3300, 1.5f, 1}, sizeof(t_object));
	utils->add_object_popup = 0;
}

void	hold_left_button(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}

void	left_button_down(t_utils *utils, int x, int y)
{
	if (utils->add_object_popup == 1)
		add_object_popup(utils, x, y);
	else if (coords_in_img(&utils->img5, x, y) && utils->sel_object != NULL)
		delete_sel_object(utils, &utils->objects);
	else if (coords_in_img(&utils->img6, x, y))
	{
		utils->add_object_popup = 1;
		utils->img7.dim.x0 = utils->mouse.x;
		utils->img7.dim.y0 = utils->mouse.y;
		utils->img7.dim.x1 = utils->mouse.x + utils->img7.dim.width;
		utils->img7.dim.y1 = utils->mouse.y + utils->img7.dim.height;
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
			image_processing(utils, &utils->img6, 0x000000);
		}
		else
		{
			utils->sel_object = utils->closest_object;
			image_processing(utils, &utils->img4, 0x000000);
			image_processing(utils, &utils->img5, 0x000000);
			utils->closest_object = NULL;
		}
	}
	put_screen(utils);
}

void	left_button_up(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}
