/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:39:40 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/24 12:43:01 by dmalesev         ###   ########.fr       */
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
			matrix->m[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	print_node(t_list *node)
{
	t_object	*object;

	object = (t_object *)node->content;
	if (object->type == 1)
		ft_putstr("Type: Sphere");
	if (object->type == 2)
		ft_putstr("Type: Plane");
	ft_putstr("\tOrigin: [");
	ft_putnbr((int)object->origin.x);
	ft_putchar(' ');
	ft_putnbr((int)object->origin.y);
	ft_putchar(' ');
	ft_putnbr((int)object->origin.z);
	ft_putstr("]");
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return ((int)c);
	return (0);
}

int	coords_in_img(t_dim *dim, int x, int y)
{
	if (x > dim->x0 && x < dim->x1 && y > dim->y0 && y < dim->y1)
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
