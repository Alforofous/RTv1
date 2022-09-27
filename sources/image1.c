/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:44:56 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/27 17:26:43 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_origin(t_utils *utils, t_2i coords, t_ray *cam)
{
	int		font_height;
	t_2i	offset;
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
	font_height = (int)utils->font2->bound_box[1];
	offset = display_str(&utils->pxl[0], coords, "X: ", color);
	display_float(utils, offset, (t_2f){cam->origin.x, 1.0f}, color);
	coords.y += (int)font_height;
	offset = display_str(&utils->pxl[0], coords, "Y: ", color);
	display_float(utils, offset, (t_2f){cam->origin.y, 1.0f}, color);
	coords.y += (int)font_height;
	offset = display_str(&utils->pxl[0], coords, "Z: ", color);
	display_float(utils, offset, (t_2f){cam->origin.z, 1.0f}, color);
}

void	draw_image1(t_utils *utils)
{
	t_2i	coords;
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	coords = display_str(&utils->pxl[0], coords, "FOV: ", color);
	display_int(utils, coords, (int)utils->proj.fov, color);
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.1);
	coords = display_str(&utils->pxl[0], coords, "x", color);
	display_float(utils, coords, (t_2f){utils->multiplier, 1.0f}, color);
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.15);
	display_origin(utils, coords, &utils->cam);
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.25);
	coords = display_str(&utils->pxl[0], coords, "OBJECT COUNT: ", color);
	display_int(utils, coords, (int)ft_lstsize(utils->objects), color);
	draw_rect(&(t_pxl_func){&put_pixel, utils->curr_img},
		(t_2i){0, 0}, (t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}
