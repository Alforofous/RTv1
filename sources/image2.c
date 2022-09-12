/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:44:56 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/09 18:53:37 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_origin(t_utils *utils, t_2i coords, t_ray *cam)
{
	int		font_height;
	t_2i	offset;

	font_height = (int)utils->font2->bound_box[1];
	offset = display_str(utils, coords, utils->font2, "X: ");
	display_float(utils, offset, utils->font2, cam->origin.x);
	coords.y += (int)font_height;
	offset = display_str(utils, coords, utils->font2, "Y: ");
	display_float(utils, offset, utils->font2, cam->origin.y);
	coords.y += (int)font_height;
	offset = display_str(utils, coords, utils->font2, "Z: ");
	display_float(utils, offset, utils->font2, cam->origin.z);
}

void	draw_image2(t_utils *utils)
{
	t_2i	coords;

	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	coords = display_str(utils, coords, utils->font2, "FOV: ");
	display_int(utils, coords, utils->font2, (int)utils->proj.fov);
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.1);
	display_origin(utils, coords, &utils->cam);
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.25);
	coords = display_str(utils, coords, utils->font2, "OBJECT COUNT: ");
	display_int(utils, coords, utils->font2, (int)ft_lstsize(utils->objects));
	draw_rect(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}
