/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:55:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 14:58:20 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	check_if_object(char *line)
{
	char	*str[5];

	str[0] = "OBJECT";
	if (ft_strnequ(ft_strstr(line, str[0]), str[0], ft_strlen(str[0])))
	{
		line = ft_strstr(line, str[0]);
		line += ft_strlen(str[0]);
		str[0] = "light";
		str[1] = "sphere";
		str[2] = "plane";
		str[3] = "cone";
		str[4] = "cylinder";
		if (ft_strnequ(ft_strstr(line, str[0]), str[0], ft_strlen(str[0])))
			return (0);
		else if (ft_strnequ(ft_strstr(line, str[1]), str[1], ft_strlen(str[1])))
			return (1);
		else if (ft_strnequ(ft_strstr(line, str[2]), str[2], ft_strlen(str[2])))
			return (2);
		else if (ft_strnequ(ft_strstr(line, str[3]), str[3], ft_strlen(str[3])))
			return (3);
		else if (ft_strnequ(ft_strstr(line, str[4]), str[4], ft_strlen(str[4])))
			return (4);
	}
	return (-1);
}

static int	read_object(t_object *object, char *line)
{
	static int	reading;

	if (line == NULL)
		return (-1);
	if (reading == 0)
	{
		object->type = -1;
		object->type = check_if_object(line);
		if (object->type >= 0)
			reading = 1;
	}
	else if (reading == 1)
	{
		if (check_if_object(line) >= 0)
		{
			reading = 0;
			return (1);
		}
		read_object_info(line, object);
	}
	return (0);
}

static t_list	*read_scene_file(int fd)
{
	t_object	object;
	t_list		*scene;
	int			ret;
	char		*line;

	ret = 1;
	scene = NULL;
	ft_bzero(&object, sizeof(t_object));
	while (ret > 0)
	{	
		line = NULL;
		ret = get_next_line(fd, &line);
		if (ret == -1)
			break ;
		if (read_object(&object, line) == 1 || (ret == 0 && object.type > 0))
		{
			if (add_object(&scene, &object) == -1)
				ft_putendl("ERROR: Failed to add object to scene...");
			read_object(&object, line);
		}
		if (line != NULL)
			free(line);
	}
	return (scene);
}

t_list	*load_scene(char *path)
{
	t_list	*scene;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	scene = read_scene_file(fd);
	if (fd >= 0)
		close(fd);
	return (scene);
}
