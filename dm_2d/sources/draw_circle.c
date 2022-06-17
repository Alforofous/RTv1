/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:09 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 09:56:03 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_circle(t_pxl_func *pxl_func, t_2i *xy, int radius, int color)
{
	int	x2;
	int	y2;
	int	l;

	l = (int)(radius * cos(PI / 4));
	x2 = 0;
	while (x2 <= l)
	{
		y2 = (int)sqrt((double)(radius * radius) - (x2 * x2));
		pxl_func->f(x2 + xy->x, -y2 + xy->y, color, (void *)pxl_func->param);
		pxl_func->f(y2 + xy->x, -x2 + xy->y, color, (void *)pxl_func->param);
		pxl_func->f(y2 + xy->x, x2 + xy->y, color, (void *)pxl_func->param);
		pxl_func->f(x2 + xy->x, y2 + xy->y, color, (void *)pxl_func->param);
		pxl_func->f(-x2 + xy->x, y2 + xy->y, color, (void *)pxl_func->param);
		pxl_func->f(-y2 + xy->x, x2 + xy->y, color, (void *)pxl_func->param);
		pxl_func->f(-y2 + xy->x, -x2 + xy->y, color, (void *)pxl_func->param);
		pxl_func->f(-x2 + xy->x, -y2 + xy->y, color, (void *)pxl_func->param);
		x2++;
	}
}
