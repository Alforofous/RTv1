/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:50:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/23 10:59:30 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light	*light_prop(float lumen)
{
	t_light	*light;
	
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		return (NULL);
	light->lumen = lumen;
	return (light);
}

t_sphere	*sphere_prop(float radius)
{
	t_sphere	*sphere;
	
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->radius = radius;
	return (sphere);
}

t_plane	*plane_prop(t_3f normal)
{
	t_plane	*plane;
	
	plane = (t_plane *)malloc(sizeof(t_plane));
	if (plane == NULL)
		return (NULL);
	plane->normal = normal;
	return (plane);
}

t_cone	*cone_prop(t_3f axis, float radius)
{
	t_cone	*cone;
	
	cone = (t_cone *)malloc(sizeof(t_cone));
	if (cone == NULL)
		return (NULL);
	cone->axis = axis;
	cone->radius = radius;
	return (cone);
}

t_cylinder	*cylinder_prop(t_3f axis, float radius)
{
	t_cylinder	*cylinder;
	
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (NULL);
	cylinder->axis = axis;
	cylinder->radius = radius;
	return (cylinder);
}
