/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:29:33 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/21 15:14:20 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3f	direction_rot(t_utils *utils, t_3f *direction)
{
	t_3f	point_rot[3];

	matrix_multip(direction, &point_rot[0], &utils->rmatrix_x);
	matrix_multip(&point_rot[0], &point_rot[1], &utils->rmatrix_y);
	matrix_multip(&point_rot[1], &point_rot[2], &utils->rmatrix_z);
	return (point_rot[2]);
}

void	get_camera_directions(t_utils *utils, t_ray *cam)
{
	cam->dir.forward = direction_rot(utils, &(t_3f){0.0f, 0.0f, -1.0f});
	cam->dir.back = direction_rot(utils, &(t_3f){0.0f, 0.0f, 1.0f});
	cam->dir.right = direction_rot(utils, &(t_3f){1.0f, 0.0f, 0.0f});
	cam->dir.left = direction_rot(utils, &(t_3f){-1.0f, 0.0f, 0.0f});
	cam->dir.up = direction_rot(utils, &(t_3f){0.0f, 1.0f, 0.0f});
	cam->dir.down = direction_rot(utils, &(t_3f){0.0f, -1.0f, 0.0f});
}

static int	quadratic_equ(const t_3f *quadr, double *t0, double *t1)
{
	double	discr;
	double	temp;

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
		*t0 = (-quadr->y - sqrt(discr)) / (2 * quadr->x);
		*t1 = (-quadr->y + sqrt(discr)) / (2 * quadr->x);
	}
	if (*t0 > *t1)
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return (1);
}

int	intersect_plane(t_3f *ray, t_3f *origin, t_3f *ray_origin, t_3f *normal, double *t)
{
	float	denom;
	t_3f	intersect;
	
	denom = dot_product(*normal, *ray);
	if (denom > 1e-6)
	{
		intersect = subtract_vectors(*origin, *ray_origin);
		*t = dot_product(intersect, *normal) / denom;
		return (*t >= 0);
	}
	return (0);
}

int	intersect_sphere(t_3f *ray, t_3f *ray_origin, t_3f *origin, float radius, t_2d *t)
{
	t_3f	w;
	t_3f	quadr;

	w = subtract_vectors(*ray_origin, *origin);
	quadr.x = dot_product(*ray, *ray);
	quadr.y = 2 * dot_product(*ray, w);
	quadr.z = dot_product(w, w) - radius * radius;
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
	right = normalize_vector(cross_product(forward, cam->dir.up));
	up = normalize_vector(cross_product(forward, right));
	right = scale_vector(right, h_w[1] * screen_coords.x);
	up = scale_vector(up, h_w[0] * screen_coords.y);
	ray = add_vectors(forward, right);
	ray = add_vectors(ray, up);
	ray = normalize_vector(ray);
	return (ray);
}
