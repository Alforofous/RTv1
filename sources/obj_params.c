/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:49:21 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:16:47 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	get_face_normal(char *line, int *face_normal)
{
	line = ft_strchr(line, '/');
	if (line && *line == '/')
		line++;
	if (line)
		line = ft_strchr(line, '/');
	if (line && *line == '/')
		line++;
	if (line)
		*face_normal = ft_atoi(line);
}

static void	get_obj_faces(t_obj *obj, char *line, int *i)
{
	char	*temp;

	if (line && line[0] == 'f' && line[1] == ' ')
	{
		temp = line;
		temp = find_last_space(temp);
		if (temp)
			obj->faces[*i].a[0] = ft_atoi(temp);
		get_face_normal(temp, &obj->faces[*i].a[1]);
		temp = find_last_space(temp);
		if (temp)
			obj->faces[*i].b[0] = ft_atoi(temp);
		get_face_normal(temp, &obj->faces[*i].b[1]);
		temp = find_last_space(temp);
		if (temp)
			obj->faces[*i].c[0] = ft_atoi(temp);
		get_face_normal(temp, &obj->faces[*i].c[1]);
		(*i)++;
	}
}

static void	get_obj_normals(t_obj *obj, char *line, int *i)
{
	char	*temp;

	if (line && line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
	{
		temp = line;
		temp = find_last_space(temp);
		if (temp)
			obj->normals[*i].x = (double)ft_atof(temp);
		temp = find_last_space(temp);
		if (temp)
			obj->normals[*i].y = (double)ft_atof(temp);
		temp = find_last_space(temp);
		if (temp)
			obj->normals[*i].z = (double)ft_atof(temp);
		(*i)++;
	}
}

static void	get_obj_vertices(t_obj *obj, char *line, int *i)
{
	char	*temp;

	if (line && line[0] == 'v' && line[1] == ' ')
	{
		temp = line;
		temp = find_last_space(temp);
		if (temp)
			obj->vertices[*i].a = (double)ft_atof(temp);
		temp = find_last_space(temp);
		if (temp)
			obj->vertices[*i].b = (double)ft_atof(temp);
		temp = find_last_space(temp);
		if (temp)
			obj->vertices[*i].c = (double)ft_atof(temp);
		temp = find_last_space(temp);
		if (temp)
			obj->vertices[*i].d = (double)ft_atof(temp);
		(*i)++;
	}
}

int	get_obj_params(int fd, t_obj *obj)
{
	int		ret;
	int		i[3];
	char	*line;

	ret = 1;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (malloc_obj_params(obj) == -1)
		return (-1);
	while (ret > 0)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		if (obj_param_err_check(obj, ret) == -1)
			return (-1);
		get_obj_faces(obj, line, &i[0]);
		get_obj_vertices(obj, line, &i[1]);
		get_obj_normals(obj, line, &i[2]);
		if (line)
			free(line);
	}
	return (1);
}
