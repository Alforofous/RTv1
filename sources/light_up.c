/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:21:45 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/16 15:41:13 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_light_level(double t, double lumen, t_3d normal, t_3d dir)
{
	double	light_intensity;
	double	difuse;
	double	light_level;

	light_intensity = t / (lumen * lumen);
	difuse = dot_product(normal, dir);
	light_level = difuse - light_intensity;
	if (light_level < 0.0)
		light_level = 0;
	return (light_level);
}

static t_3i	calc_light(t_3i rgb, t_uint light_color, t_3i obj_rgb, double level)
{
	t_3f	light_rgb;

	seperate_rgbf(light_color, &light_rgb.x, &light_rgb.y, &light_rgb.z);
	rgb.x += (int)((double)obj_rgb.x * level * (double)light_rgb.x);
	rgb.y += (int)((double)obj_rgb.y * level * (double)light_rgb.y);
	rgb.z += (int)((double)obj_rgb.z * level * (double)light_rgb.z);
	rgb.x = ft_min(rgb.x, 255);
	rgb.y = ft_min(rgb.y, 255);
	rgb.z = ft_min(rgb.z, 255);
	return (rgb);
}

static t_3d	dir_to_light(t_3d light_origin, t_3d origin, double *t)
{
	t_3d	light_dir;

	light_dir = subtract_vectors(light_origin, origin);
	*t = vector_magnitude(light_dir);
	light_dir = normalize_vector(light_dir);
	return (light_dir);
}

t_uint	light_up(t_list *scene, t_uint obj_color, t_ray to_light, t_3d normal)
{
	t_list		*scene_start;
	t_object	*object;
	t_3i		rgb[2];
	double		t;
	double		level;

	rgb[0] = (t_3i){0, 0, 0};
	seperate_rgb(obj_color, &rgb[1].x, &rgb[1].y, &rgb[1].z);
	scene_start = scene;
	while (scene != NULL)
	{
		object = (t_object *)scene->content;
		if (object->type == 0)
		{
			to_light.dir = dir_to_light(object->origin, to_light.origin, &t);
			if (t <= closest_t(scene_start, NULL, to_light, -2).x)
			{
				level = get_light_level(t, object->lumen, normal, to_light.dir);
				rgb[0] = calc_light(rgb[0], object->color, rgb[1], level);
			}
		}
		scene = scene->next;
	}
	return (combine_rgb(rgb[0].x, rgb[0].y, rgb[0].z));
}
