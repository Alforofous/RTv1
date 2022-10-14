/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:23:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 13:58:04 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	rotate(char *line, t_object *object)
{
	char	*str;
	t_3f	angles;

	str = "rotate";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		angles.x = (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		angles.y = (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		angles.z = (float)ft_atof(line++);
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
		line += ft_strlen(str);
		object->origin.x += (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		object->origin.y += (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		object->origin.z += (float)ft_atof(line++);
		return (1);
	}
	return (0);
}

int	transformations(char *line, t_object *object)
{
	if (rotate(line, object))
		return (1);
	if (translate(line, object))
		return (1);
	return (0);
}
