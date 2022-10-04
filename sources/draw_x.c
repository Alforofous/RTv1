/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:40:11 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 16:40:17 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_x(t_img *img, t_dim button)
{
	t_pxl_func	pxl[2];
	t_2i		coords[2];
	t_2i		color;

	color = (t_2i){0x5A0000, 0xC80000};
	pxl[0].f = &put_pixel;
	pxl[0].param = img;
	pxl[1].f = &put_dot;
	pxl[1].param = img;
	draw_rectf(&pxl[0], button.start, button.end, (t_uint)color.x);
	draw_rect(&pxl[1], button.start, button.end, (t_uint)color.y);
	coords[0].x = button.start.x + button.size.x * 30 / 100;
	coords[0].y = button.start.y + button.size.y * 30 / 100;
	coords[1].x = button.start.x + button.size.x * 70 / 100;
	coords[1].y = button.start.y + button.size.y * 70 / 100;
	draw_line(&pxl[1], (t_line){coords[0], coords[1]}, 0xFFFFFF, 0xFFFFFF);
	coords[0].y = button.start.y + button.size.y * 70 / 100;
	coords[1].y = button.start.y + button.size.y * 30 / 100;
	draw_line(&pxl[1], (t_line){coords[0], coords[1]}, 0xFFFFFF, 0xFFFFFF);
}
