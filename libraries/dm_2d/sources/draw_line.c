/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:20 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 14:58:41 by dmalesev         ###   ########.fr       */
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

static void	downhill(t_pxl_func *pf, t_line *line, t_uint col, t_uint d_col)
{
	t_2i	len;
	t_uint	mix_col;
	int		i;
	int		check;
	float	percent;

	len.x = line->end.x - line->start.x;
	len.y = line->end.y - line->start.y;
	init_draw_line_vars(&len.x, &len.y, &i, &check);
	while (line->start.x <= line->end.x)
	{
		percent = (float)(line->start.x - (line->end.x - len.x)) / (float)len.x;
		if (len.x)
			mix_col = transition_colors(col, d_col, percent);
		pf->f(line->start.x, line->start.y, mix_col, pf->param);
		if (check >= 0)
		{
			line->start.y = line->start.y + i;
			check = check + (2 * (len.y - len.x));
		}
		else
			check = check + (2 * len.y);
		line->start.x++;
	}
}

static void	uphill(t_pxl_func *pf, t_line *line, t_uint col, t_uint d_col)
{
	t_2i	len;
	t_uint	mix_col;
	int		i;
	int		check;
	float	percent;

	len.x = line->end.x - line->start.x;
	len.y = line->end.y - line->start.y;
	init_draw_line_vars(&len.y, &len.x, &i, &check);
	while (line->start.y <= line->end.y)
	{
		percent = (float)(line->start.y - (line->end.y - len.y)) / (float)len.y;
		if (len.y)
			mix_col = transition_colors(col, d_col, percent);
		pf->f(line->start.x, line->start.y, mix_col, pf->param);
		if (check >= 0)
		{
			line->start.x = line->start.x + i;
			check = check + (2 * (len.x - len.y));
		}
		else
			check = check + (2 * len.x);
		line->start.y++;
	}
}

void	draw_line(t_pxl_func *pf, t_line line, t_uint col, t_uint d_col)
{
	if (abs(line.end.y - line.start.y) < abs(line.end.x - line.start.x))
	{
		if (line.start.x > line.end.x)
			downhill(pf, &(t_line){line.end, line.start}, d_col, col);
		else
			downhill(pf, &(t_line){line.start, line.end}, col, d_col);
	}
	else
	{
		if (line.start.y > line.end.y)
			uphill(pf, &(t_line){line.end, line.start}, d_col, col);
		else
			uphill(pf, &(t_line){line.start, line.end}, col, d_col);
	}
}
