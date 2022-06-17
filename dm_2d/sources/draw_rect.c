/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:44 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 10:05:33 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_rect(t_pxl_func *pxl_func, t_2i *xy, t_2i *dimen, int color)
{
	draw_line(pxl_func, &(t_line){xy->x, xy->y, xy->x + dimen->x,
		xy->y}, color, color);
	draw_line(pxl_func, &(t_line){xy->x + dimen->x, xy->y, xy->x + dimen->x,
		xy->y + dimen->y}, color, color);
	draw_line(pxl_func, &(t_line){xy->x + dimen->x, xy->y + dimen->y, xy->x,
		xy->y + dimen->y}, color, color);
	draw_line(pxl_func, &(t_line){xy->x, xy->y + dimen->y, xy->x,
		xy->y}, color, color);
}
