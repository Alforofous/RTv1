/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:29:33 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/08 13:09:21 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	quadratic_equ(const t_3f *quadr, float *x0, float *x1)
{
	float	discr;
	float	q;
	float	temp;

	discr = quadr->y * quadr->y - 4 * quadr->x * quadr->z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
		*x0 = *x1 = - 0.5f * quadr->y / quadr->x;
	else
	{
		if (quadr->y > 0)
			q = -0.5f * (quadr->y + (float)sqrt(discr));
		else
			q = -0.5f * (quadr->y - (float)sqrt(discr));
		*x0 = q / quadr->x;
		*x1 = quadr->z / q;
	}
	if (*x0 > *x1)
	{
		temp = *x0;
		*x0 = *x1;
		*x1 = temp;
	}
	return (1);
}

int	intersect_plane(t_3f *ray, t_3f *origin, t_3f *ray_origin, t_3f *normal, float *t)
{
	float	denom;
	t_3f	intersect;
	
	denom = dot_product(normal, ray);
	if (denom > 1e-6)
	{
		intersect = subtract_vectors(origin, ray_origin);
		*t = dot_product(&intersect, normal) / denom;
		return (*t >= 0);
	}
	return (0);
}

int	intersect_sphere(t_3f *ray, t_3f *origin, float radius, t_2f *t)
{
	t_3f	l;
	t_3f	quadr;

	l = *origin;
	l.x *= -1;
	l.y *= -1;
	l.z *= -1;
	quadr.x = dot_product(ray, ray);
	quadr.y = 2 * dot_product(ray, &l);
	quadr.z = dot_product(&l, &l) - radius;
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

t_3f	get_ray(t_2f screen_coords, t_ray *cam, t_proj *proj)
{
	t_3f	ray;
	t_3f	forward;
	t_3f	right;
	t_3f	up;
	float	h_w[2];

	h_w[0] = (float)tan(proj->fov * PI / 360);
	h_w[1] = h_w[0] * proj->asp_ratio;
	forward = cam->dir.forward;
	right = normalize_vector(cross_product(&forward, &cam->dir.up));
	up = normalize_vector(cross_product(&forward, &right));
	right = scale_vector(h_w[1] * screen_coords.x, &right);
	up = scale_vector(h_w[0] * screen_coords.y, &up);
	ray = add_vectors(&forward, &right);
	ray = add_vectors(&ray, &up);
	ray = normalize_vector(ray);
	return (ray);
}
