/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:55:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/28 12:59:23 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	create_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Couldn't load a scene: ");
		ft_putendl(path);
		perror("ERROR");
	}
	return (fd);
}

static int	get_object_type(char *line)
{
	char	*str;

	str = "OBJECT"
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

static int	read_scene_file(char *path)
{
	int			ret;
	char		*line;

	ret = 1;
	line = NULL;
	while (ret > 0)
	{	
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			ft_putendl("ERROR: Mallocing failed in GNL...");
			return (-1);
		}
		if (reading == 0)
			object->type = get_object_type(line);
		if (object->type >= 0)
		{
			reading = 1;
			read_object_info(line, &object);
		}
		free(line);
		line = NULL;
	}

}

t_list	*malloc_objects(size_t object_count)
{
	t_list		*objects;
	t_object	*object;

	object = (t_object *)malloc(sizeof(t_object));
	if (object == NULL)
		return (NULL);
	objects = ft_lstnew(&object, sizeof(t_object));
	if (objects == NULL)
		return (NULL);
	
}

t_list	*load_scene(char *path)
{
	t_list		*objects;
	t_object	object;
	static int	reading;
	size_t		object_count;

	object_count = ft_strs_in_file(path);
	scene = malloc_objects(object_count);
	if (scene == NULL)
		return (NULL);
	scene = ft_lstnew(&object, sizeof(t_object));
	return (scene);
}
