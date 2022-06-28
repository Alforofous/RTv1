/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/28 12:26:47 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	draw_ray_arrows(t_utils *utils, t_3f *ray, t_u_int color)
{
	t_3f	point;
	t_3f	point2;
	t_proj	proj;

	proj = init_proj(60, &(t_2i){utils->img.dim.width, utils->img.dim.height}, &(t_2f){0.1f, 1000.0f});
	ray->x *= 10;
	ray->y *= 10;
	ray->z *= 10;
	point = get_points(utils, ray, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	point2 = get_points(utils, &(t_3f){0, 0, 0}, &utils->rot, &utils->proj);
	draw_circle(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_2i){(int)point.x, (int)point.y}, 3, color);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_line){(int)point2.x, (int)point2.y,
		(int)point.x, (int)point.y}, color, 0xFFFFFF);
	draw_circle(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_2i){(int)point2.x, (int)point2.y}, 3, 0xFFFFFF);
}

static t_3f	get_camera_rotation(t_utils *utils, t_3f *direction)
{
	t_3f	point_rot[3];

	matrix_multip(direction, &point_rot[0], &utils->rmatrix_x); 
	matrix_multip(&point_rot[0], &point_rot[1], &utils->rmatrix_y); 
	matrix_multip(&point_rot[1], &point_rot[2], &utils->rmatrix_z); 
	return (point_rot[2]);
}

static void	get_camera_directions(t_utils *utils, t_cam *cam)
{
	cam->dir.forward = get_camera_rotation(utils, &(t_3f){0.0f, 0.0f, -1.0f});
	cam->dir.back = get_camera_rotation(utils, &(t_3f){0.0f, 0.0f, 1.0f});
	cam->dir.right = get_camera_rotation(utils, &(t_3f){1.0f, 0.0f, 0.0f});
	cam->dir.left = get_camera_rotation(utils, &(t_3f){-1.0f, 0.0f, 0.0f});
	cam->dir.up = get_camera_rotation(utils, &(t_3f){0.0f, 1.0f, 0.0f});
	cam->dir.down = get_camera_rotation(utils, &(t_3f){0.0f, -1.0f, 0.0f});
}

void	ray_plotting(t_utils *utils, t_img *img)
{
	int		xy[2];
	t_2f	scrn;
	t_3f	center;
	t_3f	ray;

	xy[0] = 0;
	get_camera_directions(utils, &utils->cam);
	while (xy[0] <= img->dim.width)
	{
		xy[1] = 0;
		while (xy[1] <= img->dim.height)
		{
			scrn.x = (float)(2 * xy[0]) / (float)img->dim.width - 1.0f;
			scrn.y = (float)(-2 * xy[1]) / (float)img->dim.height + 1.0f;
			ray = get_ray(utils, scrn, &utils->cam);
			if (utils->visual_rays == 1)
			{
				if (xy[0] % 50 == 0 && xy[1] % 50 == 0)
					draw_ray_arrows(utils, &ray, 0x004466);
				if (xy[0] + img->dim.x0 == utils->mouse.x
					&& xy[1] + img->dim.y0 == utils->mouse.y)
					draw_ray_arrows(utils, &ray, 0xFF0000);
			}
			center = subtract_vectors(&(t_3f){0.0f, 0, -10.0f}, &utils->cam.origin);
			if (intersect_sphere(&ray, &center, 1.0f))
				ft_pixel_put(xy[0], xy[1], 0x00FFFF, img);
			xy[1]++;
		}
		xy[0]++;
	}
}

void	draw_image1(t_utils *utils)
{
	ray_plotting(utils, &utils->img);
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}

void	draw_image2(t_utils *utils)
{
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}

static void	cam_direction_map(t_utils *utils)
{
	int		sc_mid[2];
	t_3f	point;

	sc_mid[0] = utils->curr_img->dim.width / 2;
	sc_mid[1] = utils->curr_img->dim.height / 2;
	point = get_points(utils, &(t_3f){utils->cam.dir.forward.x * 5,
		utils->cam.dir.forward.y * 5, utils->cam.dir.forward.z * 5}, &utils->rot, &utils->proj);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_line){(int)sc_mid[0], (int)sc_mid[1],
		(int)point.x, (int)point.y}, 0xFF0000, 0xFF0000);
	point = get_points(utils, &(t_3f){utils->cam.dir.right.x * 5,
		utils->cam.dir.right.y * 5, utils->cam.dir.right.z * 5}, &utils->rot, &utils->proj);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_line){(int)sc_mid[0], (int)sc_mid[1],
		(int)point.x, (int)point.y}, 0x00FF00, 0x00FF00);
	point = get_points(utils, &(t_3f){utils->cam.dir.up.x * 5,
		utils->cam.dir.up.y * 5, utils->cam.dir.up.z * 5}, &utils->rot, &utils->proj);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_line){(int)sc_mid[0], (int)sc_mid[1],
		(int)point.x, (int)point.y}, 0x0000FF, 0x0000FF);
}

void	draw_image3(t_utils *utils)
{
	cam_direction_map(utils);
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}

static void	image_processing(t_utils *utils, t_img *img, t_u_int fill_color)
{
	utils->curr_img = img;
	fill_img(utils, fill_color);
	img->draw_func(utils);
	mlx_put_image_to_window(utils->mlx, utils->win, img->ptr, img->dim.x0,
		img->dim.y0);
}

void	render_screen(t_utils *utils)
{
	clock_t	interv[2];
	int		xy[2];
	char	*str;

	xy[0] = utils->img.dim.width / 80;
	xy[1] = utils->img.dim.height / 50;
	interv[0] = clock();
	image_processing(utils, &utils->img, 0x000000);
	interv[1] = clock();
	str = ft_ftoa((float)(interv[1] - interv[0]) / CLOCKS_PER_SEC, 5);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for render time...", -1);
	mlx_string_put(utils->mlx, utils->win, utils->img.dim.x0 + xy[0],
		utils->img.dim.y0 + xy[1], 0x000000, str);
	mlx_string_put(utils->mlx, utils->win, utils->img.dim.x0 + xy[0],
		utils->img.dim.y0 + xy[1] + 1, 0xFFFFFF, str);
	free(str);
	image_processing(utils, &utils->img2, 0x000000);
	str = ft_ftoa(utils->proj.fov, 3);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for FOV...", -1);
	mlx_string_put(utils->mlx, utils->win, 10, 10, 0xFFFFFF, str);
	if (utils->reference == 1)
		image_processing(utils, &utils->img3, 0x8899BBFF);
	free(str);
}
