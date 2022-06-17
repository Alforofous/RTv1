/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/13 13:34:33 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	malloc_obj_params(t_obj *obj)
{
	obj->vertices = (t_4f *)malloc(sizeof(t_4f) * (size_t)obj->vert_count);
	if (obj->vertices == NULL)
		return (-1);
	obj->faces = (t_faces *)malloc(sizeof(t_faces) * (size_t)obj->face_count);
	if (obj->faces == NULL)
	{
		free(obj->vertices);
		return (-1);
	}
	obj->normals = (t_3f *)malloc(sizeof(t_3f) * (size_t)obj->normal_count);
	if (obj->normals == NULL)
	{
		free(obj->vertices);
		free(obj->faces);
		return (-1);
	}
	ft_bzero(obj->vertices, sizeof(t_4f) * (size_t)obj->vert_count);
	ft_bzero(obj->faces, sizeof(t_faces) * (size_t)obj->face_count);
	ft_bzero(obj->normals, sizeof(t_3f) * (size_t)obj->normal_count);
	return (1);
}

int	obj_param_err_check(t_obj *obj, int ret)
{
	if (ret == -1)
	{
		free(obj->vertices);
		free(obj->faces);
		obj->vertices = NULL;
		obj->faces = NULL;
		return (-1);
	}
	return (1);
}

static int	count_obj_params(int fd, t_obj *obj)
{
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	ft_bzero(obj, sizeof(t_obj));
	while (ret > 0)
	{	
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			ft_putendl("ERROR: Mallocing failed in GNL...");
			return (-1);
		}
		if (line && line[0] == 'v' && line[1] == ' ')
			obj->vert_count += 1;
		else if (line && line[0] == 'f' && line[1] == ' ')
			obj->face_count += 1;
		else if (line && line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			obj->normal_count += 1;
		free(line);
		line = NULL;
	}
	return (1);
}

static int	create_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Couldn't load the object: ");
		ft_putendl(path);
		perror("ERROR");
	}
	return (fd);
}

void	load_obj(char *path, t_obj *obj)
{
	int	help_fd;
	int	fd;

	fd = create_fd(path);
	if (fd >= 0)
	{
		help_fd = create_fd(path);
		if (help_fd >= 0)
		{
			if (count_obj_params(help_fd, obj) == 1)
				get_obj_params(fd, obj);
			if (obj->vertices == NULL || obj->faces == NULL || obj->normals == NULL)
			{
				ft_putstr("ERROR: Mallocing obj params failed for object: ");
				ft_putendl(path);
			}
			else
			{
				ft_putstr("Succesfully loaded object: ");
				ft_putendl(path);
			}
			close(help_fd);
			close(fd);
		}
	}
}
