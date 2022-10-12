/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:41:47 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/12 11:26:31 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3f	get_quadratic_abc_cone(t_ray ray, t_object *cone)
{
	t_3f	quadratic;
	t_3f	w;
	t_3f	axis;
	float	m;
	float	dph[2];

	axis = scale_vector(cone->axis, cone->axis_length);
	cone->top = add_vectors(cone->origin, axis);
	w = subtract_vectors(ray.origin, cone->top);
	m = (cone->radius * cone->radius);
	m /= (fabsf(cone->axis_length) * fabsf(cone->axis_length));
	dph[0] = dot_product(ray.dir, scale_vector(cone->axis, -1.0f));
	dph[1] = dot_product(w, scale_vector(cone->axis, -1.0f));
	quadratic.x = dot_product(ray.dir, ray.dir) - m * (dph[0] * dph[0]);
	quadratic.x -= (dph[0] * dph[0]);
	quadratic.y = (dot_product(ray.dir, w) - m * dph[0] * dph[1]);
	quadratic.y -= (dph[0] * dph[1]);
	quadratic.y *= 2;
	quadratic.z = dot_product(w, w) - m * (dph[1] * dph[1]);
	quadratic.z -= (dph[1] * dph[1]);
	return (quadratic);
}

int	intersect_cone(t_ray ray, t_object *cone, t_2f *t)
{
	t_3f	quadratic;
	t_3f	hit_point;
	t_2f	one_int;
	int		ret[2];

	quadratic = get_quadratic_abc_cone(ray, cone);
	one_int.x = dot_product(ray.dir, scale_vector(cone->axis, -1.0f));
	one_int.y = fabsf(cone->axis_length);
	one_int.y /= sqrtf(one_int.y * one_int.y + cone->radius * cone->radius);
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
	if (ret[0] < 0 && ret[1] < 0)
	{
		*t = (t_2f){T_MAX, T_MAX};
		return (0);
	}
	return (1);
}
