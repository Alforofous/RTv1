/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:03:56 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:26:45 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3d	sphere_normal(t_object *object, t_3d hit_point)
{
	t_3d	normal;

	normal = normalize_vector(subtract_vectors(hit_point, object->origin));
	return (normal);
}

static t_3d	cone_normal(t_object *object, t_3d hit_point)
{
	t_3d	normal;
	t_3d	vect;
	t_3d	tip;
	double	dp;

	tip = scale_vector(object->axis, object->axis_length);
	tip = add_vectors(object->origin, tip);
	vect = normalize_vector(subtract_vectors(hit_point, tip));
	dp = (double)fabs(acos(dot_product(vect, object->axis)));
	dp = (double)vector_magnitude(subtract_vectors(hit_point, tip)) / cos(dp);
	normal = add_vectors(tip, scale_vector(object->axis, dp));
	normal = normalize_vector(subtract_vectors(hit_point, normal));
	return (normal);
}

static t_3d	cylinder_normal(t_object *object, t_3d hit_point)
{
	t_3d	normal;
	t_3d	top;
	double	dp;

	top = scale_vector(object->axis, object->axis_length);
	top = add_vectors(object->origin, top);
	dp = dot_product(subtract_vectors(hit_point, object->origin), object->axis);
	normal = add_vectors(object->origin, scale_vector(object->axis, dp));
	normal = normalize_vector(subtract_vectors(hit_point, normal));
	return (normal);
}

t_3d	calculate_normal(t_object *object, t_3d hit_point, t_2d t)
{
	t_3d	normal;

	normal = (t_3d){0.0f, 0.0f, 0.0f};
	if (object == NULL)
		return (normal);
	if (object->type == 0 || object->type == 1)
		normal = sphere_normal(object, hit_point);
	else if (object->type == 2)
		normal = object->axis;
	else if (object->type == 3)
		normal = cone_normal(object, hit_point);
	else if (object->type == 4)
		normal = cylinder_normal(object, hit_point);
	if (t.x == t.y)
		normal = scale_vector(normal, -1.0f);
	return (normal);
}
