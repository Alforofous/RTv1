/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/07 13:59:28 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_object	*select_last(t_list *objects)
{
	while (objects->next != NULL)
	{
		objects = objects->next;
	}
	return ((t_object *)objects->content);
}

static void	add_object_popup(t_utils *utils, int x, int y)
{
	t_3f	object_origin;
	t_dim	dim;

	dim.x0 = utils->img7.dim.x0;
	dim.y0 = utils->img7.dim.y0;
	dim.x1 = utils->img7.dim.x1;
	dim.y1 = dim.y0 + utils->img7.dim.height / 5;
	object_origin = scale_vector(utils->cam.dir.forward, 10);
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){sphere_prop(4.0f), add_vectors(utils->cam.origin, object_origin), 0xDDDDDD, 1}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){sphere_prop(4.0f), add_vectors(utils->cam.origin, object_origin), 0xDDDDDD, 1}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
	dim.y0 = dim.y1;
	dim.y1 = dim.y1 + utils->img7.dim.height / 5;
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){plane_prop(utils->cam.dir.forward), add_vectors(utils->cam.origin, object_origin), 0xDDDDDD, 2}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){plane_prop(utils->cam.dir.forward), add_vectors(utils->cam.origin, object_origin), 0xDDDDDD, 2}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
	dim.y0 = dim.y1;
	dim.y1 = dim.y1 + utils->img7.dim.height / 5;
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){cone_prop(utils->cam.dir.up, 1.0f), add_vectors(utils->cam.origin, object_origin), 0xDDDDDD, 3}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){cone_prop(utils->cam.dir.up, 1.0f), add_vectors(utils->cam.origin, object_origin), 0xDDDDDD, 3}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
	dim.y0 = dim.y1;
	dim.y1 = dim.y1 + utils->img7.dim.height / 5;
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){cylinder_prop(utils->cam.dir.up, 4.0f), add_vectors(utils->cam.origin, object_origin), 0xDDDDDD, 4}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){cylinder_prop(utils->cam.dir.up, 4.0f), add_vectors(utils->cam.origin, object_origin), 0xDDDDDD, 4}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
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
	else if (coords_in_area(&utils->img5.dim, x, y) && utils->sel_object != NULL)
		delete_sel_object(utils, &utils->objects);
	else if (coords_in_area(&utils->img6.dim, x, y))
	{
		utils->add_object_popup = 1;
		utils->img7.dim.x0 = utils->mouse.x;
		utils->img7.dim.y0 = utils->mouse.y;
		utils->img7.dim.x1 = utils->mouse.x + utils->img7.dim.width;
		utils->img7.dim.y1 = utils->mouse.y + utils->img7.dim.height;
	}
	else if (coords_in_area(&utils->img.dim, x, y))
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
