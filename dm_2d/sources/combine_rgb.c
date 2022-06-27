/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:00:02 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/27 12:30:11 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

t_u_int	combine_rgb(int red, int green, int blue)
{
	t_u_int	color;

	color = 0;
	color += red << 16;
	color += green << 8;
	color += blue;
	return (color);
}
