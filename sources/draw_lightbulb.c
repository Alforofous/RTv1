/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lightbulb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:48:55 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/05 11:48:57 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_lightbulb(t_img *img, t_dim button, int mode)
{
	t_pxl_func	pxl[2];
	t_2i		coords[2];
	t_2i		color;
	t_line		line;

	color = (t_2i){0xBF5A00, 0xFFC000};
	pxl[0].f = &put_pixel;
	pxl[0].param = img;
	pxl[1].f = &put_dot;
	pxl[1].param = img;
	if (mode == 1)
		draw_rectf(&pxl[0], button.start, button.end, (t_uint)color.x);
	draw_rect(&pxl[1], button.start, button.end, (t_uint)color.y);
	coords[0].x = button.start.x + button.size.x * 50 / 100;
	coords[0].y = button.start.y + button.size.y * 45 / 100;
	draw_circlef(&pxl[0], coords[0], coords[0].x / 2, (t_uint)color.y);
	coords[0].x = button.start.x + button.size.x * 50 / 100;
	coords[0].y = button.start.y + button.size.y * 50 / 100;
	coords[1].x = button.start.x + button.size.x * 50 / 100;
	coords[1].y = button.start.y + button.size.y * 80 / 100;
	line = (t_line){coords[0], coords[1]};
	if (mode == 1)
		draw_line(&pxl[0], line, 0xFFFFFF, (t_uint)color.y);
	else
		draw_line(&pxl[1], line, 0x000000, (t_uint)color.y);
}
