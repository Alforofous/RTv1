/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:23:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/16 13:55:27 by dmalesev         ###   ########.fr       */
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
		line = ft_strchr(line, ' ');
		if (line)
		{
			object->origin.x = (double)ft_atof(line++);
			line = ft_strchr(line, ' ');
		}
		if (line)
		{
			object->origin.y = (double)ft_atof(line++);
			line = ft_strchr(line, ' ');
		}
		if (line)
			object->origin.z = (double)ft_atof(line++);
		return (1);
	}
	return (0);
}

static int	lumen(char *line, t_object *object)
{
	char	*str;

	str = "lumen";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line = ft_strchr(line, ' ');
		if (line)
			object->lumen = (double)ft_atof(line);
		if (object->lumen < 0)
			object->lumen = 0;
		if (object->type == 0)
			object->radius = 0.5f;
		return (1);
	}
	return (0);
}

static int	radius(char *line, t_object *object)
{
	char	*str;

	str = "radius";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line = ft_strchr(line, ' ');
		if (line)
			object->radius = (double)ft_atof(line);
		if (object->radius < 0)
			object->radius = 0;
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
		line = ft_strchr(line, ' ');
		if (line)
			object->color = (t_uint)ft_atoh(line);
		return (1);
	}
	return (0);
}

int	read_object_info(char *line, t_object *object)
{
	if (origin(line, object))
		return (1);
	if (radius(line, object))
		return (1);
	if (lumen(line, object))
		return (1);
	if (color(line, object))
		return (1);
	if (transformations(line, object))
		return (1);
	return (0);
}
