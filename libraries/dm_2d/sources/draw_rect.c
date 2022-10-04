/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:44 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 15:14:37 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_rect(t_pxl_func *pxl, t_2i coords, t_2i dimen, t_uint color)
{
	t_2i	end;

	end = (t_2i){coords.x + dimen.x, coords.y + dimen.y};
	draw_line(pxl, (t_line){coords, (t_2i){end.x, coords.y}}, color, color);
	draw_line(pxl, (t_line){(t_2i){end.x, coords.y}, end}, color, color);
	draw_line(pxl, (t_line){end, (t_2i){coords.x, end.y}}, color, color);
	draw_line(pxl, (t_line){(t_2i){coords.x, end.y}, coords}, color, color);
}
