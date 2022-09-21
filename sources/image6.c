/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/21 16:56:43 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_image6(t_utils *utils)
{
	t_3i	coords;

	coords.x = (int)((float)utils->curr_img->dim.width * 0.3f);
	coords.y = (int)((float)utils->curr_img->dim.height * 0.5f);
	coords.z = (int)((float)utils->curr_img->dim.width * 0.7f);
	draw_rectf(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0x42CD00);
	draw_rect(&(t_pxl_func){&put_dot, utils},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0xFFFFFF);
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, coords.z, coords.y},
		0xFFFFFF, 0xFFFFFF);
	coords.x = (int)((float)utils->curr_img->dim.height * 0.3f);
	coords.y = (int)((float)utils->curr_img->dim.width * 0.5f);
	coords.z = (int)((float)utils->curr_img->dim.height * 0.7f);
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.y, coords.x, coords.y, coords.z},
		0xFFFFFF, 0xFFFFFF);
}
