/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:20 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 10:22:02 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

static void	init_draw_line_vars(int *x_len, int *y_len, int *i, int *check)
{
	*i = 1;
	if (*y_len < 0)
	{
		*i = -1;
		*y_len = -(*y_len);
	}
	*check = (2 * (*y_len) - (*x_len));
}

static void	downhill(t_pxl_func *pxl_func, t_line *line, int col, int d_col)
{
	t_2i	len;
	int		mix_col;
	int		i;
	int		check;
	float	percent;

	len.x = line->x_dest - line->x;
	len.y = line->y_dest - line->y;
	init_draw_line_vars(&len.x, &len.y, &i, &check);
	while (line->x <= line->x_dest)
	{
		percent = (float)(line->x - (line->x_dest - len.x)) / (float)len.x;
		if (len.x)
			mix_col = mix_colors(col, d_col, percent);
		pxl_func->f(line->x, line->y, mix_col, pxl_func->param);
		if (check >= 0)
		{
			line->y = line->y + i;
			check = check + (2 * (len.y - len.x));
		}
		else
			check = check + (2 * len.y);
		line->x++;
	}
}

static void	uphill(t_pxl_func *pxl_func, t_line *line, int col, int d_col)
{
	t_2i	len;
	int		mix_col;
	int		i;
	int		check;
	float	percent;

	len.x = line->x_dest - line->x;
	len.y = line->y_dest - line->y;
	init_draw_line_vars(&len.y, &len.x, &i, &check);
	while (line->y <= line->y_dest)
	{
		percent = (float)(line->y - (line->y_dest - len.y)) / (float)len.y;
		if (len.y)
			mix_col = mix_colors(col, d_col, percent);
		pxl_func->f(line->x, line->y, mix_col, pxl_func->param);
		if (check >= 0)
		{
			line->x = line->x + i;
			check = check + (2 * (len.x - len.y));
		}
		else
			check = check + (2 * len.x);
		line->y++;
	}
}

void	draw_line(t_pxl_func *pxl_func, t_line *line, int col, int d_col)
{
	if (abs(line->y_dest - line->y) < abs(line->x_dest - line->x))
	{
		if (line->x > line->x_dest)
			downhill(pxl_func, &(t_line){line->x_dest, line->y_dest,
				line->x, line->y}, d_col, col);
		else
			downhill(pxl_func, &(t_line){line->x, line->y,
				line->x_dest, line->y_dest}, col, d_col);
	}
	else
	{
		if (line->y > line->y_dest)
			uphill(pxl_func, &(t_line){line->x_dest, line->y_dest,
				line->x, line->y}, d_col, col);
		else
			uphill(pxl_func, &(t_line){line->x, line->y,
				line->x_dest, line->y_dest}, col, d_col);
	}
}
