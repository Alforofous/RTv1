/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj_to_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:21:34 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/30 15:02:10 by dmalesev         ###   ########.fr       */
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

void	add_object_menu(t_utils *utils, int x, int y)
{
	t_3f		object_origin;
	t_object	object;
	t_dim		dim[5];
	int			i;

	i = 0;
	while (i < 5)
	{
		dim[i].start.x = utils->img[6].dim.start.x;
		dim[i].start.y = utils->img[6].dim.start.y + (utils->img[6].dim.size.y / 5 * i);
		dim[i].end.x = utils->img[6].dim.end.x;
		dim[i].end.y = dim[i].start.y + utils->img[6].dim.size.y / 5;
		i += 1;
	}
	object_origin = add_vectors(scale_vector(utils->cam.dir.forward, 10), utils->cam.origin);
	if (coords_in_area(&dim[0], x, y))
		object = create_light(object_origin, 0xFFFFFF, 100.0f);
	else if (coords_in_area(&dim[1], x, y))
		object = create_sphere(object_origin, 0xAA0000, 5.0f);
	else if (coords_in_area(&dim[2], x, y))
		object = create_plane(object_origin, 0x009900, utils->cam.dir.forward);
	else if (coords_in_area(&dim[3], x, y))
		object = create_cone(object_origin, 0x004499, scale_vector(utils->cam.dir.forward, 10.f), 10.0f);
	else if (coords_in_area(&dim[4], x, y))
		object = create_cylinder(object_origin, 0x994400, scale_vector(utils->cam.dir.forward, 10.f), 10.0f);
	else
		return ;
	utils->objects = add_object(utils->objects, &object);
	if (utils->objects == NULL)
		close_prog(utils, "Failed to add an object to the scene...", -2);
	utils->sel_object = select_last(utils->objects);
	render_screen(utils);
}
