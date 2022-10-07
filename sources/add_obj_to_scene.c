/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj_to_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:21:34 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/07 14:13:03 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	*select_last(t_list *objects)
{
	while (objects->next != NULL)
	{
		objects = objects->next;
	}
	return ((t_object *)objects->content);
}

t_list	*add_object(t_list *objects, t_object *object)
{
	if (objects == NULL)
	{
		objects = ft_lstnew(object, sizeof(t_object));
		if (objects == NULL)
			return (NULL);
	}
	else
	{
		if (ft_lstappnew(&objects, object, sizeof(t_object)) == 0)
			return (NULL);
	}
	return (objects);
}

static void	button_dimensions(t_dim *button, t_dim img_dim)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		button[i].start.x = img_dim.start.x;
		button[i].start.y = img_dim.start.y + (img_dim.size.y / 5 * i);
		button[i].end.x = img_dim.end.x;
		button[i].end.y = button[i].start.y + img_dim.size.y / 5;
		i += 1;
	}
}

void	add_object_menu(t_utils *utils, int x, int y)
{
	t_3f		origin;
	t_3f		axis;
	t_object	object;
	t_dim		button[5];

	button_dimensions(button, utils->img[4].dim);
	origin = scale_vector(utils->cam.dir.forward, 30.0f);
	origin = add_vectors(origin, utils->cam.origin);
	axis = scale_vector(utils->cam.dir.forward, 30.0f);
	if (coords_in_area(button[0], x, y))
		object = create_light(origin, 0xFFFFFF, 100.0f);
	else if (coords_in_area(button[1], x, y))
		object = create_sphere(origin, 0xAA0000, 5.0f);
	else if (coords_in_area(button[2], x, y))
		object = create_plane(origin, 0x009900, utils->cam.dir.forward);
	else if (coords_in_area(button[3], x, y))
		object = create_cone(origin, 0x004499, axis, 10.0f);
	else if (coords_in_area(button[4], x, y))
		object = create_cylinder(origin, 0x994400, axis, 10.0f);
	else
		return ;
	utils->objects = add_object(utils->objects, &object);
	if (utils->objects == NULL)
		close_prog(utils, "Failed to add an object to the scene...", -2);
	utils->sel_object = select_last(utils->objects);
}
