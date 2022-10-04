/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:23:10 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 15:07:43 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_square(t_pxl_func *pxl_func, t_line line, t_uint color)
{
	t_2i	size;
	t_line	square_line;

	size.x = line.start.x - line.end.x;
	size.y = line.start.y - line.end.y;
	draw_line(pxl_func, line, color, color);
	square_line.start = line.end;
	square_line.end = (t_2i){line.end.x + size.y, line.end.y - size.x};
	draw_line(pxl_func, square_line, color, color);
	square_line.start = (t_2i){line.start.x + size.y, line.start.y - size.x};
	square_line.end = (t_2i){line.end.x + size.y, line.end.y - size.x};
	draw_line(pxl_func, square_line, color, color);
	square_line.start = line.start;
	square_line.end = (t_2i){line.start.x + size.y, line.start.y - size.x};
	draw_line(pxl_func, square_line, color, color);
}
