/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:55:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/30 12:41:58 by dmalesev         ###   ########.fr       */
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

t_list	*load_scene(char *path)
{
	t_list		*scene;
	t_object	object;
	static int	reading;
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
	scene = ft_lstnew(&object, sizeof(t_object));
	return (scene);
}
