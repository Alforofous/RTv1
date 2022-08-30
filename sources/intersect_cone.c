/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:41:47 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/29 12:02:23 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	quadratic_equ(const t_3f *quadr, float *t0, float *t1)
{
	float	discr;
	float	q;
	float	temp;

	discr = quadr->y * quadr->y - 4 * quadr->x * quadr->z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		*t0 = - 0.5f * quadr->y / quadr->x;
		*t1 = - 0.5f * quadr->y / quadr->x;
	}
	else
	{
		if (quadr->y > 0)
			q = -0.5f * (quadr->y + (float)sqrt(discr));
		else
			q = -0.5f * (quadr->y - (float)sqrt(discr));
		*t0 = q / quadr->x;
		*t1 = quadr->z / q;
	}
	if (*t0 > *t1)
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return (1);
}

int	intersect_cone(t_ray *ray, t_3f *origin, t_3f *tip, float radius, t_2f *t)
{
	t_3f	quadr;
	t_3f	w;
	t_3f	h[2];
	float	h0_magn;
	float	m;
	float	dph[2];

	h[0] = subtract_vectors(origin, tip);
	h0_magn = vector_magnitude(h[0]);
	h[1] = divide_vector(h0_magn, &h[0]);
	w = subtract_vectors(&ray->origin, tip);
	m = (radius * radius) / (h0_magn * h0_magn);
	dph[0] = dot_product(&ray->dir.forward, &h[1]);
	dph[1] = dot_product(&w, &h[1]);
	quadr.x = dot_product(&ray->dir.forward, &ray->dir.forward) - m * (dph[0] * dph[0]) - (dph[0] * dph[0]);
	quadr.y = 2 * (dot_product(&ray->dir.forward, &w) - m * dph[0] * dph[1] - dph[0] * dph[1]);
	quadr.z = dot_product(&w, &w) - m * (dph[1] * dph[1]) - (dph[1] * dph[1]);
	if (quadratic_equ(&quadr, &t->x, &t->y) == 0)
		return (0);
	if (t->x < 0)
	{
		t->x = t->y;
		if (t->x < 0)
			return (0);
	}
	return (1);
}
