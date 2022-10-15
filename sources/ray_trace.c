/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:27:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 09:56:32 by dmalesev         ###   ########.fr       */
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

t_2f	closest_t(t_list *scene, t_object **clo_obj, t_ray ray, int mode)
{
	t_object	*object;
	t_2f		t[2];
	int			ret;
	int			(*intersect_f[5])(t_ray ray, t_object *object, t_2f *t);

	if (clo_obj)
		*clo_obj = NULL;
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

static t_uint	render_no_lights(t_uint color, t_2f t)
{
	if (t.x == t.y)
		return (~color & 0x00FFFFFF);
	else
		return (color);
}

static t_uint	render_with_normals(t_3f normal)
{
	t_3f	rgb;

	rgb = (t_3f){255, 255, 255};
	if (normal.x < 0)
		rgb.x *= -normal.x;
	else
		rgb.x *= normal.x;
	if (normal.y < 0)
		rgb.y *= -normal.y;
	else
		rgb.y *= normal.y;
	if (normal.z < 0)
		rgb.z *= -normal.z;
	else
		rgb.z *= normal.z;
	return (combine_rgb((int)rgb.x, (int)rgb.y, (int)rgb.z));
}

t_uint	ray_trace(t_utils *utils, t_object **clo_obj, t_list *scene, t_ray ray)
{
	t_ray		to_light;
	t_3f		normal;
	t_3f		hit_point;
	t_2f		t[2];

	t[0] = closest_t(scene, clo_obj, ray, utils->rend_lights);
	if (*clo_obj == NULL)
		return (0x000000);
	hit_point = scale_vector(ray.dir, t[0].x);
	hit_point = add_vectors(hit_point, ray.origin);
	normal = calculate_normal(*clo_obj, hit_point, t[0]);
	if (utils->render == 2 && (*clo_obj)->type != 0)
	{
		to_light.origin = scale_vector(normal, utils->shadow_bias);
		to_light.origin = add_vectors(hit_point, to_light.origin);
		return (light_up(scene, (*clo_obj)->color, to_light, normal));
	}
	else if (utils->render == 0)
		return (render_with_normals(normal));
	else if (utils->render == 1 || (*clo_obj)->type == 0)
		return (render_no_lights((*clo_obj)->color, t[0]));
	return (0x00FF00);
}
