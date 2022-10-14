/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:20:11 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 15:23:40 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	origin(char *line, t_cam *camera)
{
	char	*str;

	str = "origin";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		camera->origin.x = (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		camera->origin.y = (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		camera->origin.z = (float)ft_atof(line++);
		return (1);
	}
	return (0);
}

static int	direction(char *line, t_cam *camera)
{
	char	*str;

	str = "direction";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		camera->dir.forward.x = (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		camera->dir.forward.y = (float)ft_atof(line++);
		line = ft_strchr(line, ' ');
		camera->dir.forward.z = (float)ft_atof(line++);
		camera->dir.forward = normalize_vector(camera->dir.forward);
		return (1);
	}
	return (0);
}

int	read_camera_info(char *line, t_cam *camera)
{
	if (origin(line, camera))
		return (1);
	if (direction(line, camera))
		return (1);
	return (0);
}
