/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:41:05 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/16 14:52:05 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3f	intersect(t_utils *utils, t_3f *ray, t_3f *ray_origin, t_img *img, t_2i *xy, t_3f *point_hit, int *object_no)
{
	t_list		*objects;
	t_object	*object;
	t_3f		origin;
	t_3f		normal;
	t_3f		tip;
	t_3f		vect[2];
	t_2d		t[2];
	float		dp;
	int			i;
	int			ret;
	t_read_obj	obj;

	t[1].x = 10000;
	t[1].y = 10000;
	t[0].x = 10000;
	t[0].y = 10000;
	normal = (t_3f){0.0f, 0.0f, 0.0f};
	*object_no = 0;
	i = 1;
	ret = 0;
	objects = utils->objects;
	obj.plane = NULL;
	while (objects != NULL)
	{
		object = (t_object *)objects->content;
		if (object->type == 0)
		{
			obj.light = (t_light *)object->content;
			origin = subtract_vectors(object->origin, *ray_origin);
			ret = intersect_sphere(ray, &origin, 0.1f, &t[1]);
		}
		else if (object->type == 1)
		{
			obj.sphere = (t_sphere *)object->content;
			origin = subtract_vectors(object->origin, *ray_origin);
			ret = intersect_sphere(ray, &origin, obj.sphere->radius, &t[1]);
		}
		else if (object->type == 2)
		{
			obj.plane = (t_plane *)object->content;
			ret = intersect_plane(ray, &object->origin, ray_origin , &obj.plane->normal, &t[1].x);
		}
		else if (object->type == 3)
		{
			obj.cone = (t_cone *)object->content;
			tip = add_vectors(object->origin, obj.cone->tip);
			ret = intersect_cone(ray_origin, ray, &object->origin, &tip, obj.cone->radius, &t[1]);
		}
		else if (object->type == 4)
		{
			obj.cylinder = (t_cylinder *)object->content;
			tip = add_vectors(object->origin, obj.cylinder->orientation);
			ret = intersect_cylinder(ray_origin, ray, &object->origin, &tip, obj.cylinder->radius, &t[1]);
		}
		if (ret)
		{
			if (t[1].x < t[0].x)
			{
				*point_hit = scale_vector(*ray, (float)t[1].x);
				*point_hit = add_vectors(*point_hit, *ray_origin);
				t[0] = t[1];
				if (object->type == 1)
					normal = (t_3f){0.0f, 0.0f, 0.0f};
				if (object->type == 1)
				{
					normal = normalize_vector(subtract_vectors(*point_hit, object->origin));
					if (t[0].x == t[0].y)
						normal = scale_vector(normal, -1.0f);
				}
				else if (object->type == 2)
				{
					normal = scale_vector(obj.plane->normal, -1.0f);
					//normal = (t_3f){0.0f, 0.0f, 0.0f};
				}
				else if (object->type == 3)
				{
					vect[0] = normalize_vector(subtract_vectors(*point_hit, tip));
					vect[1] = normalize_vector(subtract_vectors(tip, object->origin));
					dp = (float)fabs(acos(dot_product(vect[0], vect[1])));
					dp = (float)vector_magnitude(subtract_vectors(*point_hit, tip)) / cosf(dp);
					normal = add_vectors(tip, scale_vector(vect[1], dp));
					normal = normalize_vector(subtract_vectors(*point_hit, normal));
					if (t[0].x == t[0].y)
						normal = scale_vector(normal, -1.0f);
				}
				else if (object->type == 4)
				{
					dp = dot_product(subtract_vectors(*point_hit, object->origin), normalize_vector(subtract_vectors(object->origin, tip)));
					normal = add_vectors(object->origin, scale_vector(normalize_vector(subtract_vectors(object->origin, tip)), dp));
					normal = normalize_vector(subtract_vectors(*point_hit, normal));
					if (t[0].x == t[0].y)
						normal = scale_vector(normal, -1.0f);
				}
				utils->closest_object = object;
				if (utils->render == -1)
				{
					if (t[1].x == t[1].y)
						put_pixel(xy->x, xy->y, ~object->color, img);
					else
						put_pixel(xy->x, xy->y, object->color, img);
				}
				*object_no = i;
			}
		}
		if (t[0].x == 10000 && t[0].y == 10000)
			put_pixel(xy->x, xy->y, 0x444444, img);
		i++;
		objects = objects->next;
	}
	if (xy->x == img->dim.width / 2 && xy->y == img->dim.height / 2)
	{
		printf("T: x[%.2f] y[%.2f]\n", t[1].x, t[1].y);
		printf("POINT_HIT: %f %f %f\n", point_hit->x, point_hit->y, point_hit->z);
		printf("NORMAL: %f %f %f\n", normal.x, normal.y, normal.z);
		if (utils->closest_object != NULL)
			printf("CLOSEST OBJECT: %d\n", utils->closest_object->type);
	}
	return (normal);
}

static int	intersect_light(t_utils *utils, t_3f *ray, t_3f *ray_origin, t_3f *light_hit)
{
	t_list		*objects;
	t_object	*object;
	t_3f		origin;
	t_3f		tip;
	t_2d		t[2];
	int			object_no;
	int			i;
	int			ret;
	t_read_obj	obj;

	t[1].x = 10000;
	t[1].y = 10000;
	t[0].x = 10000;
	t[0].y = 10000;
	object_no = 0;
	i = 1;
	objects = utils->objects;
	while (objects != NULL)
	{
		ret = 0;
		object = (t_object *)objects->content;
		if (object->type == 1)
		{
			obj.sphere = (t_sphere *)object->content;
			origin = subtract_vectors(object->origin, *ray_origin);
			ret = intersect_sphere(ray, &origin, obj.sphere->radius, &t[1]);
		}
		else if (object->type == 2)
		{
			obj.plane = (t_plane *)object->content;
			ret = intersect_plane(ray, &object->origin, ray_origin , &obj.plane->normal, &t[1].x);
		}
		else if (object->type == 3)
		{
			obj.cone = (t_cone *)object->content;
			tip = add_vectors(object->origin, obj.cone->tip);
			ret = intersect_cone(ray_origin, ray, &object->origin, &tip, obj.cone->radius, &t[1]);
		}
		else if (object->type == 4)
		{
			obj.cylinder = (t_cylinder *)object->content;
			tip = add_vectors(object->origin, obj.cylinder->orientation);
			ret = intersect_cylinder(ray_origin, ray, &object->origin, &tip, obj.cylinder->radius, &t[1]);
		}
		if (ret)
		{
			if (t[1].x < t[0].x)
			{
				*light_hit = scale_vector(*ray, (float)t[1].x);
				*light_hit = add_vectors(*light_hit, *ray_origin);
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
	t_list		*objects;
	t_object	*object;
	t_3f		point_hit;
	t_3f		light_hit;
	t_2f		scrn;
	t_3f		normal;
	t_3f		ray;
	t_3f		light_color;
	double		light_level;
	double		t;
	int			object_no[2];
	t_3i		temp_rgb;
	t_3i		rgb;
	t_3i		rgb_t;
	t_read_obj	obj;

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
		objects = utils->objects;
		while (objects != NULL)
		{
			object = (t_object *)objects->content;
			if (object->type == 0)
			{
				obj.light = (t_light *)object->content;
				seperate_rgb(object->color, &temp_rgb.x, &temp_rgb.y, &temp_rgb.z);
				light_color.x = (float)temp_rgb.x / 255;
				light_color.y = (float)temp_rgb.y / 255;
				light_color.z = (float)temp_rgb.z / 255;
				obj.light->dir = subtract_vectors(point_hit, object->origin);
				t = sqrt(((obj.light->dir.x) * (obj.light->dir.x)) + ((obj.light->dir.y) * (obj.light->dir.y)) + ((obj.light->dir.z) * (obj.light->dir.z)));
				t = t / obj.light->lumen;
				obj.light->dir = normalize_vector(obj.light->dir);
				object_no[1] = intersect_light(utils, &obj.light->dir, &object->origin, &light_hit);
				obj.light->dir = scale_vector(obj.light->dir, -1.0f);
				/*if (normal.x == 0.0f && normal.y == 0.0f && normal.z == 0.0f)
					 light_level = 1.0f;
				else
					light_level = (double)dot_product(normal, obj.light->dir);
				{
				}*/
				light_level = (double)dot_product(normal, obj.light->dir);
				light_level -= t;
				if (light_level < 0.0)
					light_level = 0.0;
				if (object_no[0] == object_no[1] && light_level > 0 && object_no[0] > 0 && fabs(light_hit.x - point_hit.x) < 0.1 && fabs(light_hit.z - point_hit.z) < 0.1 && fabs(light_hit.y - point_hit.y) < 0.1)
				{
					rgb_t.x += (int)(rgb.x * light_level * light_color.x);
					rgb_t.y += (int)(rgb.y * light_level * light_color.y);
					rgb_t.z += (int)(rgb.z * light_level * light_color.z);
					rgb_t.x = ft_min(rgb_t.x, 255);
					rgb_t.y = ft_min(rgb_t.y, 255);
					rgb_t.z = ft_min(rgb_t.z, 255);
				}
				if (coords.x == img->dim.width / 2 && coords.y == img->dim.height / 2)
				{
					printf("t / lumen ratio: %lf\n", t);
					printf("normal & light similarity: %lf\n", (double)dot_product(normal, obj.light->dir));
					printf("light level %%: %lf\n", light_level);
					printf("OBJECT NO: %d | %d\n", object_no[0], object_no[1]);
				}
			}
			objects = objects->next;
		}
		put_pixel(coords.x, coords.y, combine_rgb(rgb_t.x, rgb_t.y, rgb_t.z), img);
	}
}

static void	draw_aim_point(t_utils *utils)
{
	draw_circle(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){(int)utils->curr_img->dim.width / 2,
		(int)utils->curr_img->dim.height / 2}, 3, 0x004557);
	draw_circle(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){(int)utils->curr_img->dim.width / 2,
		(int)utils->curr_img->dim.height / 2}, 2, 0xFFFFFF);
	draw_rect(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}

void	draw_image1(t_utils *utils)
{
	t_2i			coords;
	char			*str;
	static clock_t	interv[2];
	float			plot_time;

	coords.x = 0;
	get_camera_directions(utils, &utils->cam);
	//printf("CAMERA ORIGIN: %f %f %f\n", utils->cam.origin.x, utils->cam.origin.y, utils->cam.origin.z);
	//printf("CAMERA FORWARD: %f %f %f\n", utils->cam.dir.forward.x, utils->cam.dir.forward.y, utils->cam.dir.forward.z);
	if (utils->density.x == 9 && utils->density.y == 9)
		interv[0] = clock();
	while (coords.x <= utils->curr_img->dim.width)
	{
		if (coords.x % 10 == utils->density.x)
		{
			coords.y = 0;
			while (coords.y <= utils->curr_img->dim.height)
			{
				if (coords.y % 10 == utils->density.y)
				{
					ray_plotting(utils, &utils->img, coords);
				}
				coords.y += 1;
			}
		}
		coords.x += 1;
	}
	draw_aim_point(utils);
	if (!(utils->density.x == 0 && utils->density.y == 0))
		return ;
	interv[1] = clock();
	plot_time = (float)(interv[1] - interv[0]) / CLOCKS_PER_SEC;
	coords.x = utils->img.dim.width / 80;
	coords.y = utils->img.dim.height / 50;
	str = ft_ftoa(plot_time, 5);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for render time...", -1);
	render_str("Plot time:", &(t_pxl){utils->font, &put_pixel, utils->curr_img}, &(t_2i){coords.x + 2, coords.y + 2}, 0x000000);
	coords = render_str("Plot time:", &(t_pxl){utils->font, &put_pixel, utils->curr_img}, &(t_2i){coords.x, coords.y}, 0xFFFFFF);
	render_str(str, &(t_pxl){utils->font, &put_pixel, utils->curr_img}, &(t_2i){coords.x + 2, coords.y + 2}, 0x000000);
	render_str(str, &(t_pxl){utils->font, &put_pixel, utils->curr_img}, &(t_2i){coords.x, coords.y}, 0xFFFFFF);
	free(str);
}
