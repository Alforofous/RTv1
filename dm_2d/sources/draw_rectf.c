/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:58 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 10:05:46 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_rectf(t_pxl_func *pxl_func, t_2i *xy, t_2i *dimen, int color)
{
	int	dest;

	dest = xy->y + dimen->y;
	while (xy->y <= dest)
	{
		draw_line(pxl_func, &(t_line){xy->x, xy->y, xy->x + dimen->x,
			xy->y}, color, color);
		xy->y += 1;
	}
}
