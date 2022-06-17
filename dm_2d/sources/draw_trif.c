/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_trif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:23:32 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 10:06:00 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

static void	swap_vertices(int *x0, int *y0, int *x1, int *y1)
{
	int	temp;

	temp = *x0;
	*x0 = *x1;
	*x1 = temp;
	temp = *y0;
	*y0 = *y1;
	*y1 = temp;
}

static void	sort_vertices(t_tri *tri)
{
	if (tri->y2 < tri->y1)
		swap_vertices(&tri->x1, &tri->y1, &tri->x2, &tri->y2);
	if (tri->y3 < tri->y2)
		swap_vertices(&tri->x2, &tri->y2, &tri->x3, &tri->y3);
	if (tri->y2 < tri->y1)
		swap_vertices(&tri->x1, &tri->y1, &tri->x2, &tri->y2);
}

static void	fill_bottom_triangle(t_pxl_func *pxl_func, t_tri *tri, int color)
{
	float	invslope1;
	float	invslope2;
	float	curx1;
	float	curx2;
	int		scanline_y;

	invslope1 = (float)(tri->x2 - tri->x1) / (float)(tri->y2 - tri->y1);
	invslope2 = (float)(tri->x3 - tri->x1) / (float)(tri->y3 - tri->y1);
	curx1 = (float)tri->x1;
	curx2 = (float)tri->x1;
	scanline_y = tri->y1;
	while (scanline_y <= tri->y2)
	{
		draw_line(pxl_func, &(t_line){(int)curx1, scanline_y,
			(int)curx2, scanline_y}, color, color);
		curx1 += invslope1;
		curx2 += invslope2;
		scanline_y++;
	}
}

static void	fill_top_triangle(t_pxl_func *pxl_func, t_tri *tri, int color)
{
	float	invslope1;
	float	invslope2;
	float	curx1;
	float	curx2;
	int		scanline_y;

	invslope1 = (float)(tri->x3 - tri->x1) / (float)(tri->y3 - tri->y1);
	invslope2 = (float)(tri->x3 - tri->x2) / (float)(tri->y3 - tri->y2);
	curx1 = (float)tri->x3;
	curx2 = (float)tri->x3;
	scanline_y = tri->y3;
	while (scanline_y > tri->y1)
	{
		draw_line(pxl_func, &(t_line){(int)curx1, scanline_y,
			(int)curx2, scanline_y}, color, color);
		curx1 -= invslope1;
		curx2 -= invslope2;
		scanline_y--;
	}
}

void	draw_trif(t_pxl_func *pxl_func, t_tri *tri, int color)
{
	t_2i	v4;

	sort_vertices(tri);
	if (tri->y2 == tri->y3)
		fill_bottom_triangle(pxl_func, tri, color);
	else if (tri->y1 == tri->y2)
		fill_top_triangle(pxl_func, tri, color);
	else
	{
		v4 = (t_2i){(int)((float)tri->x1 + ((float)(tri->y2 - tri->y1)
					/ (float)(tri->y3 - tri->y1))
				* (float)(tri->x3 - tri->x1)), tri->y2};
		fill_bottom_triangle(pxl_func, &(t_tri){tri->x1, tri->y1, tri->x2,
			tri->y2, v4.x, v4.y}, color);
		fill_top_triangle(pxl_func, &(t_tri){tri->x2, tri->y2, v4.x, v4.y,
			tri->x3, tri->y3}, color);
	}
}
