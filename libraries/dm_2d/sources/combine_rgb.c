/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:00:02 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/05 09:47:34 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

t_u_int	combine_rgb(int red, int green, int blue)
{
	t_u_int	color;

	color = 0;
	color += (t_u_int)(red << 16);
	color += (t_u_int)(green << 8);
	color += (t_u_int)(blue);
	return (color);
}
