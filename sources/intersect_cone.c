/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:41:47 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 12:17:34 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3d	get_quadratic_abc_cone(t_ray ray, t_object *cone)
{
	t_3d	quadratic;
	t_3d	w;
	t_3d	axis;
	double	m;
	double	dph[2];

	axis = scale_vector(cone->axis, cone->axis_length);
	cone->top = add_vectors(cone->origin, axis);
	w = subtract_vectors(ray.origin, cone->top);
	m = (cone->radius * cone->radius);
	m /= (fabs(cone->axis_length) * fabs(cone->axis_length));
	dph[0] = dot_product(ray.dir, cone->axis);
	dph[1] = dot_product(w, cone->axis);
	quadratic.x = dot_product(ray.dir, ray.dir) - m * (dph[0] * dph[0]);
	quadratic.x -= (dph[0] * dph[0]);
	quadratic.y = (dot_product(ray.dir, w) - m * dph[0] * dph[1]);
	quadratic.y -= (dph[0] * dph[1]);
	quadratic.y *= 2;
	quadratic.z = dot_product(w, w) - m * (dph[1] * dph[1]);
	quadratic.z -= (dph[1] * dph[1]);
	return (quadratic);
}

int	intersect_cone(t_ray ray, t_object *cone, t_2d *t)
{
	t_3d	quadratic;
	t_3d	hit_point;
	t_2d	one_int;
	int		ret[2];

	quadratic = get_quadratic_abc_cone(ray, cone);
	one_int.x = dot_product(ray.dir, scale_vector(cone->axis, -1.0f));
	one_int.y = fabs(cone->axis_length);
	one_int.y /= sqrt(one_int.y * one_int.y + cone->radius * cone->radius);
	if (!quadratic_equation(quadratic, one_int, t))
		return (0);
	hit_point = add_vectors(scale_vector(ray.dir, t->x), ray.origin);
	ret[0] = finite_object(hit_point, cone);
	if (ret[0] == -2)
		t->x = t->y;
	hit_point = add_vectors(scale_vector(ray.dir, t->y), ray.origin);
	ret[1] = finite_object(hit_point, cone);
	if (ret[1] == -1)
		t->y = t->x;
	if (ret[0] == -1 && ret[1] == 1)
	{
		t->x = t->y;
		t->y = T_MAX;
	}
	if (ret[0] < 0 && ret[1] < 0)
	{
		*t = (t_2d){T_MAX, T_MAX};
		return (0);
	}
	return (1);
}
