/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:03:56 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/13 12:30:54 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3f	sphere_normal(t_object *object, t_3f hit_point)
{
	t_3f	normal;

	normal = normalize_vector(subtract_vectors(hit_point, object->origin));
	return (normal);
}

static t_3f	cone_normal(t_object *object, t_3f hit_point)
{
	t_3f	normal;
	t_3f	vect;
	t_3f	tip;
	float	dp;

	tip = scale_vector(object->axis, object->axis_length);
	tip = add_vectors(object->origin, tip);
	vect = normalize_vector(subtract_vectors(hit_point, tip));
	dp = (float)fabs(acos(dot_product(vect, object->axis)));
	dp = (float)vector_magnitude(subtract_vectors(hit_point, tip)) / cosf(dp);
	normal = add_vectors(tip, scale_vector(object->axis, dp));
	normal = normalize_vector(subtract_vectors(hit_point, normal));
	normal = normalize_vector(subtract_vectors(hit_point, object->origin));
	return (normal);
}

static t_3f	cylinder_normal(t_object *object, t_3f hit_point)
{
	t_3f	normal;
	t_3f	top;
	float	dp;

	top = scale_vector(object->axis, object->axis_length);
	top = add_vectors(object->origin, top);
	dp = dot_product(subtract_vectors(hit_point, object->origin), object->axis);
	normal = add_vectors(object->origin, scale_vector(object->axis, dp));
	normal = normalize_vector(subtract_vectors(hit_point, normal));
	return (normal);
}

t_3f	calculate_normal(t_object *object, t_3f hit_point, t_2f t)
{
	t_3f	normal;

	normal = (t_3f){0.0f, 0.0f, 0.0f};
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
