/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:36:15 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/09 12:28:48 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	quadratic_equ(const t_3d *quadr, double dprh, t_2d *t)
{
	double	discr;
	double	q;

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
		if (quadr->y > 0)
			q = -0.5f * (quadr->y + sqrt(discr));
		else
			q = -0.5f * (quadr->y - sqrt(discr));
		t->y = q / quadr->x;
		t->x = quadr->z / q;
	}
	if (t->x < 0)
	{
		t->x = t->y;
		if (t->x < 0)
			return (0);
	}
	return (1);
}

int	intersect_cylinder(t_3f *ray_origin, t_3f *ray, t_3f *origin, t_3f *tip, float radius, t_2d *t)
{
	t_3d	quadr;
	t_3f	w;
	t_3f	h[2];
	double	dph[2];

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
	return (1);
}
