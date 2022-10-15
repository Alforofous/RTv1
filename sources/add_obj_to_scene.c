/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj_to_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:21:34 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 12:57:09 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	*select_next_object(t_list *scene, t_object *sel_object)
{
	if (scene && sel_object == NULL)
		return ((t_object *)scene->content);
	while (scene && scene->next != NULL)
	{
		if (sel_object == (t_object *)(scene->content))
			return ((t_object *)scene->next->content);
		scene = scene->next;
	}
	return (NULL);
}

static t_object	*select_last(t_list *scene)
{
	while (scene->next != NULL)
	{
		scene = scene->next;
	}
	return ((t_object *)scene->content);
}

int	add_object(t_list **scene, t_object *object)
{
	if (*scene == NULL)
	{
		*scene = ft_lstnew(object, sizeof(t_object));
		if (*scene == NULL)
			return (-1);
	}
	else
	{
		if (ft_lstappnew(scene, object, sizeof(t_object)) == -1)
			return (-1);
	}
	return (1);
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
	t_3d		origin;
	t_3d		axis;
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
		object = create_plane(origin, 0x009900, utils->cam.dir.back);
	else if (coords_in_area(button[3], x, y))
		object = create_cone(origin, 0x004499, axis, 10.0f);
	else if (coords_in_area(button[4], x, y))
		object = create_cylinder(origin, 0x994400, axis, 10.0f);
	else
		return ;
	if (add_object(&utils->scene, &object) == -1)
		ft_putendl("Failed to add an object to the scene...");
	if (utils->scene != NULL)
		utils->sel_object = select_last(utils->scene);
}
