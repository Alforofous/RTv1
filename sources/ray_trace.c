/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:27:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/13 17:17:56 by dmalesev         ###   ########.fr       */
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
			*clo_obj = object;
		}
		scene = scene->next;
	}
	return (t[0]);
}

t_ray	get_light_ray(t_3f lorigin, t_3f normal, t_3f hit_point, float bias)
{
	t_ray	light;

	light.dir = normalize_vector(subtract_vectors(lorigin, hit_point));
	light.origin = add_vectors(hit_point, scale_vector(normal, bias));
	return (light);
}

void	ray_trace(t_utils *utils, t_img *img, t_2i coords)
{
	t_list		*scene;
	t_object	*object;
	t_3f		hit_point;
	t_3f		normal;
	t_3f		light_color;
	t_ray		ray;
	t_ray		light;
	float		light_level;
	t_2f		t[2];
	t_3i		rgb;
	t_3i		rgb_t;

	rgb_t = (t_3i){0, 0, 0};
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
		printf("hit_point           : %f %f %f\n", hit_point.x, hit_point.y, hit_point.z);
		printf("T: %.50f\n", t[0].x);
	}
	normal = calculate_normal(utils->closest_object, hit_point, t[0]);
	seperate_rgb(utils->closest_object->color, &rgb.x, &rgb.y, &rgb.z);
	if (utils->render == 1 && utils->closest_object->type != 0)
	{
		scene = utils->scene;
		while (scene != NULL)
		{
			object = (t_object *)scene->content;
			if (object->type == 0)
			{
				light = get_light_ray(object->origin, normal, hit_point, utils->shadow_bias);
				t[1] = closest_t(utils->scene, &utils->closest_object, light, -2);
				if (vector_magnitude(subtract_vectors(light.origin, object->origin)) > t[1].x)
				{
					t[1].x = t[1].x / object->lumen;
					light_level = (float)dot_product(normal, light.dir) - t[1].x;
					light_level = ft_maxf(light_level, 0.0);
					seperate_rgbf(object->color, &light_color.x, &light_color.y, &light_color.z);
					rgb_t.x += (int)(rgb.x * light_level * light_color.x);
					rgb_t.y += (int)(rgb.y * light_level * light_color.y);
					rgb_t.z += (int)(rgb.z * light_level * light_color.z);
					rgb_t.x = ft_min(rgb_t.x, 255);
					rgb_t.y = ft_min(rgb_t.y, 255);
					rgb_t.z = ft_min(rgb_t.z, 255);
				}
			}
			scene = scene->next;
		}
		put_pixel(coords, combine_rgb(rgb_t.x, rgb_t.y, rgb_t.z), img);
	}
	else
	{
		if (t[0].x == t[0].y)
			put_pixel(coords, ~utils->closest_object->color & 0x00FFFFFF, img);
		else
			put_pixel(coords, utils->closest_object->color, img);
		rgb = (t_3i){255, 255, 255};
		if (normal.x < 0)
			rgb.x *= -normal.x;
		else
			rgb.y *= normal.x;
		if (normal.y < 0)
			rgb.y *= -normal.y;
		else
			rgb.z *= normal.y;
		if (normal.z < 0)
			rgb.z *= -normal.z;
		else
			rgb.x *= normal.z;
		put_pixel(coords, combine_rgb(rgb.x, rgb.y, rgb.z), img);
	}
}
