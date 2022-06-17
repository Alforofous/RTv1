/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 11:31:06 by dmalesev         ###   ########.fr       */
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
					(void *)utils->curr_img);
			y++;
		}
		x++;
	}
}

static void	draw_ray_arrows(t_utils *utils, t_3f *ray, int color)
{
	t_3f	point;
	t_3f	point2;

	ray->y *= -1;
	ray->x *= 10;
	ray->y *= 10;
	ray->z *= 10;
	point = get_points(utils, ray->x, ray->z, ray->y);
	point2 = get_points(utils, 0, 0, 0);
	draw_circle(&(t_pxl_func){&ft_pixel_put, (void *)utils->curr_img}, &(t_2i){(int)point2.x, (int)point2.y}, 3, 0xFFFFFF);
	draw_circle(&(t_pxl_func){&ft_pixel_put, (void *)utils->curr_img}, &(t_2i){(int)point.x, (int)point.y}, 3, color);
	draw_line(&(t_pxl_func){&ft_pixel_put, (void *)utils->curr_img}, &(t_line){(int)point2.x, (int)point2.y,
		(int)point.x, (int)point.y}, color, 0xFFFFFF);
}

static t_3f	get_camera_position(t_3f *target, t_3f *origin)
{
	t_3f	camera;

	camera = normalize_vector(subtract_vectors(target, origin));
	return (camera);
}

static t_3f	get_camera_rotation(t_utils *utils)
{
	t_3f	start;
	t_3f	point_rot[3];

	start.x = 0.0f;
	start.y = 0.0f;
	start.z = -1.0f;
	init_pmatrix(utils);
	init_rmatrix_x(utils);
	init_rmatrix_y(utils);
	init_rmatrix_z(utils);
	matrix_multip(&start, &point_rot[0], &utils->rmatrix_z); 
	matrix_multip(&point_rot[0], &point_rot[1], &utils->rmatrix_y); 
	matrix_multip(&point_rot[1], &point_rot[2], &utils->rmatrix_x); 
	return (point_rot[2]);
}

void	ray_plotting(t_utils *utils)
{
	int		x;
	int		y;
	t_2f	screen_coords;
	t_3f	ray;
	t_3f	camera;

	x = 0;
	while (x <= utils->curr_img->dim.width)
	{
		y = 0;
		while (y <= utils->curr_img->dim.height)
		{
			screen_coords.x = (float)(2 * x) / (float)utils->curr_img->dim.width - 1.0f;
			screen_coords.y = (float)(-2 * y) / (float)utils->curr_img->dim.height + 1.0f;
			camera = get_camera_rotation(utils);
			camera = get_camera_position(&camera, &utils->cam.origin);
			ray = get_ray(utils, screen_coords, camera);
			if (utils->visual_rays == 1)
			{
				if (x % 50 == 0 && y % 50 == 0)
					draw_ray_arrows(utils, &ray, 0x004466);
				if (x + utils->curr_img->dim.x0 == utils->mouse.x
					&& y + utils->curr_img->dim.y0 == utils->mouse.y)
					draw_ray_arrows(utils, &ray, 0xFF0000);
			}
			if (intersect_sphere(&ray, &(t_3f){0, 0, 0}, &(t_3f){0.0f, 0, -50.0f}, 10.0f))
			{
				ft_pixel_put(x, y, 0x00FFFF, (void *)utils->curr_img);
			}
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
	init_proj(utils);
	ray_plotting(utils);
	draw_rect(&(t_pxl_func){&ft_pixel_put, (void *)utils->curr_img}, &(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}

void	draw_image2(t_utils *utils)
{
	draw_rect(&(t_pxl_func){&ft_pixel_put, (void *)utils->curr_img}, &(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}

static void	image_processing(t_utils *utils, t_img *img)
{
	utils->curr_img = img;
	ft_clear_img(utils);
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
	image_processing(utils, &utils->img);
	interv[1] = clock();
	str = ft_ftoa((float)(interv[1] - interv[0]) / CLOCKS_PER_SEC, 5);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for render time...", -1);
	mlx_string_put(utils->mlx, utils->win, utils->img.dim.x0 + xy[0],
		utils->img.dim.y0 + xy[1], 0x000000, str);
	mlx_string_put(utils->mlx, utils->win, utils->img.dim.x0 + xy[0],
		utils->img.dim.y0 + xy[1] + 1, 0xFFFFFF, str);
	free(str);
	image_processing(utils, &utils->img2);
}
