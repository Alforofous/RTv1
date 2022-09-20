/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:36:15 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/20 11:26:51 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	quadratic_equ(const t_3d *quadr, double dprh, t_2d *t)
{
	double	discr;

	discr = quadr->y * quadr->y - 4 * quadr->x * quadr->z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		if (fabs(dprh) != 1.0f)
			t->y = - 0.5f * quadr->y / quadr->x;
	}
	else
	{
		t->x = (-quadr->y - sqrt(discr)) / (2 * quadr->x);
		t->y = (-quadr->y + sqrt(discr)) / (2 * quadr->x);
	}
	if (t->x < 0)
	{
		t->x = t->y;
		if (t->x < 0)
		{
			t->x = 10000;
			t->y = 10000;
			return (0);
		}
	}
	if (t->x < 0)
	{
		t->x = t->y;
		if (t->x < 0)
			return (0);
	}
	return (1);
}

static int	limited_cylinder(t_3f *hit_point, t_3f tip, t_3f *h)
{
	t_3f	hit_point_to_tip;
	double	temp;
	double	h_magn;

	hit_point_to_tip = subtract_vectors(*hit_point, tip);
	temp = dot_product(hit_point_to_tip, normalize_vector(*h));
	h_magn = vector_magnitude(*h);
	if (temp < 0)
		return (-1);
	else if (temp > h_magn)
		return (-2);
	return (1);
}

int	intersect_cylinder(t_3f *ray_origin, t_3f *ray, t_3f *origin, t_3f *tip, float radius, t_2d *t)
{
	t_3d	quadr;
	t_3f	w;
	t_3f	h[2];
	double	dph[2];
	t_3f	hit_point;
	int		ret[2];

	h[0] = subtract_vectors(*origin, *tip);
	h[1] = normalize_vector(h[0]);
	w = subtract_vectors(*ray_origin, *tip);
	dph[0] = dot_product(*ray, h[1]);
	dph[1] = dot_product(w, h[1]);
	quadr.x = dot_product(*ray, *ray) - (dph[0] * dph[0]);
	quadr.y = 2 * (dot_product(*ray, w) - dph[0] * dph[1]);
	quadr.z = dot_product(w, w) - (dph[1] * dph[1]) - radius * radius;
	if (quadratic_equ(&quadr, dph[0], t) == 0)
		return (0);
	hit_point = scale_vector(*ray, (float)t->x);
	hit_point = add_vectors(hit_point, *ray_origin);
	ret[0] = limited_cylinder(&hit_point, *tip, &h[0]);
	if (ret[0] < 0)
		t->x = t->y;
	hit_point = scale_vector(*ray, (float)t->y);
	hit_point = add_vectors(hit_point, *ray_origin);
	ret[1] = limited_cylinder(&hit_point, *tip, &h[0]);
	if (ret[1] == -2 && ret[0] == -1)
		t->y = t->x;
	if (ret[0] < 0 || ret[1] < 0)
	{
		return (0);
	}
	return (1);
}
