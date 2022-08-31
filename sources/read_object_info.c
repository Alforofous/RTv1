/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:23:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/30 12:41:58 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	origin(char *line, t_object *object)
{
	char	*str;

	str = "\torigin"
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line += ft_strlen(str);
		object->origin.x = ft_atof(line);
		line = ft_strchr(line, ' ');
		object->origin.y = ft_atof(line);
		line = ft_strchr(line, ' ');
		object->origin.z = ft_atof(line);
		return (1);
	}
	return (0);
}


static int	radius(char *line, t_object *object)
{
	char	*str;

	str = "\tradius"
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line += ft_strlen(str);
		object->radius = ft_atof(line);
		return (1);
	}
	return (0);
}

static int	normal(char *line, t_object *object)
{
	char	*str;

	str = "\tnormal"
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line += ft_strlen(str);
		object->normal = ft_atof(line);
		return (1);
	}
	return (0);
}

static int	color(char *line, t_object *object)
{
	char	*str;
	t_3i	color;

	str = "\tcolor"
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line += ft_strlen(str);
		object->color = ft_atoh(line);
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
	if (normal(line, object))
		return (1);
	if (color(line, object))
		return (1);
	return (0);
}
