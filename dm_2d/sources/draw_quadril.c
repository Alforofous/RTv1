/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_quadril.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:32 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 10:06:02 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_quadrilateral(t_pxl_func *pxl_func, t_quadril *xy, int color)
{
	draw_line(pxl_func, &(t_line){xy->a, xy->b, xy->c, xy->d}, color, color);
	draw_line(pxl_func, &(t_line){xy->c, xy->d, xy->e, xy->f}, color, color);
	draw_line(pxl_func, &(t_line){xy->e, xy->f, xy->g, xy->h}, color, color);
	draw_line(pxl_func, &(t_line){xy->g, xy->h, xy->a, xy->b}, color, color);
}
