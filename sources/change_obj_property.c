/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_obj_property.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:38:21 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 15:40:44 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	change_obj_property(t_object *sel_object, float nbr)
{
	t_read_obj	obj;
	float		*property;

	if (sel_object->type == 0)
	{
		obj.light = (t_light *)sel_object->content;
		property = &obj.light->lumen;
	}
	else if (sel_object->type == 1)
	{
		obj.sphere = (t_sphere *)sel_object->content;
		property = &obj.sphere->radius;
	}
	else if (sel_object->type == 3)
	{
		obj.cone = (t_cone *)sel_object->content;
		property = &obj.cone->radius;
	}
	else if (sel_object->type == 4)
	{
		obj.cylinder = (t_cylinder *)sel_object->content;
		property = &obj.cylinder->radius;
	}
	else
		return ;
	*property += nbr;
}
