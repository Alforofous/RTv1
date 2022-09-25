/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/23 15:09:29 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	hold_left_button(t_utils *utils, int x, int y)
{
	utils++;
	x++;
	y++;
}

void	move_left_button(t_utils *utils, int x, int y)
{
	utils++;
	x++;
	y++;
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
	else if (coords_in_area(&utils->img[9].dim, x, y) && utils->sel_object != NULL && utils->property0 != NULL)
		utils->sel_elem = 1;
	else if (coords_in_area(&utils->img[10].dim, x, y) && utils->sel_object != NULL && utils->property0 != NULL)
		utils->sel_elem = 2;
	else if (coords_in_area(&utils->img[11].dim, x, y) && utils->sel_object != NULL && utils->property1 != NULL)
		utils->sel_elem = 3;
	else if (coords_in_area(&utils->img[12].dim, x, y) && utils->sel_object != NULL && utils->property1 != NULL)
		utils->sel_elem = 4;
	else if (coords_in_area(&utils->img[7].dim, x, y) && utils->sel_object != NULL)
		utils->sel_elem = 5;
	else if (coords_in_area(&utils->img[8].dim, x, y))
	{
		utils->light_render *= -1;
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
	utils->sel_elem = 0;
	x += 0;
	y += 0;
}
