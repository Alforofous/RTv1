/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:29:33 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 16:12:58 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	quadratic_equ(const t_3f *abc, float *x0, float *x1)
{
	float	discr;
	float	q;
	float	temp;

	discr = abc->y * abc->y - 4 * abc->x * abc->z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
		*x0 = *x1 = - 0.5f * abc->y / abc->x;
	else
	{
		if (abc->y > 0)
			q = -0.5f * (abc->y + (float)sqrt(discr));
		else
			q = -0.5f * (abc->y - (float)sqrt(discr));
		*x0 = q / abc->x;
		*x1 = abc->z / q;
	}
	if (*x0 > *x1)
	{
		temp = *x0;
		*x0 = *x1;
		*x1 = temp;
	}
	return (1);
}

int	intersect_sphere(t_3f *ray, t_3f *orig, t_3f *center, float radius)
{
	t_3f	l;
	t_3f	abc;
	float	temp;
	float	t[2];

	l = subtract_vectors(orig, center);
	abc.x = dot_product(ray, ray);
	abc.y = 2 * dot_product(ray, &l);
	abc.z = dot_product(&l, &l) - radius;
	if (quadratic_equ(&abc, &t[0], &t[1]) == 0)
		return (0);
	if (t[0] > t[1])
	{
		temp = t[0];
		t[0] = t[1];
		t[1] = temp;
	}
	if (t[0] < 0)
	{
		t[0] = t[1];
		if (t[0] < 0)
			return (0);
	}
	return (1);
}

t_3f	get_ray(t_utils *utils, t_2f screen_coords, t_cam *cam)
{
	t_3f	ray;
	t_3f	forward;
	t_3f	right;
	t_3f	up;
	float	h_w[2];

	h_w[0] = (float)tan(utils->proj.fov * PI / 180);
	h_w[1] = h_w[0] * utils->proj.asp_ratio;
	forward = normalize_vector(subtract_vectors(&cam->dir.forward, &cam->origin));
	right = scale_vector(h_w[1] * screen_coords.x, &cam->dir.right);
	up = scale_vector(h_w[0] * screen_coords.y, &cam->dir.up);
	ray = add_vectors(&forward, &right);
	ray = add_vectors(&ray, &up);
	ray = normalize_vector(ray);
	return (ray);
}
