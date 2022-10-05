/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/05 17:04:27 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	hold_left_button(t_utils *utils, int x, int y)
{
	if (coords_in_area(utils->img[5].dim, x, y) && utils->sel_object != NULL)
	{
		x -= utils->img[5].dim.start.x;
		y -= utils->img[5].dim.start.y;
		utils->sel_object->color = rgb_slider(&utils->img[5], &(t_2i){x, y});
		render_screen(utils);
	}
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
	else if (coords_in_area(utils->img[6].dim, x, y) && utils->sel_object != NULL)
	{
		delete_sel_object(utils, &utils->objects);
	}
	else if (coords_in_area(utils->img[9].dim, x, y) && utils->sel_object != NULL && utils->property[0] != NULL)
		utils->sel_elem = 1;
	else if (coords_in_area(utils->img[10].dim, x, y) && utils->sel_object != NULL && utils->property[0] != NULL)
		utils->sel_elem = 2;
	/*else if (coords_in_area(utils->img[5], x, y) && utils->sel_object != NULL && utils->property[1] != NULL)
		utils->sel_elem = 3;
	else if (coords_in_area(utils->img[6], x, y) && utils->sel_object != NULL && utils->property[1] != NULL)
		utils->sel_elem = 4;*/
	else if (coords_in_area(utils->img[8].dim, x, y))
	{
		utils->light_render *= -1;
		render_screen(utils);
	}
	else if (coords_in_area(utils->img[7].dim, x, y))
	{
		utils->add_object_menu = 1;
		utils->img[4].dim.start.x = utils->mouse.x;
		utils->img[4].dim.start.y = utils->mouse.y;
		utils->img[4].dim.end.x = utils->mouse.x + utils->img[4].dim.size.x;
		utils->img[4].dim.end.y = utils->mouse.y + utils->img[4].dim.size.y;
	}
	else if (coords_in_area(utils->img[0].dim, x, y))
	{
		x -= utils->img[0].dim.start.x;
		y -= utils->img[0].dim.start.y;
		ray_plotting(utils, &utils->img[0], (t_2i){x, y});
		if (utils->sel_object == utils->closest_object)
			utils->sel_object = NULL;
		else
			utils->sel_object = utils->closest_object;
		if (utils->sel_object != NULL)
		{
			image_processing(utils, &utils->img[3], 0x000000);
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
