/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:44:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/30 14:58:03 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_image4(void *param)
{
	t_2i	coords[2];
	t_utils	*utils;

	utils = param;
	coords[0].x = (int)(utils->curr_img->dim.size.x * 0.3);
	coords[0].y = (int)(utils->curr_img->dim.size.y * 0.3);
	coords[1].x = (int)(utils->curr_img->dim.size.x * 0.7);
	coords[1].y = (int)(utils->curr_img->dim.size.y * 0.7);
	draw_rectf(&(t_pxl_func){&put_pixel, utils->curr_img},
		(t_2i){0, 0}, (t_2i){utils->curr_img->dim.size.x - 1,
		utils->curr_img->dim.size.y - 1}, 0xCD0000);
	draw_rect(&(t_pxl_func){&put_dot, utils},
		(t_2i){0, 0}, (t_2i){utils->curr_img->dim.size.x - 1,
		utils->curr_img->dim.size.y - 1}, 0xFFFFFF);
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords[0].x, coords[0].y, coords[1].x, coords[1].y},
		0xFFFFFF, 0xFFFFFF);
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords[0].x, coords[1].y, coords[1].x, coords[0].y},
		0xFFFFFF, 0xFFFFFF);
}
