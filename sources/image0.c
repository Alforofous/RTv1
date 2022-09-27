/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:41:05 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/27 14:33:26 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3f	intersect(t_utils *utils, t_3f *ray, t_3f *ray_origin, t_img *img, t_2i *xy, t_3f *point_hit, t_2d *t)
{
	t_list		*objects;
	t_object	*object;
	t_3f		normal;
	t_3f		axis;
	t_3f		vect[2];
	t_2d		t2;
	float		dp;
	int			i;
	int			ret;
	t_obj_ptrs	obj;

	t->x = T_MAX;
	t->y = T_MAX;
	t2.x = T_MAX;
	t2.y = T_MAX;
	normal = (t_3f){0.0f, 0.0f, 0.0f};
	i = 1;
	ret = 0;
	objects = utils->objects;
	obj.plane = NULL;
	while (objects != NULL)
	{
		object = (t_object *)objects->content;
		if (object->type == 0 && utils->light_render == 1)
		{
			obj.light = (t_light *)object->content;
			ret = intersect_sphere(ray, ray_origin, &object->origin, 0.5f, &t2);
		}
		else if (object->type == 1)
		{
			obj.sphere = (t_sphere *)object->content;
			ret = intersect_sphere(ray, ray_origin, &object->origin, obj.sphere->radius, &t2);
		}
		else if (object->type == 2)
		{
			obj.plane = (t_plane *)object->content;
			ret = intersect_plane(ray, &object->origin, ray_origin , &obj.plane->normal, &t2.x);
		}
		else if (object->type == 3)
		{
			obj.cone = (t_cone *)object->content;
			axis = add_vectors(object->origin, scale_vector(obj.cone->axis, obj.cone->axis_length));
			ret = intersect_cone(ray_origin, ray, &object->origin, &axis, obj.cone->radius, &t2);
		}
		else if (object->type == 4)
		{
			obj.cylinder = (t_cylinder *)object->content;
			axis = add_vectors(object->origin, scale_vector(obj.cylinder->axis, obj.cylinder->axis_length));
			ret = intersect_cylinder(ray_origin, ray, &object->origin, &axis, obj.cylinder->radius, &t2);
		}
		if (ret)
		{
			if (t2.x < t->x)
			{
				*point_hit = scale_vector(*ray, (float)t2.x);
				*point_hit = add_vectors(*point_hit, *ray_origin);
				*t = t2;
				if (object->type == 1 || object->type == 0)
				{
					normal = normalize_vector(subtract_vectors(*point_hit, object->origin));
					if (t->x == t->y)
						normal = scale_vector(normal, -1.0f);
				}
				else if (object->type == 2)
				{
					normal = scale_vector(obj.plane->normal, -1.0f);
					//normal = (t_3f){0.0f, 0.0f, 0.0f};
				}
				else if (object->type == 3)
				{
					vect[0] = normalize_vector(subtract_vectors(*point_hit, axis));
					vect[1] = normalize_vector(subtract_vectors(axis, object->origin));
					dp = (float)fabs(acos(dot_product(vect[0], vect[1])));
					dp = (float)vector_magnitude(subtract_vectors(*point_hit, axis)) / cosf(dp);
					normal = add_vectors(axis, scale_vector(vect[1], dp));
					normal = normalize_vector(subtract_vectors(*point_hit, normal));
					if (t->x == t->y)
						normal = scale_vector(normal, -1.0f);
				}
				else if (object->type == 4)
				{
					dp = dot_product(subtract_vectors(*point_hit, object->origin), normalize_vector(subtract_vectors(object->origin, axis)));
					normal = add_vectors(object->origin, scale_vector(normalize_vector(subtract_vectors(object->origin, axis)), dp));
					normal = normalize_vector(subtract_vectors(*point_hit, normal));
					if (t->x == t->y)
						normal = scale_vector(normal, -1.0f);
				}
				utils->closest_object = object;
			}
		}
		i++;
		objects = objects->next;
	}
	if (xy->x == img->dim.width / 2 && xy->y == img->dim.height / 2)
	{
		printf("************************NEW RENDERING *************************\n");
		printf("T: x[%.2f] y[%.2f]\n", t2.x, t2.y);
		printf("POINT_HIT: %f %f %f\n", point_hit->x, point_hit->y, point_hit->z);
		printf("NORMAL: %f %f %f\n", normal.x, normal.y, normal.z);
		if (utils->closest_object != NULL)
			printf("CLOSEST OBJECT TYPE: %d\n", utils->closest_object->type);
	}
	return (normal);
}

static double	intersect_light(t_utils *utils, t_3f *ray, t_3f *ray_origin)
{
	t_list		*objects;
	t_object	*object;
	t_3f		axis;
	t_2d		t[2];
	int			i;
	int			ret;
	t_obj_ptrs	obj;

	t[1].x = T_MAX;
	t[1].y = T_MAX;
	t[0].x = T_MAX;
	t[0].y = T_MAX;
	i = 1;
	objects = utils->objects;
	while (objects != NULL)
	{
		ret = 0;
		object = (t_object *)objects->content;
		if (object->type == 1)
		{
			obj.sphere = (t_sphere *)object->content;
			ret = intersect_sphere(ray, ray_origin, &object->origin, obj.sphere->radius, &t[1]);
		}
		else if (object->type == 2)
		{
			obj.plane = (t_plane *)object->content;
			ret = intersect_plane(ray, &object->origin, ray_origin , &obj.plane->normal, &t[1].x);
		}
		else if (object->type == 3)
		{
			obj.cone = (t_cone *)object->content;
			axis = add_vectors(object->origin, scale_vector(obj.cone->axis, obj.cone->axis_length));
			ret = intersect_cone(ray_origin, ray, &object->origin, &axis, obj.cone->radius, &t[1]);
		}
		else if (object->type == 4)
		{
			obj.cylinder = (t_cylinder *)object->content;
			axis = add_vectors(object->origin, scale_vector(obj.cylinder->axis, obj.cylinder->axis_length));
			ret = intersect_cylinder(ray_origin, ray, &object->origin, &axis, obj.cylinder->radius, &t[1]);
		}
		if (ret)
		{
			if (t[1].x < t[0].x)
			{
				t[0] = t[1];
			}
		}
		i++;
		objects = objects->next;
	}
	return (t[0].x);
}

void	ray_plotting(t_utils *utils, t_img *img, t_2i coords)
{
	t_list		*objects;
	t_object	*object;
	t_3f		point_hit[2];
	t_2f		scrn;
	t_3f		normal;
	t_3f		ray;
	t_3f		light_color;
	double		light_level;
	t_2d		t;
	double		intersect_t;
	t_3i		temp_rgb;
	t_3i		rgb;
	t_3i		rgb_t;
	t_obj_ptrs	obj;

	rgb_t.x = 0;
	rgb_t.y = 0;
	rgb_t.z = 0;
	scrn.x = (float)(2 * coords.x) / (float)img->dim.width - 1.0f;
	scrn.y = (float)(-2 * coords.y) / (float)img->dim.height + 1.0f;
	ray = get_ray(scrn, &utils->cam, &utils->proj);
	utils->closest_object = NULL;
	normal = intersect(utils, &ray, &utils->cam.origin, img, &(t_2i){coords.x, coords.y}, &point_hit[0], &t);
	if (utils->closest_object == NULL)
	{
		put_pixel(coords.x, coords.y, 0x000000, img);
		return ;
	}
	seperate_rgb(utils->closest_object->color, &rgb.x, &rgb.y, &rgb.z);
	if (utils->render == 1 && utils->closest_object->type != 0)
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
				obj.light->dir = subtract_vectors(object->origin, point_hit[0]);
				t.x = sqrt(((obj.light->dir.x) * (obj.light->dir.x)) + ((obj.light->dir.y) * (obj.light->dir.y)) + ((obj.light->dir.z) * (obj.light->dir.z)));
				obj.light->dir = normalize_vector(obj.light->dir);
				point_hit[1] = add_vectors(point_hit[0], scale_vector(normal, utils->shadow_bias));
				intersect_t = intersect_light(utils, &obj.light->dir, &point_hit[1]);
				if (intersect_t < 0)
					intersect_t = T_MAX;
				if (coords.x == img->dim.width / 2 && coords.y == img->dim.height / 2)
				{
					printf("intersect_t | t: %f %lf\n", intersect_t, t.x);
				}
				if (intersect_t > t.x)
				{
					t.x = t.x / obj.light->lumen;
					/*if (normal.x == 0.0f && normal.y == 0.0f && normal.z == 0.0f)
						 light_level = 1.0f;
					else
						light_level = (double)dot_product(normal, obj.light->dir);
					*/
					light_level = (double)dot_product(normal, obj.light->dir);
					light_level -= t.x;
					if (light_level < 0.0)
						light_level = 0.0;
						//if (object_no[0] == object_no[1] && light_level > 0 && object_no[0] > 0)
					rgb_t.x += (int)(rgb.x * light_level * light_color.x);
					rgb_t.y += (int)(rgb.y * light_level * light_color.y);
					rgb_t.z += (int)(rgb.z * light_level * light_color.z);
					rgb_t.x = ft_min(rgb_t.x, 255);
					rgb_t.y = ft_min(rgb_t.y, 255);
					rgb_t.z = ft_min(rgb_t.z, 255);
					if (coords.x == img->dim.width / 2 && coords.y == img->dim.height / 2)
					{
						printf("********************************\n");
						printf("t / lumen ratio: %lf\n", t.x);
						printf("normal & light similarity: %lf\n", (double)dot_product(normal, obj.light->dir));
						printf("light level %%: %lf\n", light_level);
						printf("********************************\n");
					}
				}
			}
			objects = objects->next;
		}
		put_pixel(coords.x, coords.y, combine_rgb(rgb_t.x, rgb_t.y, rgb_t.z), img);
	}
	else
	{
		if (t.x == t.y)
			put_pixel(coords.x, coords.y, ~utils->closest_object->color & 0x00FFFFFF, img);
		else
			put_pixel(coords.x, coords.y, utils->closest_object->color, img);
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
		(t_2i){0, 0}, (t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}

void	draw_image0(t_utils *utils)
{
	t_2i			coords;
	char			*str;
	static clock_t	interv[2];
	float			plot_time;

	coords.y = 0;
	get_camera_directions(utils, &utils->cam);
	//printf("CAMERA ORIGIN: %f %f %f\n", utils->cam.origin.x, utils->cam.origin.y, utils->cam.origin.z);
	//printf("CAMERA FORWARD: %f %f %f\n", utils->cam.dir.forward.x, utils->cam.dir.forward.y, utils->cam.dir.forward.z);
	if (utils->density.x == 9 && utils->density.y == 9)
		interv[0] = clock();
	while (coords.y <= utils->curr_img->dim.height)
	{
		if (coords.y % 10 == utils->density.y)
		{
			coords.x = 0;
			while (coords.x <= utils->curr_img->dim.width)
			{
				if (coords.x % 10 == utils->density.x)
				{
					ray_plotting(utils, &utils->img[0], coords);
				}
				coords.x += 1;
			}
		}
		coords.y += 1;
	}
	draw_aim_point(utils);
	if (!(utils->density.x == 0 && utils->density.y == 0))
		return ;
	interv[1] = clock();
	plot_time = (float)(interv[1] - interv[0]) / CLOCKS_PER_SEC;
	coords.x = utils->img[0].dim.width / 80;
	coords.y = utils->img[0].dim.height / 50;
	str = ft_ftoa(plot_time, 5);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for render time...", -1);
	render_str("Plot time:", &(t_pxl){utils->font, &put_pixel, utils->curr_img}, &(t_2i){coords.x + 2, coords.y + 2}, 0x000000);
	coords = render_str("Plot time:", &(t_pxl){utils->font, &put_pixel, utils->curr_img}, &(t_2i){coords.x, coords.y}, 0xFFFFFF);
	render_str(str, &(t_pxl){utils->font, &put_pixel, utils->curr_img}, &(t_2i){coords.x + 2, coords.y + 2}, 0x000000);
	render_str(str, &(t_pxl){utils->font, &put_pixel, utils->curr_img}, &(t_2i){coords.x, coords.y}, 0xFFFFFF);
	free(str);
}
