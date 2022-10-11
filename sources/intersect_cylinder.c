/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:36:15 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/11 12:00:55 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3f	get_quadratic_abc_cylinder(t_ray ray, t_object *cylinder)
{
	t_3f	quadratic;
	t_3f	w;
	t_3f	axis;
	float	dph[2];

	axis = scale_vector(cylinder->axis, cylinder->axis_length);
	cylinder->top = add_vectors(cylinder->origin, axis);
	w = subtract_vectors(ray.origin, cylinder->top);
	dph[0] = dot_product(ray.dir, cylinder->axis);
	dph[1] = dot_product(w, cylinder->axis);
	quadratic.x = dot_product(ray.dir, ray.dir) - (dph[0] * dph[0]);
	quadratic.y = 2 * (dot_product(ray.dir, w) - dph[0] * dph[1]);
	quadratic.z = dot_product(w, w) - (dph[1] * dph[1]);
	quadratic.z -= cylinder->radius * cylinder->radius;
	return (quadratic);
}

int	intersect_cylinder(t_ray ray, t_object *cylinder, t_2f *t)
{
	t_3f	quadratic;
	t_3f	hit_point;
	float	dp_ray_hnorm;
	int		ret[2];

	quadratic = get_quadratic_abc_cylinder(ray, cylinder);
	dp_ray_hnorm = dot_product(ray.dir, cylinder->axis);
	if (quadratic_equation(quadratic, (t_2f){fabsf(dp_ray_hnorm), 1}, t) == 0)
		return (0);
	hit_point = scale_vector(ray.dir, t->x);
	hit_point = add_vectors(hit_point, ray.origin);
	ret[0] = finite_object(hit_point, cylinder);
	if (ret[0] < 0)
		t->x = t->y;
	hit_point = scale_vector(ray.dir, t->y);
	hit_point = add_vectors(hit_point, ray.origin);
	ret[1] = finite_object(hit_point, cylinder);
	if (ret[1] == -2 && ret[0] == -1)
		t->y = t->x;
	if (ret[0] < 0 && ret[1] < 0)
	{
		*t = (t_2f){T_MAX, T_MAX};
		return (0);
	}
	return (1);
}
