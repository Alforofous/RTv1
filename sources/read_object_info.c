/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:23:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 11:18:15 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	origin(char *line, t_object *object)
{
	char	*str;

	str = "origin";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		object->origin.x = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		object->origin.y = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		object->origin.z = (double)ft_atof(line++);
		return (1);
	}
	return (0);
}

static int	radius_or_lumen(char *line, t_object *object)
{
	char	*str;

	str = "radius";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		object->radius = (double)ft_atof(line);
		return (1);
	}
	str = "lumen";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		object->lumen = (double)ft_atof(line);
		object->radius = 0.5f;
		return (1);
	}
	return (0);
}

static int	axis(char *line, t_object *object)
{
	char	*str;

	str = "axis";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		object->axis.x = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		object->axis.y = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		object->axis.z = (double)ft_atof(line++);
		object->axis_length = vector_magnitude(object->axis);
		object->axis = normalize_vector(object->axis);
		return (1);
	}
	return (0);
}

static int	color(char *line, t_object *object)
{
	char	*str;

	str = "color";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		object->color = (t_uint)ft_atoh(line);
		return (1);
	}
	return (0);
}

int	read_object_info(char *line, t_object *object)
{
	if (origin(line, object))
		return (1);
	if (radius_or_lumen(line, object))
		return (1);
	if (axis(line, object))
		return (1);
	if (color(line, object))
		return (1);
	if (transformations(line, object))
		return (1);
	return (0);
}
