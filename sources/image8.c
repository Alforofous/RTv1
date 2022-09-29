/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:44:54 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/29 17:02:52 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_image8(void *param)
{
	t_2i	coords[2];
	t_utils	*utils;

	utils = param;
	if (utils->light_render == 1)
		draw_rectf(&(t_pxl_func){&put_pixel, utils->curr_img},
			(t_2i){0, 0}, (t_2i){utils->curr_img->dim.width - 2,
			utils->curr_img->dim.height - 2}, 0xBF5A00);
	draw_rect(&(t_pxl_func){&put_dot, utils},
		(t_2i){0, 0}, (t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0xFFC000);
	coords[0].x = (int)((float)utils->curr_img->dim.width * 0.5f);
	coords[0].y = (int)((float)utils->curr_img->dim.height * 0.45f);
	draw_circlef(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){coords[0].x, coords[0].y}, (coords[0].x + coords[0].y) / 4, 0xFFC000);
	coords[0].x = (int)((float)utils->curr_img->dim.width * 0.5f);
	coords[0].y = (int)((float)utils->curr_img->dim.height * 0.5f);
	coords[1].x = (int)((float)utils->curr_img->dim.width * 0.5f);
	coords[1].y = (int)((float)utils->curr_img->dim.height * 0.8f);
	if (utils->light_render == 1)
		draw_line(&(t_pxl_func){&put_pixel, utils->curr_img},
			&(t_line){coords[0].x, coords[0].y, coords[1].x, coords[1].y},
			0xFFFFFF, 0xFFC000);
	else
		draw_line(&(t_pxl_func){&put_pixel, utils->curr_img},
			&(t_line){coords[0].x, coords[0].y, coords[1].x, coords[1].y},
			0x000000, 0xFFC000);
}
