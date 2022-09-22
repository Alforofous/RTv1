/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj_to_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:21:34 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 12:30:12 by dmalesev         ###   ########.fr       */
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

void	add_object_popup(t_utils *utils, int x, int y)
{
	t_3f	object_origin;
	t_dim	dim;

	dim.x0 = utils->img[6].dim.x0;
	dim.y0 = utils->img[6].dim.y0;
	dim.x1 = utils->img[6].dim.x1;
	dim.y1 = dim.y0 + utils->img[6].dim.height / 5;
	object_origin = add_vectors(scale_vector(utils->cam.dir.forward, 10), utils->cam.origin);
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){light_prop(40.0f), object_origin, 0xFFFFFF, 0}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){light_prop(40.0f), object_origin, 0xFFFFFF, 0}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
	dim.y0 = dim.y1;
	dim.y1 = dim.y1 + utils->img[6].dim.height / 5;
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){sphere_prop(4.0f), object_origin, 0xDDDDDD, 1}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){sphere_prop(4.0f), object_origin, 0xDDDDDD, 1}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
	dim.y0 = dim.y1;
	dim.y1 = dim.y1 + utils->img[6].dim.height / 5;
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){plane_prop(utils->cam.dir.forward), object_origin, 0xDDDDDD, 2}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){plane_prop(utils->cam.dir.forward), object_origin, 0xDDDDDD, 2}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
	dim.y0 = dim.y1;
	dim.y1 = dim.y1 + utils->img[6].dim.height / 5;
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){cone_prop(utils->cam.dir.forward, 5.0f), object_origin, 0xDDDDDD, 3}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){cone_prop(utils->cam.dir.forward, 5.0f), object_origin, 0xDDDDDD, 3}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
	dim.y0 = dim.y1;
	dim.y1 = dim.y1 + utils->img[6].dim.height / 5;
	if (coords_in_area(&dim, x, y))
	{
		if (utils->objects == NULL)
			utils->objects = ft_lstnew(&(t_object){cylinder_prop(utils->cam.dir.forward, 5.0f), object_origin, 0xDDDDDD, 4}, sizeof(t_object));
		else
			ft_lstappnew(&utils->objects, &(t_object){cylinder_prop(utils->cam.dir.forward, 5.0f), object_origin, 0xDDDDDD, 4}, sizeof(t_object));
		utils->sel_object = select_last(utils->objects);
		render_screen(utils);
	}
}
