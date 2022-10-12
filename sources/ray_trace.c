/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:27:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/12 16:38:59 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3f	intersect(t_utils *utils, t_ray ray, t_3f *point_hit, t_2f *t)
{
	t_list		*objects;
	t_object	*object;
	t_3f		normal;
	t_3f		axis;
	t_3f		vect;
	t_2f		t2;
	float		dp;
	int			i;
	int			ret;

	t->x = T_MAX;
	t->y = T_MAX;
	t2.x = T_MAX;
	t2.y = T_MAX;
	normal = (t_3f){0.0f, 0.0f, 0.0f};
	i = 1;
	ret = 0;
	objects = utils->objects;
	while (objects != NULL)
	{
		object = (t_object *)objects->content;
		if (object->type == 0 && utils->light_render == 1)
		{
			object->radius = 0.5f;
			ret = intersect_sphere(ray, object, &t2);
		}
		else if (object->type == 1)
			ret = intersect_sphere(ray, object, &t2);
		else if (object->type == 2)
			ret = intersect_plane(ray, object, &t2.x);
		else if (object->type == 3)
			ret = intersect_cone(ray, object, &t2);
		else if (object->type == 4)
			ret = intersect_cylinder(ray, object, &t2);
		if (ret)
		{
			if (t2.x < t->x)
			{
				*point_hit = scale_vector(ray.dir, (float)t2.x);
				*point_hit = add_vectors(*point_hit, ray.origin);
				*t = t2;
				if (object->type == 1 || object->type == 0)
				{
					normal = normalize_vector(subtract_vectors(*point_hit, object->origin));
					if (t->x == t->y)
						normal = scale_vector(normal, -1.0f);
				}
				else if (object->type == 2)
				{
					normal = object->axis;
				}
				else if (object->type == 3)
				{
					axis = add_vectors(object->origin, scale_vector(object->axis, object->axis_length));
					vect = normalize_vector(subtract_vectors(*point_hit, axis));
					dp = (float)fabs(acos(dot_product(vect, object->axis)));
					dp = (float)vector_magnitude(subtract_vectors(*point_hit, axis)) / cosf(dp);
					normal = add_vectors(axis, scale_vector(object->axis, dp));
					normal = normalize_vector(subtract_vectors(*point_hit, normal));
					if (t->x == t->y)
						normal = scale_vector(normal, -1.0f);
				}
				else if (object->type == 4)
				{
					axis = add_vectors(object->origin, scale_vector(object->axis, object->axis_length));
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
	return (normal);
}

static float	intersect_light(t_utils *utils, t_3f *ray, t_3f *ray_origin)
{
	t_list		*objects;
	t_object	*object;
	t_2f		t[2];
	int			i;
	int			ret;

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
			ret = intersect_sphere((t_ray){*ray_origin, *ray}, object, &t[1]);
		}
		else if (object->type == 2)
		{
			ret = intersect_plane((t_ray){*ray_origin, *ray}, object, &t[1].x);
		}
		else if (object->type == 3)
		{
			ret = intersect_cone((t_ray){*ray_origin, *ray}, object, &t[1]);
		}
		else if (object->type == 4)
		{
			ret = intersect_cylinder((t_ray){*ray_origin, *ray}, object, &t[1]);
		}
		if (ret)
		{
			if (t[1].x < t[0].x)
			{
				t[0].x = t[1].x;
				t[0].y = t[1].y;
			}
		}
		i++;
		objects = objects->next;
	}
	return (t[0].x);
}
void	ray_trace(t_utils *utils, t_img *img, t_2i coords)
{
	t_list		*objects;
	t_object	*object;
	t_3f		point_hit[2];
	t_2f		scrn;
	t_3f		normal;
	t_ray		ray;
	t_3f		light_color;
	t_3f		light_dir;
	float		light_level;
	t_2f		t;
	float		intersect_t;
	t_3i		temp_rgb;
	t_3i		rgb;
	t_3i		rgb_t;

	rgb_t.x = 0;
	rgb_t.y = 0;
	rgb_t.z = 0;
	scrn.x = (float)(2 * coords.x) / (float)img->dim.size.x - 1.0f;
	scrn.y = (float)(-2 * coords.y) / (float)img->dim.size.y + 1.0f;
	ray.dir = get_ray(scrn, &utils->cam, &utils->proj);
	ray.origin = utils->cam.origin;
	utils->closest_object = NULL;
	normal = intersect(utils, ray, &point_hit[0], &t);
	if (utils->closest_object == NULL)
	{
		put_pixel(coords, 0x000000, img);
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
				seperate_rgb(object->color, &temp_rgb.x, &temp_rgb.y, &temp_rgb.z);
				light_color.x = (float)temp_rgb.x / 255;
				light_color.y = (float)temp_rgb.y / 255;
				light_color.z = (float)temp_rgb.z / 255;
				light_dir = subtract_vectors(object->origin, point_hit[0]);
				t.x = vector_magnitude(light_dir);
				light_dir = normalize_vector(light_dir);
				point_hit[1] = add_vectors(point_hit[0], scale_vector(normal, utils->shadow_bias));
				intersect_t = intersect_light(utils, &light_dir, &point_hit[1]);
				if (intersect_t < 0)
					intersect_t = T_MAX;
				if (coords.x == img->dim.size.x / 2 && coords.y == img->dim.size.y / 2)
				{
					printf("intersect_t | t: %.50f %f\n", intersect_t, t.x);
					printf("POINT_HIT           : %f %f %f\n", point_hit[0].x, point_hit[0].y, point_hit[0].z);
					printf("POINT_HIT (with bias: %f %f %f\n", point_hit[1].x, point_hit[1].y, point_hit[1].z);
				}
				if (intersect_t > t.x)
				{
					t.x = t.x / object->lumen;
					/*if (normal.x == 0.0f && normal.y == 0.0f && normal.z == 0.0f)
						 light_level = 1.0f;
					else
						light_level = (float)dot_product(normal, light_dir);
					*/
					light_level = (float)dot_product(normal, light_dir);
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
					if (coords.x == img->dim.size.x / 2 && coords.y == img->dim.size.y / 2)
					{
						printf("********************************\n");
						printf("t / lumen ratio: %f\n", t.x);
						printf("normal & light similarity: %f\n", (float)dot_product(normal, light_dir));
						printf("light level %%: %f\n", light_level);
						printf("********************************\n");
					}
				}
			}
			objects = objects->next;
		}
		put_pixel(coords, combine_rgb(rgb_t.x, rgb_t.y, rgb_t.z), img);
	}
	else
	{
		if (t.x == t.y)
			put_pixel(coords, ~utils->closest_object->color & 0x00FFFFFF, img);
		else
			put_pixel(coords, utils->closest_object->color, img);
		/*rgb = (t_3i){127, 127, 127};
		if (normal.x < 0)
			rgb.x *= -normal.x;
		else
			rgb.x *= normal.x * 2.0f;
		if (normal.y < 0)
			rgb.y *= -normal.y;
		else
			rgb.y *= normal.y * 2.0f;
		if (normal.z < 0)
			rgb.z *= -normal.z;
		else
			rgb.z *= normal.z * 2.0f;
		put_pixel(coords, combine_rgb(rgb.x, rgb.y, rgb.z), img);*/
	}
}
