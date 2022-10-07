/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circlef.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:15:08 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/07 11:38:01 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_circlef(t_pxl_func *pxl, t_2i coords, int radius, t_uint color)
{
	double	i;
	int		pixel[2];

	while (radius >= 0)
	{
		i = 0;
		while (i <= PI * 2)
		{
			pixel[0] = coords.x + (int)((double)radius * cos(i));
			pixel[1] = coords.y + (int)((double)radius * sin(i));
			pxl->f((t_2i){pixel[0], pixel[1]}, color, (void *)pxl->param);
			i += 0.01;
		}
		radius -= 1;
	}
}
