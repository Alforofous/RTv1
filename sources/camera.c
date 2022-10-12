/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:29:33 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/12 12:45:16 by dmalesev         ###   ########.fr       */
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

void	get_camera_directions(t_utils *utils, t_cam *cam)
{
	cam->dir.forward = direction_rot(utils, &(t_3f){0.0f, 0.0f, -1.0f});
	cam->dir.back = direction_rot(utils, &(t_3f){0.0f, 0.0f, 1.0f});
	cam->dir.right = direction_rot(utils, &(t_3f){1.0f, 0.0f, 0.0f});
	cam->dir.left = direction_rot(utils, &(t_3f){-1.0f, 0.0f, 0.0f});
	cam->dir.up = direction_rot(utils, &(t_3f){0.0f, 1.0f, 0.0f});
	cam->dir.down = direction_rot(utils, &(t_3f){0.0f, -1.0f, 0.0f});
}

t_3f	get_ray(t_2f screen_coords, t_cam *cam, t_proj *proj)
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
