/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/27 13:51:12 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	checkerboard_carpet(t_utils *utils)
{
	int		x;
	int		y;
	t_3f	point;

	x = -50;
	while (x <= 50)
	{
		y = -50;
		while (y <= 50)
		{
			point = get_points(utils, (float)x, 0, (float)y);
			if (point.z > 1)
				ft_pixel_put((int)point.x, (int)point.y, 0xFFFFFF,
					utils->curr_img);
			y++;
		}
		x++;
	}
}

static void	draw_ray_arrows(t_utils *utils, t_3f *ray, t_u_int color)
{
	t_3f	point;
	t_3f	point2;

	ray->x *= 10;
	ray->y *= 10;
	ray->z *= 10;
	point = get_points(utils, ray->x, ray->z, ray->y);
	point2 = get_points(utils, 0, 0, 0);
	draw_circle(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_2i){(int)point.x, (int)point.y}, 3, color);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_line){(int)point2.x, (int)point2.y,
		(int)point.x, (int)point.y}, color, 0xFFFFFF);
	draw_circle(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_2i){(int)point2.x, (int)point2.y}, 3, 0xFFFFFF);
}

t_3f	get_camera_position(t_3f *target, t_3f *origin)
{
	t_3f	camera;

	camera = normalize_vector(subtract_vectors(target, origin));
	return (camera);
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

void	ray_plotting(t_utils *utils)
{
	int		x;
	int		y;
	t_2f	screen_coords;
	t_3f	ray;

	x = 0;
	get_camera_directions(utils, &utils->cam);
	printf("FORWARD: %f %f %f\n", utils->cam.dir.forward.x, utils->cam.dir.forward.y, utils->cam.dir.forward.z);
	//utils->cam.origin = get_camera_position(&utils->cam.dir.forward, &utils->cam.origin);
	printf("CAM_ORIGIN: %f %f %f\n", utils->cam.origin.x, utils->cam.origin.y, utils->cam.origin.z);
	while (x <= utils->curr_img->dim.width)
	{
		y = 0;
		while (y <= utils->curr_img->dim.height)
		{
			screen_coords.x = (float)(2 * x) / (float)utils->curr_img->dim.width - 1.0f;
			screen_coords.y = (float)(-2 * y) / (float)utils->curr_img->dim.height + 1.0f;
			ray = get_ray(utils, screen_coords, &utils->cam);
			if (utils->visual_rays == 1)
			{
				if (x % 50 == 0 && y % 50 == 0)
					draw_ray_arrows(utils, &ray, 0x004466);
				if (x + utils->curr_img->dim.x0 == utils->mouse.x
					&& y + utils->curr_img->dim.y0 == utils->mouse.y)
					draw_ray_arrows(utils, &ray, 0xFF0000);
			}
			if (intersect_sphere(&ray, &(t_3f){0, 0, 0}, &(t_3f){0.0f, 0, -10.0f}, 1.0f))
				ft_pixel_put(x, y, 0x00FFFF, utils->curr_img);
			if (intersect_sphere(&ray, &(t_3f){0.0f, 0, 0.0f}, &(t_3f){3.0f, 0, -10.0f}, 1.0f))
				ft_pixel_put(x, y, 0xFFFF00, utils->curr_img);
			y++;
		}
		x++;
	}
}

void	draw_image1(t_utils *utils)
{
	if (utils->reference == 1)
	{
		checkerboard_carpet(utils);
		plot_object(utils, &utils->objects.teapot, &(t_3f){10, -10, 0}, 0x003364);
	}
	ray_plotting(utils);
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
	point = get_points(utils, utils->cam.dir.forward.x * 5,
		utils->cam.dir.forward.y * 5, utils->cam.dir.forward.z * 5);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_line){(int)sc_mid[0], (int)sc_mid[1],
		(int)point.x, (int)point.y}, 0x000000, 0xFF0000);
	point = get_points(utils, utils->cam.dir.right.x * 5,
		utils->cam.dir.right.y * 5, utils->cam.dir.right.z * 5);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_line){(int)sc_mid[0], (int)sc_mid[1],
		(int)point.x, (int)point.y}, 0x000000, 0x00FF00);
	point = get_points(utils, utils->cam.dir.up.x * 5,
		utils->cam.dir.up.y * 5, utils->cam.dir.up.z * 5);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_line){(int)sc_mid[0], (int)sc_mid[1],
		(int)point.x, (int)point.y}, 0x000000, 0x0000FF);
	point = get_points(utils, utils->cam.dir.left.x * 5,
		utils->cam.dir.left.y * 5, utils->cam.dir.up.z * 5);
	draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_line){(int)sc_mid[0], (int)sc_mid[1],
		(int)point.x, (int)point.y}, 0x000000, 0xFFDD45);
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
	image_processing(utils, &utils->img3, 0x8899BBFF);
	free(str);
}
