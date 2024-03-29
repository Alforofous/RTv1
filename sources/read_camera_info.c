/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:20:11 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:16:48 by dmalesev         ###   ########.fr       */
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
		camera->origin.x = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		camera->origin.y = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		camera->origin.z = (double)ft_atof(line++);
		return (1);
	}
	return (0);
}

static int	rotation(char *line, t_cam *camera)
{
	char	*str;

	str = "rotation";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		camera->rot.x = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		camera->rot.y = (double)ft_atof(line++);
		line = ft_strchr(line, ' ');
		camera->rot.z = (double)ft_atof(line++);
		return (1);
	}
	return (0);
}

int	read_camera_info(char *line, t_cam *camera)
{
	if (origin(line, camera))
		return (1);
	if (rotation(line, camera))
		return (1);
	return (0);
}
