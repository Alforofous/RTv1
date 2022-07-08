/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:00:02 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/08 10:12:01 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

t_uint	combine_rgb(int red, int green, int blue)
{
	t_uint	color;

	color = 0;
	color += (t_uint)(red << 16);
	color += (t_uint)(green << 8);
	color += (t_uint)(blue);
	return (color);
}
