/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:09 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 14:36:45 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_circle(t_pxl_func *pxl, t_2i coords, int radius, t_uint color)
{
	int	x2;
	int	y2;
	int	l;

	l = (int)(radius * cos(PI / 4));
	x2 = 0;
	while (x2 <= l)
	{
		y2 = (int)sqrt((double)(radius * radius) - (x2 * x2));
		pxl->f(x2 + coords.x, -y2 + coords.y, color, (void *)pxl->param);
		pxl->f(y2 + coords.x, -x2 + coords.y, color, (void *)pxl->param);
		pxl->f(y2 + coords.x, x2 + coords.y, color, (void *)pxl->param);
		pxl->f(x2 + coords.x, y2 + coords.y, color, (void *)pxl->param);
		pxl->f(-x2 + coords.x, y2 + coords.y, color, (void *)pxl->param);
		pxl->f(-y2 + coords.x, x2 + coords.y, color, (void *)pxl->param);
		pxl->f(-y2 + coords.x, -x2 + coords.y, color, (void *)pxl->param);
		pxl->f(-x2 + coords.x, -y2 + coords.y, color, (void *)pxl->param);
		x2++;
	}
}
