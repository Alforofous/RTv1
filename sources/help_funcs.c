/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:39:40 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 12:53:20 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return ((int)c);
	return (0);
}

int	coords_in_area(t_dim dim, int x, int y)
{
	if (x > dim.start.x && x < dim.end.x && y > dim.start.y && y < dim.end.y)
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
