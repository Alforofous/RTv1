/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:41:05 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/20 11:04:46 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	i = 1;
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
				*point_hit = add_vectors(point_hit, ray_origin);
				t[0] = t[1];
				if (object->type == 1)
				{
					normal = normalize_vector(subtract_vectors(point_hit, &object->origin));
					if (t[0].x == t[0].y)
						normal = scale_vector(-1.0f, &normal);
				}
				if (object->type == 2)
					normal = (t_3f){0.0f, 0.0f, 0.0f};
				utils->closest_object = object;
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
		printf("NORMAL: %f %f %f\n", normal.x, normal.y, normal.z);
	}
	return (normal);
}

static int	intersect_light(t_utils *utils, t_3f *ray, t_3f *ray_origin, t_3f *light_hit)
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
	i = 1;
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
				*light_hit = scale_vector(t[1].x, ray);
				*light_hit = add_vectors(light_hit, ray_origin);
				object_no = i;
				t[0] = t[1];
			}
		}
		i++;
		objects = objects->next;
	}
	return (object_no);
}

void	ray_plotting(t_utils *utils, t_img *img, t_2i coords)
{
	t_3f	point_hit;
	t_3f	light_hit;
	t_2f	scrn;
	t_3f	normal;
	t_3f	ray;
	t_3f	origin;
	t_2f	tt;
	double	light_level;
	double	t;
	int		object_no[2];
	t_3i	rgb;
	t_3i	rgb_t;
	int		i;

	i = 0;
	/*printf("CAMERA ORIGIN: %f %f %f\n", utils->cam.origin.x, utils->cam.origin.y, utils->cam.origin.z);
	printf("CAMERA FORWARD: %f %f %f\n", utils->cam.dir.forward.x, utils->cam.dir.forward.y, utils->cam.dir.forward.z);
	printf("LIGHT ORIGIN: %f %f %f\n", utils->light[i].origin.x, utils->light[i].origin.y, utils->light[i].origin.z);*/
	i = 0;
	rgb_t.x = 0;
	rgb_t.y = 0;
	rgb_t.z = 0;
	scrn.x = (float)(2 * coords.x) / (float)img->dim.width - 1.0f;
	scrn.y = (float)(-2 * coords.y) / (float)img->dim.height + 1.0f;
	ray = get_ray(scrn, &utils->cam, &utils->proj);
	normal = intersect(utils, &ray, &utils->cam.origin, img, &(t_2i){coords.x, coords.y}, &point_hit, &object_no[0]);
	if (utils->closest_object != NULL)
	{
		seperate_rgb(utils->closest_object->color, &rgb.x, &rgb.y, &rgb.z);
	}
	if (utils->render == 1)
	{
		while (i < 3)
		{
			utils->light[i].dir = subtract_vectors(&point_hit, &utils->light[i].origin);
			t = sqrt(((utils->light[i].dir.x) * (utils->light[i].dir.x)) + ((utils->light[i].dir.y) * (utils->light[i].dir.y)) + ((utils->light[i].dir.z) * (utils->light[i].dir.z)));
			t = t / utils->light[i].lumen;
			utils->light[i].dir = normalize_vector(utils->light[i].dir);
			object_no[1] = intersect_light(utils, &utils->light[i].dir, &utils->light[i].origin, &light_hit);
			utils->light[i].dir = scale_vector(-1.0f, &utils->light[i].dir);
			if (normal.x == 0.0f && normal.y == 0.0f && normal.z == 0.0f)
				light_level = 1.0f;
			else
			{
				light_level = (double)dot_product(&normal, &utils->light[i].dir);
			}
				light_level -= t;
			if (light_level < 0.0)
				light_level = 0.0;
			if (object_no[0] == object_no[1] && light_level > 0 && object_no[0] > 0 && fabs(light_hit.x - point_hit.x) < 0.1 && fabs(light_hit.z - point_hit.z) < 0.1 && fabs(light_hit.y - point_hit.y) < 0.1)
			{
				rgb_t.x += (int)(rgb.x * light_level * utils->light[i].color.x);
				rgb_t.y += (int)(rgb.y * light_level * utils->light[i].color.y);
				rgb_t.z += (int)(rgb.z * light_level * utils->light[i].color.z);
				rgb_t.x = ft_min(rgb_t.x, 255);
				rgb_t.y = ft_min(rgb_t.y, 255);
				rgb_t.z = ft_min(rgb_t.z, 255);
			}
			/*if (coords.x == img->dim.width / 2 && coords.y == img->dim.height / 2)
			{
				printf("____________________________________________\n*****LIGHT NO: [%d]*****\n", i);
				printf("LIGHT HIT: %f %f %f\n", light_hit.x, light_hit.y, light_hit.z);
				printf("POINT SIMILARITY: %f %f %f\n", fabs(light_hit.x - point_hit.x), fabs(light_hit.y - point_hit.y), fabs(light_hit.z - point_hit.z));
				printf("t / lumen ratio: %lf\n", t);
				printf("normal & light similarity: %lf\n", (double)dot_product(&normal, &utils->light[i].dir));
				printf("light level %%: %lf\n", light_level);
				printf("OBJECT NO: %d | %d\n", object_no[0], object_no[1]);
			}*/
			i++;
		}
		ft_pixel_put(coords.x, coords.y, combine_rgb(rgb_t.x, rgb_t.y, rgb_t.z), img);
	}
	i = 0;
	while (i < 3)
	{
		origin = subtract_vectors(&utils->light[i].origin, &utils->cam.origin);
		if (intersect_sphere(&ray, &origin, 0.5, &tt))
			ft_pixel_put(coords.x, coords.y, combine_rgb((int)(utils->light[i].color.x * 200), (int)(utils->light[i].color.y * 200), (int)(utils->light[i].color.z * 200)), img);
		i++;
	}
}

void	draw_image1(t_utils *utils)
{
	t_2i	coords;

	coords.x = 0;
	get_camera_directions(utils, &utils->cam);
	while (coords.x <= utils->curr_img->dim.width)
	{
		coords.y = 0;
		while (coords.y <= utils->curr_img->dim.height)
		{
			ray_plotting(utils, &utils->img, coords);
			coords.y += 1;
		}
		coords.x += 1;
	}
	draw_circle(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){(int)utils->curr_img->dim.width / 2,
		(int)utils->curr_img->dim.height / 2}, 3, 0x004557);
	draw_circle(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){(int)utils->curr_img->dim.width / 2,
		(int)utils->curr_img->dim.height / 2}, 2, 0xFFFFFF);
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}