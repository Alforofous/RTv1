/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:15:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 17:55:32 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	check_if_camera(char *line)
{
	char	*str;

	str = "OBJECT";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strstr(line, str);
		line += ft_strlen(str);
		str = "camera";
		if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
			return (1);
		return (0);
	}
	return (-1);
}

static int	read_camera(t_cam *camera, char *line)
{
	static int	reading;

	if (line == NULL)
		return (-1);
	if (reading == 0)
	{
		if (check_if_camera(line) == 1)
			reading = 1;
	}
	else if (reading == 1)
	{
		if (check_if_camera(line) >= 0)
		{
			reading = 0;
			return (1);
		}
		read_camera_info(line, camera);
	}
	return (0);
}

static t_cam	read_camera_file(int fd)
{
	t_cam		camera;
	int			ret;
	char		*line;

	ret = 1;
	init_camera(&camera);
	while (ret > 0)
	{	
		line = NULL;
		ret = get_next_line(fd, &line);
		if (ret == -1)
			break ;
		read_camera(&camera, line);
		if (line != NULL)
			free(line);
	}
	return (camera);
}

t_cam	load_camera(char *path, t_cam camera)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (camera);
	camera = read_camera_file(fd);
	if (fd >= 0)
		close(fd);
	return (camera);
}
