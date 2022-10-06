/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:40:43 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/06 15:46:13 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_plus(void *param)
{
	t_utils		*utils;
	t_img		*img;
	t_2i		coords[2];
	t_pxl_func	pxl[2];
	t_2ui		color;

	utils = (t_utils *)param;
	img = utils->curr_img;
	color = (t_2ui){0x005F00, 0x00B800};
	pxl[0] = (t_pxl_func){&put_pixel, img};
	pxl[1] = (t_pxl_func){&put_dot, img};
	draw_rectf(&pxl[0], (t_2i){0, 0}, img->dim.size, color.x);
	coords[0].x = img->dim.size.x - 2;
	coords[0].y = img->dim.size.y - 2;
	draw_rect(&pxl[1], (t_2i){0, 0}, coords[0], color.y);
	coords[0].x = img->dim.size.x * 30 / 100;
	coords[0].y = img->dim.size.y * 50 / 100;
	coords[1].x = img->dim.size.x * 70 / 100;
	coords[1].y = img->dim.size.y * 50 / 100;
	draw_line(&pxl[1], (t_line){coords[0], coords[1]}, 0xFFFFFF, 0xFFFFFF);
	coords[0].x = img->dim.size.x * 50 / 100;
	coords[0].y = img->dim.size.y * 30 / 100;
	coords[1].x = img->dim.size.x * 50 / 100;
	coords[1].y = img->dim.size.y * 70 / 100;
	draw_line(&pxl[1], (t_line){coords[0], coords[1]}, 0xFFFFFF, 0xFFFFFF);
}
