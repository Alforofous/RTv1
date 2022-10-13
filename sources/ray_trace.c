/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:27:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/13 22:45:16 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_intersect_f(int (**f)(t_ray ray, t_object *object, t_2f *t))
{
	f[0] = intersect_sphere;
	f[1] = intersect_sphere;
	f[2] = intersect_plane;
	f[3] = intersect_cone;
	f[4] = intersect_cylinder;
}

static t_2f	closest_t(t_list *scene, t_object **clo_obj, t_ray ray, int mode)
{
	t_object	*object;
	t_2f		t[2];
	int			ret;
	int			(*intersect_f[5])(t_ray ray, t_object *object, t_2f *t);

	init_intersect_f(intersect_f);
	t[0] = (t_2f){T_MAX, T_MAX};
	t[1] = (t_2f){T_MAX, T_MAX};
	ret = 0;
	while (scene != NULL)
	{
		object = (t_object *)scene->content;
		if (!(object->type == 0 && mode < 0))
			ret = (*intersect_f[object->type])(ray, object, &t[1]);
		if (ret && t[1].x < t[0].x)
		{
			t[0] = t[1];
			if (clo_obj)
				*clo_obj = object;
		}
		scene = scene->next;
	}
	return (t[0]);
}

static t_uint	shine_light(t_list *scene, t_3i obj_color, t_ray to_light, t_3f hit_point, t_3f normal)
{
	t_list		*scene_start;
	t_object	*object;
	t_3i		rgb_t;
	t_3f		light_color;
	float		t_light;
	float		light_level;

	rgb_t = (t_3i){0, 0, 0};
	scene_start = scene;
	while (scene != NULL)
	{
		object = (t_object *)scene->content;
		if (object->type == 0)
		{
			to_light.dir = normalize_vector(subtract_vectors(object->origin, hit_point));
			t_light = vector_magnitude(subtract_vectors(to_light.origin, object->origin));
			if (t_light < closest_t(scene_start, NULL, to_light, -2).x)
			{
				t_light = t_light / object->lumen;
				light_level = (float)dot_product(normal, to_light.dir) - t_light;
				light_level = ft_maxf(light_level, 0.0);
				seperate_rgbf(object->color, &light_color.x, &light_color.y, &light_color.z);
				rgb_t.x += (int)((float)obj_color.x * light_level * light_color.x);
				rgb_t.y += (int)((float)obj_color.y * light_level * light_color.y);
				rgb_t.z += (int)((float)obj_color.z * light_level * light_color.z);
				rgb_t.x = ft_min(rgb_t.x, 255);
				rgb_t.y = ft_min(rgb_t.y, 255);
				rgb_t.z = ft_min(rgb_t.z, 255);
			}
		}
		scene = scene->next;
	}
	return (combine_rgb(rgb_t.x, rgb_t.y, rgb_t.z));
}

void	ray_trace(t_utils *utils, t_img *img, t_2i coords)
{
	t_3f		hit_point;
	t_ray		to_light;
	t_3f		normal;
	t_ray		ray;
	t_2f		t[2];
	t_uint		color;
	t_3i		rgb;

	ray = get_ray(coords, img, &utils->cam, &utils->proj);
	utils->closest_object = NULL;
	t[0] = closest_t(utils->scene, &utils->closest_object, ray, utils->rend_lights);
	if (utils->closest_object == NULL)
	{
		put_pixel(coords, 0x000000, img);
		return ;
	}
	hit_point = scale_vector(ray.dir, t[0].x);
	hit_point = add_vectors(hit_point, ray.origin);
	if (coords.x == img->dim.size.x / 2 && coords.y == img->dim.size.y / 2)
	{
		printf("\nNEW RENDER********************\n");
		printf("T: %.50f\n", t[0].x);
	}
	normal = calculate_normal(utils->closest_object, hit_point, t[0]);
	seperate_rgb(utils->closest_object->color, &rgb.x, &rgb.y, &rgb.z);
	if (utils->render == 1 && utils->closest_object->type != 0)
	{
		to_light.origin = add_vectors(hit_point, scale_vector(normal, utils->shadow_bias));
		color = shine_light(utils->scene, rgb, to_light, hit_point, normal);
		put_pixel(coords, color, img);
	}
	else
	{
		if (t[0].x == t[0].y)
			put_pixel(coords, ~utils->closest_object->color & 0x00FFFFFF, img);
		else
			put_pixel(coords, utils->closest_object->color, img);
		hit_point = (t_3f){255, 255, 255};
		if (normal.x < 0)
			hit_point.x *= -normal.x;
		else
			hit_point.y *= normal.x;
		if (normal.y < 0)
			hit_point.y *= -normal.y;
		else
			hit_point.z *= normal.y;
		if (normal.z < 0)
			hit_point.z *= -normal.z;
		else
			hit_point.x *= normal.z;
		put_pixel(coords, combine_rgb((int)hit_point.x, (int)hit_point.y, (int)hit_point.z), img);
	}
}
