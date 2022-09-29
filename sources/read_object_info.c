/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:23:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/29 13:17:51 by dmalesev         ###   ########.fr       */
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
		object->origin.x = (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		object->origin.y = (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		object->origin.z = (float)ft_atof(line++);
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
		object->radius = (float)ft_atof(line);
		return (1);
	}
	str = "lumen";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		object->lumen = (float)ft_atof(line);
		return (1);
	}
	return (0);
}

static int	normal(char *line, t_object *object)
{
	char	*str;

	str = "normal";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)) == 0)
		return (0);
	str = "axis";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)) == 0)
		return (0);
	line = ft_strstr(line, str);
	line += ft_strlen(str);
	object->axis.x = (float)ft_atof(line);
	line = ft_strchr(line, ' ');
	object->axis.y = (float)ft_atof(line);
	line = ft_strchr(line, ' ');
	object->axis.z = (float)ft_atof(line);
	return (1);
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
		printf("Color: %X\n", object->color);
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
	if (normal(line, object))
		return (1);
	if (color(line, object))
		return (1);
	return (0);
}
