/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:45:26 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:20:00 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3d	get_quadratic_abc_sphere(t_ray ray, t_object *sphere)
{
	t_3d	quadratic;
	t_3d	w;

	w = subtract_vectors(ray.origin, sphere->origin);
	quadratic.x = dot_product(ray.dir, ray.dir);
	quadratic.y = 2 * dot_product(ray.dir, w);
	quadratic.z = dot_product(w, w) - sphere->radius * sphere->radius;
	return (quadratic);
}

int	intersect_sphere(t_ray ray, t_object *sphere, t_2d *t)
{
	t_3d	quadratic;

	quadratic = get_quadratic_abc_sphere(ray, sphere);
	if (quadratic_equation(quadratic, (t_2d){1.0f, 2.0f}, t) == 0)
		return (0);
	if (t->x < 1e-6)
	{
		t->x = t->y;
		if (t->x < 1e-6)
			return (0);
	}
	return (1);
}
