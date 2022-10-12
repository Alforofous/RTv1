/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:19:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/12 12:44:47 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	intersect_plane(t_ray ray, t_object *plane, float *t)
{
	float	denom;
	t_3f	ray_obj_t;

	denom = dot_product(scale_vector(plane->axis, -1.0f), ray.dir);
	if (denom > 1e-6)
	{
		ray_obj_t = subtract_vectors(plane->origin, ray.origin);
		*t = dot_product(ray_obj_t, scale_vector(plane->axis, -1.0f)) / denom;
		if (*t >= 0)
			return (1);
	}
	return (0);
}
