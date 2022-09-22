/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_increment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:17:17 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 14:26:49 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_increment(t_utils *utils)
{
	t_2i		coords[2];
	t_uint		color[2];
	t_pxl_func	pxl[2];

	color[0] = 0x005A3F;
	color[1] = 0x00C864;
	coords[0].x = 0;
	coords[0].y = 0;
	coords[1].x = utils->curr_img->dim.width - 2;
	coords[1].y = utils->curr_img->dim.height - 2;
	pxl[0].f = &put_pixel;
	pxl[0].param = utils->curr_img;
	pxl[1].f = &put_dot;
	pxl[1].param = utils;
	draw_rectf(&pxl[0], coords[0], coords[1], color[0]);
	draw_rect(&pxl[1], coords[0], coords[1], color[1]);
	coords[0].x = (int)((float)utils->curr_img->dim.width * 0.3f);
	coords[0].y = (int)((float)utils->curr_img->dim.height * 0.3f);
	coords[1].x = (int)((float)utils->curr_img->dim.width * 1.0f);
	coords[1].y = (int)((float)utils->curr_img->dim.height * 0.5f);
	draw_line(&pxl[1], &(t_line){coords[0].x, coords[0].y, coords[1].x, coords[1].y},
		color[1], color[0]);
	coords[0].y = (int)((float)utils->curr_img->dim.height * 0.7f);
	draw_line(&pxl[1], &(t_line){coords[0].x, coords[0].y, coords[1].x, coords[1].y},
		color[1], color[0]);
}
