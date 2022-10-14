/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:21:45 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 11:40:30 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static float	get_light_level(float t, float lumen, t_3f normal, t_3f dir)
{
	float	light_intensity;
	float	difuse;
	float	light_level;

	light_intensity = t / (lumen * lumen);
	difuse = dot_product(normal, dir);
	light_level = difuse - light_intensity;
	light_level = ft_maxf(light_level, 0.0);
	return (light_level);
}

static t_3i	calc_light(t_3i rgb, t_uint light_color, t_3i obj_rgb, float level)
{
	t_3f	light_rgb;

	seperate_rgbf(light_color, &light_rgb.x, &light_rgb.y, &light_rgb.z);
	rgb.x += (int)((float)obj_rgb.x * level * light_rgb.x);
	rgb.y += (int)((float)obj_rgb.y * level * light_rgb.y);
	rgb.z += (int)((float)obj_rgb.z * level * light_rgb.z);
	rgb.x = ft_min(rgb.x, 255);
	rgb.y = ft_min(rgb.y, 255);
	rgb.z = ft_min(rgb.z, 255);
	return (rgb);
}

static t_3f	dir_to_light(t_3f light_origin, t_3f origin, float *t)
{
	t_3f	light_dir;

	light_dir = subtract_vectors(light_origin, origin);
	*t = vector_magnitude(light_dir);
	light_dir = normalize_vector(light_dir);
	return (light_dir);
}

t_uint	light_up(t_list *scene, t_uint obj_color, t_ray to_light, t_3f normal)
{
	t_list		*scene_start;
	t_object	*object;
	t_3i		rgb[2];
	float		t;
	float		level;

	rgb[0] = (t_3i){0, 0, 0};
	seperate_rgb(obj_color, &rgb[1].x, &rgb[1].y, &rgb[1].z);
	scene_start = scene;
	while (scene != NULL)
	{
		object = (t_object *)scene->content;
		if (object->type == 0)
		{
			to_light.dir = dir_to_light(object->origin, to_light.origin, &t);
			if (t < closest_t(scene_start, NULL, to_light, -2).x)
			{
				level = get_light_level(t, object->lumen, normal, to_light.dir);
				rgb[0] = calc_light(rgb[0], object->color, rgb[1], level);
			}
		}
		scene = scene->next;
	}
	return (combine_rgb(rgb[0].x, rgb[0].y, rgb[0].z));
}
