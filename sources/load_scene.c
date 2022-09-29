/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:55:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/29 13:48:20 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	get_object_type(char *line)
{
	char	*str;

	str = "OBJECT";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line += ft_strlen(str) + 1;
		if (ft_strequ("light", line))
			return (0);
		else if (ft_strequ("sphere", line))
			return (1);
		else if (ft_strequ("plane", line))
			return (2);
		else if (ft_strequ("cone", line))
			return (3);
		else if (ft_strequ("cylinder", line))
			return (4);
	}
	return (-1);
}

static int	read_object(t_object *object, char *line)
{
	static int	reading;

	if (reading == 0)
	{
		object->type = get_object_type(line);
		if (object->type >= 0)
			reading = 1;
	}
	else
	{
		if (get_object_type(line) >= 0)
		{
			reading = 0;
			return (1);
		}
		read_object_info(line, object);
	}
	return (0);
}

static t_list	*read_scene_file(char *path)
{
	t_object	object;
	t_list		*scene;
	int			ret;
	char		*line;
	int			fd;

	fd = open(path, O_RDONLY);
	ret = 1;
	scene = NULL;
	line = NULL;
	ft_bzero(&object, sizeof(t_object));
	object.type = -1;
	while (fd >= 0 && ret > 0)
	{	
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			ft_putendl("ERROR: GNL failed while reading scene...");
			return (NULL);
		}
		if (line && read_object(&object, line) == 1)
		{
			scene = add_object(scene, &object);
			if (scene == NULL)
			{
				if (line != NULL)
					free(line);
				return (NULL);
			}
			read_object(&object, line);
		}
		if (line != NULL)
			free(line);
		line = NULL;
	}
	if (fd >= 0)
	{
		if (object.type >= 0)
			scene = add_object(scene, &object);
		close(fd);
	}
	return (scene);
}

t_list	*load_scene(char *path)
{
	t_list		*scene;

	scene = read_scene_file(path);
	return (scene);
}
