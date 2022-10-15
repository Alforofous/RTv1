/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:50:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:15:49 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	create_light(t_3d origin, t_uint color, double lumen)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = 0;
	object.radius = 0.5f;
	object.origin = origin;
	object.color = color;
	object.lumen = lumen;
	return (object);
}

t_object	create_sphere(t_3d origin, t_uint color, double radius)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = 1;
	object.origin = origin;
	object.color = color;
	object.radius = radius;
	return (object);
}

t_object	create_plane(t_3d origin, t_uint color, t_3d axis)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = 2;
	object.origin = origin;
	object.color = color;
	object.axis = normalize_vector(axis);
	return (object);
}

t_object	create_cone(t_3d origin, t_uint color, t_3d axis, double radius)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = 3;
	object.origin = origin;
	object.color = color;
	object.axis_length = vector_magnitude(axis);
	object.axis = normalize_vector(axis);
	object.radius = radius;
	return (object);
}

t_object	create_cylinder(t_3d origin, t_uint color, t_3d axis, double radius)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = 4;
	object.origin = origin;
	object.color = color;
	object.axis_length = vector_magnitude(axis);
	object.axis = normalize_vector(axis);
	object.radius = radius;
	return (object);
}
