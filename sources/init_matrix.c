/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/11 14:11:53 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mat	init_pmatrix(t_proj *proj)
{
	t_mat	matrix;

	matrix.m[0][0] = proj->asp_ratio * proj->fov_rad;
	matrix.m[1][1] = proj->fov_rad;
	matrix.m[2][2] = proj->z_far / (proj->z_far - proj->z_near);
	matrix.m[3][2] = proj->z_far * proj->z_near / (proj->z_far - proj->z_near);
	matrix.m[2][3] = 1;
	matrix.m[3][3] = 0;
	return (matrix);
}

t_mat	init_rmatrix_x(float angle_x)
{
	t_mat	matrix;

	matrix.m[0][0] = 1;
	matrix.m[1][1] = (float)cos(angle_x / 180.0f * PI);
	matrix.m[1][2] = (float)sin(angle_x / 180.0f * PI);
	matrix.m[2][1] = (float)-sin(angle_x / 180.0f * PI);
	matrix.m[2][2] = (float)cos(angle_x / 180.0f * PI);
	matrix.m[3][3] = 1;
	return (matrix);
}

t_mat	init_rmatrix_y(float angle_y)
{
	t_mat	matrix;

	matrix.m[0][0] = (float)cos(angle_y / 180.0f * PI);
	matrix.m[0][2] = (float)-sin(angle_y / 180.0f * PI);
	matrix.m[1][1] = 1;
	matrix.m[2][0] = (float)sin(angle_y / 180.0f * PI);
	matrix.m[2][2] = (float)cos(angle_y / 180.0f * PI);
	matrix.m[3][3] = 1;
	return (matrix);
}

t_mat	init_rmatrix_z(float angle_z)
{
	t_mat	matrix;

	matrix.m[0][0] = (float)cos(angle_z / 180.0f * PI);
	matrix.m[0][1] = (float)sin(angle_z / 180.0f * PI);
	matrix.m[1][0] = (float)-sin(angle_z / 180.0f * PI);
	matrix.m[1][1] = (float)cos(angle_z / 180.0f * PI);
	matrix.m[2][2] = 1;
	matrix.m[3][3] = 1;
	return (matrix);
}
