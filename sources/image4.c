/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:25:31 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/25 16:37:59 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_sel_object_origin(t_utils *utils, t_2i coords)
{
	int		bb;
	t_2i	offset;

	bb = (int)utils->font2->bound_box[1];
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.3);
	offset = display_str(utils, coords, utils->font2, "X: ");
	display_float(utils, offset, utils->font2, utils->sel_object->origin.x);
	coords.y += (int)bb;
	offset = display_str(utils, coords, utils->font2, "Y: ");
	display_float(utils, offset, utils->font2, utils->sel_object->origin.y);
	coords.y += (int)bb;
	offset = display_str(utils, coords, utils->font2, "Z: ");
	display_float(utils, offset, utils->font2, utils->sel_object->origin.z);
}

static void	display_sel_object(t_utils *utils, t_2i coords)
{
	if (utils->sel_object != NULL)
	{
		if (utils->sel_object->type == 1)
			display_str(utils, coords, utils->font2, "Sphere");
		if (utils->sel_object->type == 2)
			display_str(utils, coords, utils->font2, "Plane");
		if (utils->sel_object->type == 3)
			display_str(utils, coords, utils->font2, "N/A");
		coords.x = (int)(utils->curr_img->dim.width * 0.4);
		coords.y = (int)(utils->curr_img->dim.height * 0.1);
		draw_rectf(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
			&(t_2i){coords.x, coords.y}, &(t_2i){(int)(coords.x * 0.6),
			(int)(coords.x * 0.6)}, utils->sel_object->color);
		display_sel_object_origin(utils, coords);
	}
}

void	draw_image4(t_utils *utils)
{
	t_2i	coords;

	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	coords = display_str(utils, coords, utils->font2, "Object:");
	display_sel_object(utils, coords);
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0x45DD45);
}
