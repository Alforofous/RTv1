/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:39:40 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/27 11:21:11 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_matrix(t_mat *matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			((*matrix).m)[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	print_obj_params(t_obj *obj)
{
	int	i;

	i = 0;
	printf("VERTICES COUNT: %d\n\n", obj->vert_count);
	while (obj->vert_count > i)
	{
		printf("%f %f %f [%d]\n",
			obj->vertices[i].a, obj->vertices[i].b, obj->vertices[i].c, i);
		i++;
	}
	i = 0;
	printf("NORMAL COUNT: %d\n\n", obj->normal_count);
	while (obj->normal_count > i)
	{
		printf("%f %f %f [%d]\n",
			obj->normals[i].x, obj->normals[i].y, obj->normals[i].z, i);
		i++;
	}
	i = 0;
	printf("FACE COUNT: %d\n\n", obj->face_count);
	while (obj->face_count > i)
	{
		printf("%d/%d %d/%d %d/%d [%d]\n",
			obj->faces[i].a[0], obj->faces[i].a[1], obj->faces[i].b[0], obj->faces[i].b[1], obj->faces[i].c[0], obj->faces[i].c[1], i);
		i++;
	}
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return ((int)c);
	return (0);
}

int	coords_in_img(t_img *img, int x, int y)
{
	if (x > img->dim.x0 && x < img->dim.x1
		&& y > img->dim.y0 && y < img->dim.y1)
		return (1);
	else
		return (0);
}

int	int_to_bit(int nbr)
{
	return (1 << (nbr - 1));
}

char	*find_last_space(char *str)
{
	if (str)
	{
		str = ft_strchr(str, ' ');
		while (str && *str && is_whitespace(*str))
			str++;
	}
	return (str);
}
