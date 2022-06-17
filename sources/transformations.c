/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:24:32 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/14 16:12:58 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_3f	get_points(t_utils *utils, float x, float y, float z)
{
	t_3f	point;
	t_3f	point_rot[3];
	t_3f	point_proj;

	point.x = x;
	point.y = y;
	point.z = z;
	init_pmatrix(utils);
	init_rmatrix_x(utils);
	init_rmatrix_y(utils);
	init_rmatrix_z(utils);
	matrix_multip(&point, &point_rot[1], &utils->rmatrix_z);
	matrix_multip(&point_rot[1], &point_rot[2], &utils->rmatrix_y);
	matrix_multip(&point_rot[2], &point_rot[0], &utils->rmatrix_x);
	scale_depth(utils, &point_rot[0].z);
	matrix_multip(&point_rot[0], &point_proj, &utils->pmatrix);
	scale_into_view(utils, &point_proj.x, &point_proj.y);
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

void	scale_into_view(t_utils *utils, float *x, float *y)
{
	*x += 1;
	*y += 1;
	*x *= (float)utils->curr_img->dim.width / 2;
	*y *= (float)utils->curr_img->dim.height / 2;
}

void	scale_depth(t_utils *utils, float *z)
{
	*z -= (float)utils->mouse.zoom;
}
