/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/11 12:32:18 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	draw_ray_arrows(t_utils *utils, t_3f ray, t_uint color, t_img *img)
{
	t_3f	p[2];
	t_proj	proj;

	proj = init_proj(60, &(t_2i){img->dim.width, img->dim.height}, &(t_2f){0.1f, 1000.0f});
	ray.x *= -10;
	ray.y *= -10;
	ray.z *= 10;
	p[0] = get_points(utils, &ray, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	p[1] = get_points(utils, &(t_3f){0, 0, 0}, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	if (utils->visual_rays == 1)
	{
		draw_circle(&(t_pxl_func){&ft_pixel_put, img}, &(t_2i){(int)p[0].x, (int)p[0].y}, 3, color);
		draw_circle(&(t_pxl_func){&ft_pixel_put, img}, &(t_2i){(int)p[0].x, (int)p[0].y}, 2, 0xFFFFFF);
		draw_circle(&(t_pxl_func){&ft_pixel_put, img}, &(t_2i){(int)p[1].x, (int)p[1].y}, 3, 0xFFFFFF);
	}
	if (utils->visual_rays == 2)
	{
		if (p[1].z < p[0].z)
			draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
				&(t_line){(int)p[1].x, (int)p[1].y, (int)p[0].x, (int)p[0].y},
				color, 0xFFFFFF);
		else
			draw_line(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
				&(t_line){(int)p[0].x, (int)p[0].y, (int)p[1].x, (int)p[1].y},
				color, 0xFFFFFF);
	}
}

static t_3f	get_camera_rotation(t_utils *utils, t_3f *direction)
{
	t_3f	point_rot[3];

	matrix_multip(direction, &point_rot[0], &utils->rmatrix_x); 
	matrix_multip(&point_rot[0], &point_rot[1], &utils->rmatrix_y); 
	matrix_multip(&point_rot[1], &point_rot[2], &utils->rmatrix_z); 
	return (point_rot[2]);
}

static void	get_camera_directions(t_utils *utils, t_ray *cam)
{
	cam->dir.forward = get_camera_rotation(utils, &(t_3f){0.0f, 0.0f, -1.0f});
	cam->dir.back = get_camera_rotation(utils, &(t_3f){0.0f, 0.0f, 1.0f});
	cam->dir.right = get_camera_rotation(utils, &(t_3f){1.0f, 0.0f, 0.0f});
	cam->dir.left = get_camera_rotation(utils, &(t_3f){-1.0f, 0.0f, 0.0f});
	cam->dir.up = get_camera_rotation(utils, &(t_3f){0.0f, 1.0f, 0.0f});
	cam->dir.down = get_camera_rotation(utils, &(t_3f){0.0f, -1.0f, 0.0f});
}

static t_3f	intersect(t_utils *utils, t_3f *ray, t_3f *ray_origin, t_img *img, t_2i *xy, t_3f *point_hit, int *object_no)
{
	t_list		*objects;
	t_object	*object;
	t_3f		origin;
	t_3f		normal;
	t_2f		t[2];
	int			i;
	int			ret;

	t[1].x = 1000;
	t[1].y = 1000;
	t[0].x = 1000;
	t[0].y = 1000;
	normal = (t_3f){0.0f, 0.0f, 0.0f};
	*object_no = 0;
	i = 0;
	ret = 0;
	objects = utils->objects;
	while (objects != NULL)
	{
		object = (t_object *)objects->content;
		if (object->type == 1)
		{
			origin = subtract_vectors(&object->origin, ray_origin);
			ret = intersect_sphere(ray, &origin, object->radius, &t[1]);
		}
		else if (object->type == 2)
			ret = intersect_plane(ray, &object->origin, ray_origin , &object->normal, &t[1].x);
		if (ret)
		{
			if (t[1].x < t[0].x)
			{
				*point_hit = scale_vector(t[1].x, ray);
				*point_hit = add_vectors(&*point_hit, ray_origin);
				if (object->type == 1)
					normal = normalize_vector(subtract_vectors(point_hit, &object->origin));
				if (object->type == 2)
				{
					//normal = scale_vector(-1.0f, &object->normal);
					normal = (t_3f){0.0f, 0.0f, 0.0f};
				}
				t[0] = t[1];
				utils->curr_object = object;
				if (utils->render == -1)
					ft_pixel_put(xy->x, xy->y, object->color, img);
				*object_no = i;
			}
		}
		i++;
		objects = objects->next;
	}
	if (xy->x == img->dim.width / 2 && xy->y == img->dim.height / 2)
	{
		printf("T: 0[%.2f] 1[%.2f]\n", t[0].x, t[0].y);
		printf("POINT_HIT: %f %f %f\n", point_hit->x, point_hit->y, point_hit->z);
		printf("LIGHT_HIT: %f %f %f\n", point_hit->x, point_hit->y, point_hit->z);
		printf("CAMERA: %f %f %f\n", utils->cam.origin.x, utils->cam.origin.y, utils->cam.origin.z);
	}
	return (normal);
}

static int	intersect_light(t_utils *utils, t_3f *ray, t_3f *ray_origin)
{
	t_list		*objects;
	t_object	*object;
	t_3f		origin;
	t_2f		t[2];
	int			object_no;
	int			i;
	int			ret;

	t[1].x = 1000;
	t[1].y = 1000;
	t[0].x = 1000;
	t[0].y = 1000;
	object_no = 0;
	i = 0;
	ret = 0;
	objects = utils->objects;
	while (objects != NULL)
	{
		object = (t_object *)objects->content;
		if (object->type == 1)
		{
			origin = subtract_vectors(&object->origin, ray_origin);
			ret = intersect_sphere(ray, &origin, object->radius, &t[1]);
		}
		else if (object->type == 2)
			ret = intersect_plane(ray, &object->origin, ray_origin , &object->normal, &t[1].x);
		if (ret)
		{
			if (t[1].x < t[0].x)
			{
				object_no = i;
				t[0] = t[1];
			}
		}
		i++;
		objects = objects->next;
	}
	return (object_no);
}

void	ray_plotting(t_utils *utils, t_img *img)
{
	t_3f	point_hit;
	t_3f	light_dir;
	t_2f	scrn;
	t_3f	normal;
	t_3f	ray;
	double	t;
	double	lumen;
	double	light_level;
	int		object_no[2];
	int		rgb[3];
	int		xy[2];

	lumen = 200.0;
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
			normal = intersect(utils, &ray, &utils->cam.origin, img, &(t_2i){xy[0], xy[1]}, &point_hit, &object_no[0]);
			light_dir = subtract_vectors(&point_hit, &utils->light.origin);
			t = sqrt(((utils->light.origin.x - light_dir.x) * (utils->light.origin.x -light_dir.x)) + ((utils->light.origin.y - light_dir.y) * (utils->light.origin.y - light_dir.y)) + ((utils->light.origin.z - light_dir.z) * (utils->light.origin.z - light_dir.z)));
			t = t / lumen;
			light_dir = normalize_vector(light_dir);
			object_no[1] = intersect_light(utils, &light_dir, &utils->light.origin);
			light_dir = scale_vector(-1.0f, &light_dir);
			if (normal.x == 0.0f && normal.y == 0.0f && normal.z == 0.0f)
				light_level = 1.0f;
			else
				light_level = (double)dot_product(&normal, &light_dir);
			light_level -= t;
			if (light_level < 0)
				light_level = 0.0f;
			seperate_rgb(utils->curr_object->color, &rgb[0], &rgb[1], &rgb[2]);
			rgb[0] *= light_level;
			rgb[1] *= light_level;
			rgb[2] *= light_level;
			if (xy[0] == img->dim.width / 2 && xy[1] == img->dim.height / 2)
			{
				printf("light distance: %lf\n", t);
				printf("OBJECT NO: %d | %d\n", object_no[0], object_no[1]);
			}
			if (utils->render == 1 && object_no[0] == object_no[1])
				ft_pixel_put(xy[0], xy[1], combine_rgb(rgb[0], rgb[1], rgb[2]), img);
			xy[1]++;
		}
		xy[0]++;
	}
}

void	draw_image1(t_utils *utils)
{
	ray_plotting(utils, &utils->img);
	draw_circle(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_2i){(int)utils->curr_img->dim.width / 2, (int)utils->curr_img->dim.height / 2}, 3, 0x009557);
	draw_circle(&(t_pxl_func){&ft_pixel_put, utils->curr_img}, &(t_2i){(int)utils->curr_img->dim.width / 2, (int)utils->curr_img->dim.height / 2}, 2, 0xFFFFFF);
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
			xy[1] += 20;
		}
		xy[0] += 20;
	}
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0x00FFDD);
}

static void	image_processing(t_utils *utils, t_img *img, t_uint fill_color)
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
	if (utils->visual_rays >= 1)
		image_processing(utils, &utils->img3, 0x67000000);
	free(str);
}
