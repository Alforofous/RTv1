/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:23:10 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 10:05:53 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_square(t_pxl_func *pxl_func, t_line *xy, int color)
{
	int	size_x;
	int	size_y;

	size_x = xy->x - xy->x_dest;
	size_y = xy->y - xy->y_dest;
	draw_line(pxl_func, &(t_line){xy->x, xy->y, xy->x_dest,
		xy->y_dest}, color, color);
	draw_line(pxl_func, &(t_line){xy->x_dest,
		xy->y_dest, xy->x_dest + size_y, xy->y_dest - size_x}, color, color);
	draw_line(pxl_func, &(t_line){xy->x + size_y, xy->y - size_x,
		xy->x_dest + size_y, xy->y_dest - size_x}, color, color);
	draw_line(pxl_func, &(t_line){xy->x, xy->y,
		xy->x + size_y, xy->y - size_x}, color, color);
}
