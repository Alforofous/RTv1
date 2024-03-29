/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:29:33 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/16 13:09:11 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3d	direction_rot(t_utils *utils, t_3d *direction)
{
	t_3d	point_rot[3];

	matrix_multip(direction, &point_rot[0], &utils->rmatrix_x);
	matrix_multip(&point_rot[0], &point_rot[1], &utils->rmatrix_y);
	matrix_multip(&point_rot[1], &point_rot[2], &utils->rmatrix_z);
	return (point_rot[2]);
}

void	get_camera_directions(t_utils *utils, t_cam *cam)
{
	utils->rmatrix_x = init_rmatrix_x(utils->cam.rot.x);
	utils->rmatrix_y = init_rmatrix_y(utils->cam.rot.y);
	utils->rmatrix_z = init_rmatrix_z(utils->cam.rot.z);
	cam->dir.forward = direction_rot(utils, &(t_3d){0.0f, 0.0f, -1.0f});
	cam->dir.back = direction_rot(utils, &(t_3d){0.0f, 0.0f, 1.0f});
	cam->dir.right = direction_rot(utils, &(t_3d){1.0f, 0.0f, 0.0f});
	cam->dir.left = direction_rot(utils, &(t_3d){-1.0f, 0.0f, 0.0f});
	cam->dir.up = direction_rot(utils, &(t_3d){0.0f, 1.0f, 0.0f});
	cam->dir.down = direction_rot(utils, &(t_3d){0.0f, -1.0f, 0.0f});
}

t_ray	get_ray(t_2i coords, t_img *img, t_cam *cam, t_proj *proj)
{
	t_ray	ray;
	t_dir	dir;
	t_2d	norm_screen;
	double	h_w[2];

	norm_screen.x = (double)(2 * coords.x) / (double)img->dim.size.x - 1.0;
	norm_screen.y = (double)(2 * coords.y) / (double)img->dim.size.y - 1.0;
	h_w[0] = (double)tan(proj->fov * PI / 360);
	h_w[1] = h_w[0] * proj->asp_ratio;
	dir.forward = cam->dir.forward;
	dir.right = normalize_vector(cross_product(dir.forward, cam->dir.up));
	dir.up = normalize_vector(cross_product(dir.forward, dir.right));
	dir.right = scale_vector(dir.right, h_w[1] * norm_screen.x);
	dir.up = scale_vector(dir.up, h_w[0] * norm_screen.y);
	ray.dir = add_vectors(dir.forward, dir.right);
	ray.dir = add_vectors(ray.dir, dir.up);
	ray.dir = normalize_vector(ray.dir);
	ray.origin = cam->origin;
	return (ray);
}
