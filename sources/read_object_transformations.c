/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_transformations.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:23:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 15:39:51 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	axis(char *line, t_object *object)
{
	char	*str;

	str = "axis";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line = ft_strchr(line, ' ');
		if (line)
			object->axis.x = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		if (line)
			object->axis.y = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		if (line)
			object->axis.z = (double)ft_atof(line++);
		if (object->axis.x == 0 && object->axis.y == 0 && object->axis.z == 0)
			object->axis = (t_3d){0.0f, 1.0f, 0.0f};
		object->axis_length = vector_magnitude(object->axis);
		object->axis = normalize_vector(object->axis);
		return (1);
	}
	return (0);
}

static int	rotate(char *line, t_object *object)
{
	char	*str;
	t_3d	angles;

	str = "rotate";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line = ft_strchr(line, ' ');
		if (line)
			angles.x = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		if (line)
			angles.y = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		if (line)
			angles.z = (double)ft_atof(line++);
		object->axis = rotate_point(object->axis, angles);
		return (1);
	}
	return (0);
}

static int	translate(char *line, t_object *object)
{
	char	*str;

	str = "translate";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line = ft_strchr(line, ' ');
		if (line)
			object->origin.x += (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		if (line)
			object->origin.y += (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		if (line)
			object->origin.z += (double)ft_atof(line++);
		return (1);
	}
	return (0);
}

int	transformations(char *line, t_object *object)
{
	if (axis(line, object))
		return (1);
	if (rotate(line, object))
		return (1);
	if (translate(line, object))
		return (1);
	return (0);
}
