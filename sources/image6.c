/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/22 12:27:25 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_image6(t_utils *utils)
{
	t_2i	coords[2];

	coords[0].x = (int)(utils->curr_img->dim.width * 0.5);
	coords[0].y = (int)(utils->curr_img->dim.height * 0.0);
	coords[1].x = (int)(utils->curr_img->dim.width * 0.5);
	coords[1].y = (int)(utils->curr_img->dim.height * 1.0);
	draw_rectf(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0x42CD00);
	draw_rect(&(t_pxl_func){&put_dot, utils},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0xFFFFFF);
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords[0].x, coords[0].y, coords[1].x, coords[1].y},
		0xFFFFFF, 0xFFFFFF);
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords[0].y, coords[0].x, coords[1].y, coords[1].x},
		0xFFFFFF, 0xFFFFFF);
}
