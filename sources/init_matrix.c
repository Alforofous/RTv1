/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/01 11:09:43 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_pmatrix(t_utils *u)
{
	float	z_d;

	z_d = u->proj.z_far - u->proj.z_near;
	(u->pmatrix.m)[0][0] = (float)(u->proj.asp_ratio) * (u->proj.fov_rad);
	(u->pmatrix.m)[1][1] = (float)(u->proj.fov_rad);
	(u->pmatrix.m)[2][2] = (float)(u->proj.z_far) / (z_d);
	(u->pmatrix.m)[3][2] = (float)(-(u->proj.z_far) * (u->proj.z_near)) / z_d;
	(u->pmatrix.m)[2][3] = 1;
	(u->pmatrix.m)[3][3] = 0;
}

void	init_rmatrix_x(t_utils *utils)
{
	utils->rmatrix_x.m[0][0] = 1;
	utils->rmatrix_x.m[1][1] = (float)cos(utils->rot.x / 180 * PI);
	utils->rmatrix_x.m[1][2] = (float)sin(utils->rot.x / 180 * PI);
	utils->rmatrix_x.m[2][1] = (float)-sin(utils->rot.x / 180 * PI);
	utils->rmatrix_x.m[2][2] = (float)cos(utils->rot.x / 180 * PI);
	utils->rmatrix_x.m[3][3] = 1;
}

void	init_rmatrix_y(t_utils *utils)
{
	utils->rmatrix_y.m[0][0] = (float)cos(utils->rot.y / 180 * PI);
	utils->rmatrix_y.m[0][2] = (float)-sin(utils->rot.y / 180 * PI);
	utils->rmatrix_y.m[1][1] = 1;
	utils->rmatrix_y.m[2][0] = (float)sin(utils->rot.y / 180 * PI);
	utils->rmatrix_y.m[2][2] = (float)cos(utils->rot.y / 180 * PI);
	utils->rmatrix_y.m[3][3] = 1;
}

void	init_rmatrix_z(t_utils *utils)
{
	utils->rmatrix_z.m[0][0] = (float)cos(utils->rot.z / 180 * PI);
	utils->rmatrix_z.m[0][1] = (float)sin(utils->rot.z / 180 * PI);
	utils->rmatrix_z.m[1][0] = (float)-sin(utils->rot.z / 180 * PI);
	utils->rmatrix_z.m[1][1] = (float)cos(utils->rot.z / 180 * PI);
	utils->rmatrix_z.m[2][2] = 1;
	utils->rmatrix_z.m[3][3] = 1;
}

void	init_matrix(t_mat *matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			((*matrix).m)[i][j] = 0;
			j++;
		}
		i++;
	}
}
