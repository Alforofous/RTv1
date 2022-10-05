/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lightbulb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:48:55 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/05 15:55:50 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_lightbulb(void *param)
{
	t_utils		*utils;
	t_img		*img;
	t_pxl_func	pxl[2];
	t_2i		coords[2];
	t_2ui		color;

	utils = (t_utils *)param;
	img = utils->curr_img;
	color = (t_2ui){0xBF5A00, 0xFFC000};
	pxl[0] = (t_pxl_func){&put_pixel, img};
	pxl[1] = (t_pxl_func){&put_dot, img};
	coords[0] = (t_2i){img->dim.size.x - 2, img->dim.size.y - 2};
	if (utils->light_render == 1)
		draw_rectf(&pxl[0], (t_2i){0, 0}, coords[0], color.x);
	draw_rect(&pxl[1], (t_2i){0, 0}, coords[0], color.y);
	coords[0].x = img->dim.size.x * 50 / 100;
	coords[0].y = img->dim.size.y * 45 / 100;
	coords[1].x = img->dim.size.x + img->dim.size.y;
	draw_circlef(&pxl[0], coords[0], coords[1].x / 8, color.y);
	coords[0].x = img->dim.size.x * 50 / 100;
	coords[0].y = img->dim.size.y * 50 / 100;
	coords[1].x = img->dim.size.x * 50 / 100;
	coords[1].y = img->dim.size.y * 80 / 100;
	if (utils->light_render == 1)
		draw_line(&pxl[1], (t_line){coords[0], coords[1]}, 0xFFFFFF, color.y);
	else
		draw_line(&pxl[1], (t_line){coords[0], coords[1]}, 0x000000, color.y);
}
