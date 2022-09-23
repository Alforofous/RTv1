/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/23 14:42:33 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	hold_left_button(t_utils *utils, int x, int y)
{
	if (utils->property[0] == 1)
	{
		if (coords_in_area(&utils->img[9].dim, x, y) && utils->sel_object != NULL)
		{
			change_obj_property(utils->sel_object, -1.0f);
			render_screen(utils);
		}
		else if (coords_in_area(&utils->img[10].dim, x, y) && utils->sel_object != NULL)
		{
			change_obj_property(utils->sel_object, 1.0f);
			render_screen(utils);
		}
	}
}

void	move_left_button(t_utils *utils, int x, int y)
{
	if (coords_in_area(&utils->img[7].dim, x, y) && utils->sel_object != NULL)
	{
		x -= utils->img[7].dim.x0;
		y -= utils->img[7].dim.y0;
		change_obj_color(&utils->img[7], utils->sel_object, x, y);
		render_screen(utils);
	}
}

void	left_button_down(t_utils *utils, int x, int y)
{
	if (utils->add_object_menu == 1)
	{
		add_object_menu(utils, x, y);
		utils->add_object_menu = 0;
	}
	else if (coords_in_area(&utils->img[4].dim, x, y) && utils->sel_object != NULL)
		delete_sel_object(utils, &utils->objects);
	else if (coords_in_area(&utils->img[8].dim, x, y))
	{
		utils->light_render *= -1;
		render_screen(utils);
	}
	else if (coords_in_area(&utils->img[7].dim, x, y) && utils->sel_object != NULL)
	{
		x -= utils->img[7].dim.x0;
		y -= utils->img[7].dim.y0;
		change_obj_color(&utils->img[7], utils->sel_object, x, y);
		render_screen(utils);
	}
	else if (coords_in_area(&utils->img[5].dim, x, y))
	{
		utils->add_object_menu = 1;
		utils->img[6].dim.x0 = utils->mouse.x;
		utils->img[6].dim.y0 = utils->mouse.y;
		utils->img[6].dim.x1 = utils->mouse.x + utils->img[6].dim.width;
		utils->img[6].dim.y1 = utils->mouse.y + utils->img[6].dim.height;
	}
	else if (coords_in_area(&utils->img[0].dim, x, y))
	{
		x -= utils->img[0].dim.x0;
		y -= utils->img[0].dim.y0;
		ray_plotting(utils, &utils->img[0], (t_2i){x, y});
		if (utils->sel_object == utils->closest_object)
		{
			utils->sel_object = NULL;
			image_processing(utils, &utils->img[1], 0x000000);
			image_processing(utils, &utils->img[5], 0x000000);
		}
		else
		{
			utils->sel_object = utils->closest_object;
			image_processing(utils, &utils->img[3], 0x000000);
			image_processing(utils, &utils->img[4], 0x000000);
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
