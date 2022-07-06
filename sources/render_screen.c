/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/06 11:32:22 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	draw_ray_arrows(t_utils *utils, t_3f ray, t_u_int color, t_img *img)
{
	t_3f	point;
	t_3f	point2;
	t_proj	proj;

	proj = init_proj(60, &(t_2i){img->dim.width, img->dim.height}, &(t_2f){0.1f, 1000.0f});
	ray.x *= -10;
	ray.y *= -10;
	ray.z *= 10;
	point = get_points(utils, &ray, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	point2 = get_points(utils, &(t_3f){0, 0, 0}, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	if (utils->visual_rays == 1)
		draw_circle(&(t_pxl_func){&ft_pixel_put, img}, &(t_2i){(int)point.x, (int)point.y}, 3, color);
	if (utils->reference == 1)
		draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_line){(int)point2.x, (int)point2.y,
			(int)point.x, (int)point.y}, color, 0xFFFFFF);
	if (utils->visual_rays == 1)
		draw_circle(&(t_pxl_func){&ft_pixel_put, img}, &(t_2i){(int)point2.x, (int)point2.y}, 3, 0xFFFFFF);
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

static void	bounce_ray(t_3f *ray)
{
	ray++;
}

void	intersect(t_utils *utils, t_list *objects, t_3f *ray, t_img *img, t_2i *xy)
{
	t_3f		center;
	t_2f		t[2];
	t_sphere	*sphere;

	t[1].x = 100;
	t[1].y = 100;
	t[0].x = 100;
	t[0].y = 100;
	while (objects)
	{
		if (sizeof(*(objects->content)) == sizeof(t_sphere))
		{
			sphere = (t_sphere *)objects->content;
			center = subtract_vectors(&sphere->origin, &utils->cam.origin);
			if (intersect_sphere(ray, &center, sphere->radius, &t[1]))
			{
			if (t[1].x < t[0].x)
				{
				t[0] = t[1];
				ft_pixel_put(xy->x, xy->y, sphere->color, img);
				}
			}
		}
		objects = objects->next;
	}
	center = subtract_vectors(&(t_3f){-4.0f, 4.0f, -10.0f}, &utils->cam.origin);
	if (intersect_sphere(ray, &center, 3.0f, &t[1]))
	{
		if (t[1].x < t[0].x)
		{
			t[0] = t[1];
			ft_pixel_put(xy->x, xy->y, 0x770000, img);
		}
	}
	if (intersect_plane(&(t_3f){0.0f, -1.0f, 0.0f}, &(t_3f){0.0f, -0.1f, 0.0f}, &utils->cam.origin, ray, &t[1].x))
	{
		if (t[1].x < t[0].x)
		{
			t[0] = t[1];
			ft_pixel_put(xy->x, xy->y, 0xDD5500, img);
		}
	}
	if (intersect_plane(&(t_3f){0.0f, 1.0f, 0.0f}, &(t_3f){0.0f, -0.1f, 0.0f}, &utils->cam.origin, ray, &t[1].x))
	{
		if (t[1].x < t[0].x)
		{
			t[0] = t[1];
			ft_pixel_put(xy->x, xy->y, 0xDD5500, img);
		}
	}
	if (xy->x == img->dim.width / 2 && xy->y == img->dim.height / 2)
		printf("T: 0[%.2f] 1[%.2f]\n", t[0].x, t[0].y);
}

void	ray_plotting(t_utils *utils, t_img *img)
{
	int		xy[2];
	t_2f	scrn;
	t_3f	ray;

	xy[0] = 0;
	get_camera_directions(utils, &utils->cam);
	while (xy[0] < img->dim.width)
	{
		xy[1] = 0;
		while (xy[1] < img->dim.height)
		{
			scrn.x = (float)(2 * xy[0]) / (float)img->dim.width - 1.0f;
			scrn.y = (float)(-2 * xy[1]) / (float)img->dim.height + 1.0f;
			ray = get_ray(scrn, &utils->cam, &utils->proj);
			intersect(utils, utils->objects, &ray, img, &(t_2i){xy[0], xy[1]});
			bounce_ray(&ray);
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

void	draw_image3(t_utils *utils)
{
	int		xy[2];
	t_2f	scrn;
	t_3f	ray;
	t_img	*img;

	img = &utils->img3;
	xy[0] = 0;
	get_camera_directions(utils, &utils->cam);
	while (xy[0] < img->dim.width)
	{
		xy[1] = 0;
		while (xy[1] < img->dim.height)
		{
			scrn.x = (float)(2 * xy[0]) / (float)img->dim.width - 1.0f;
			scrn.y = (float)(-2 * xy[1]) / (float)img->dim.height + 1.0f;
			ray = get_ray(scrn, &utils->cam, &utils->proj);
			draw_ray_arrows(utils, ray, 0x004466, img);
			if (xy[0] + img->dim.x0 == utils->mouse.x
				&& xy[1] + img->dim.y0 == utils->mouse.y)
			draw_ray_arrows(utils, ray, 0xFF0000, img);
			xy[1] += 10;
		}
		xy[0] += 10;
	}
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0x00FFDD);
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
	if (utils->visual_rays == 1 || utils->reference == 1)
		image_processing(utils, &utils->img3, 0xDC338855);
	free(str);
}
