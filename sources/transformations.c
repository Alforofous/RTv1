/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:24:32 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 12:58:35 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	scale_into_view(t_img *img, float *x, float *y)
{
	*x += 1;
	*y += 1;
	*x *= (float)img->dim.size.x / 2;
	*y *= (float)img->dim.size.y / 2;
}

t_proj	init_proj(float fov, t_2i *dim, t_2f *z_depth)
{
	t_proj	proj;

	proj.z_near = z_depth->x;
	proj.z_far = z_depth->y;
	proj.fov = fov;
	proj.asp_ratio = (float)dim->x / (float)dim->y;
	proj.fov_rad = (float)(1 / tan(fov / 2 / 180 * PI));
	return (proj);
}

t_3f	rotate_point(t_3f point, t_3f rot)
{
	t_3f	point_rot[3];
	t_mat	rmatrix[3];

	rmatrix[0] = init_rmatrix_x(rot.x);
	rmatrix[1] = init_rmatrix_y(rot.y);
	rmatrix[2] = init_rmatrix_z(rot.z);
	matrix_multip(&point, &point_rot[1], &rmatrix[0]);
	matrix_multip(&point_rot[1], &point_rot[2], &rmatrix[1]);
	matrix_multip(&point_rot[2], &point_rot[0], &rmatrix[2]);
	return (point_rot[0]);
}

t_3f	get_points(t_img *img, t_3f *xyz, t_3f *rot, t_proj *proj)
{
	t_3f	point_rot;
	t_3f	point_proj;
	t_mat	pmatrix;

	pmatrix = init_pmatrix(proj);
	point_rot = rotate_point(*xyz, *rot);
	point_rot.z -= 20.0f;
	matrix_multip(&point_rot, &point_proj, &pmatrix);
	scale_into_view(img, &point_proj.x, &point_proj.y);
	return (point_proj);
}

void	matrix_multip(t_3f *in, t_3f *out, t_mat *matrix)
{
	float	temp;

	(*out).x = (*in).x * ((*matrix).m[0][0]) + (*in).y * ((*matrix).m[1][0])
		+ (*in).z * ((*matrix).m[2][0]) + ((*matrix).m[3][0]);
	(*out).y = (*in).x * ((*matrix).m[0][1]) + (*in).y * ((*matrix).m[1][1])
		+ (*in).z * ((*matrix).m[2][1]) + ((*matrix).m[3][1]);
	(*out).z = (*in).x * ((*matrix).m[0][2]) + (*in).y * ((*matrix).m[1][2])
		+ (*in).z * ((*matrix).m[2][2]) + ((*matrix).m[3][2]);
	temp = (*in).x * ((*matrix).m[0][3]) + (*in).y * ((*matrix).m[1][3])
		+ (*in).z * ((*matrix).m[2][3]) + ((*matrix).m[3][3]);
	if (temp != 0)
	{
		(*out).x /= temp;
		(*out).y /= temp;
		(*out).z /= temp;
	}
}
