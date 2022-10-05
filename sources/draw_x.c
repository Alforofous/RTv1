/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:40:11 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/05 15:48:18 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_x(void *param)
{
	t_utils		*utils;
	t_img		*img;
	t_pxl_func	pxl[2];
	t_2i		coords[2];
	t_2i		color;

	utils = (t_utils *)param;
	img = utils->curr_img;
	color = (t_2i){0x5A0000, 0xC80000};
	pxl[0].f = &put_pixel;
	pxl[0].param = img;
	pxl[1].f = &put_dot;
	pxl[1].param = img;
	coords[0].x = img->dim.size.x - 2;
	coords[0].y = img->dim.size.y - 2;
	draw_rectf(&pxl[0], (t_2i){0, 0}, img->dim.size, (t_uint)color.x);
	draw_rect(&pxl[1], (t_2i){0, 0}, coords[0], (t_uint)color.y);
	coords[0].x = img->dim.size.x * 30 / 100;
	coords[0].y = img->dim.size.y * 30 / 100;
	coords[1].x = img->dim.size.x * 70 / 100;
	coords[1].y = img->dim.size.y * 70 / 100;
	draw_line(&pxl[1], (t_line){coords[0], coords[1]}, 0xFFFFFF, 0xFFFFFF);
	coords[0].y = img->dim.size.y * 70 / 100;
	coords[1].y = img->dim.size.y * 30 / 100;
	draw_line(&pxl[1], (t_line){coords[0], coords[1]}, 0xFFFFFF, 0xFFFFFF);
}
