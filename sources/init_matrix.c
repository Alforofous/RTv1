/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:13:56 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mat	init_pmatrix(t_proj *proj)
{
	t_mat	matrix;

	ft_bzero(&matrix, sizeof(t_mat));
	matrix.m[0][0] = proj->asp_ratio * proj->fov_rad;
	matrix.m[1][1] = proj->fov_rad;
	matrix.m[2][2] = proj->z_far / (proj->z_far - proj->z_near);
	matrix.m[3][2] = proj->z_far * proj->z_near / (proj->z_far - proj->z_near);
	matrix.m[2][3] = 1;
	matrix.m[3][3] = 0;
	return (matrix);
}

t_mat	init_rmatrix_x(double angle_x)
{
	t_mat	matrix;

	ft_bzero(&matrix, sizeof(t_mat));
	matrix.m[0][0] = 1;
	matrix.m[1][1] = cos(angle_x / 180.0f * PI);
	matrix.m[1][2] = sin(angle_x / 180.0f * PI);
	matrix.m[2][1] = -sin(angle_x / 180.0f * PI);
	matrix.m[2][2] = cos(angle_x / 180.0f * PI);
	matrix.m[3][3] = 1;
	return (matrix);
}

t_mat	init_rmatrix_y(double angle_y)
{
	t_mat	matrix;

	ft_bzero(&matrix, sizeof(t_mat));
	matrix.m[0][0] = cos(angle_y / 180.0f * PI);
	matrix.m[0][2] = -sin(angle_y / 180.0f * PI);
	matrix.m[1][1] = 1;
	matrix.m[2][0] = sin(angle_y / 180.0f * PI);
	matrix.m[2][2] = cos(angle_y / 180.0f * PI);
	matrix.m[3][3] = 1;
	return (matrix);
}

t_mat	init_rmatrix_z(double angle_z)
{
	t_mat	matrix;

	ft_bzero(&matrix, sizeof(t_mat));
	matrix.m[0][0] = cos(angle_z / 180.0f * PI);
	matrix.m[0][1] = sin(angle_z / 180.0f * PI);
	matrix.m[1][0] = -sin(angle_z / 180.0f * PI);
	matrix.m[1][1] = cos(angle_z / 180.0f * PI);
	matrix.m[2][2] = 1;
	matrix.m[3][3] = 1;
	return (matrix);
}
