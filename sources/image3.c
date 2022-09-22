/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:43:52 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 12:43:57 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_sel_object_origin(t_utils *utils, t_2i coords)
{
	int		font_height;
	t_2i	offset;

	font_height = (int)utils->font2->bound_box[1];
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.3);
	offset = display_str(utils, coords, utils->font2, "X: ");
	display_float(utils, offset, utils->font2, utils->sel_object->origin.x);
	coords.y += (int)font_height;
	offset = display_str(utils, coords, utils->font2, "Y: ");
	display_float(utils, offset, utils->font2, utils->sel_object->origin.y);
	coords.y += (int)font_height;
	offset = display_str(utils, coords, utils->font2, "Z: ");
	display_float(utils, offset, utils->font2, utils->sel_object->origin.z);
}

static void	display_sel_object(t_utils *utils, t_2i coords)
{
	coords = display_str(utils, coords, utils->font2, "Object:");
	if (utils->sel_object->type == 0)
		display_str(utils, coords, utils->font2, "Light");
	else if (utils->sel_object->type == 1)
		display_str(utils, coords, utils->font2, "Sphere");
	else if (utils->sel_object->type == 2)
		display_str(utils, coords, utils->font2, "Plane");
	else if (utils->sel_object->type == 3)
		display_str(utils, coords, utils->font2, "Cone");
	else if (utils->sel_object->type == 4)
		display_str(utils, coords, utils->font2, "Cylinder");
	coords.x = (int)(utils->curr_img->dim.width * 0.5);
	coords.y = (int)(utils->curr_img->dim.height * 0.2);
	draw_circlef(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){coords.x, coords.y}, coords.x / 10, utils->sel_object->color);
	display_sel_object_origin(utils, coords);
}

void	draw_image3(t_utils *utils)
{
	t_2i	coords;

	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	if (utils->sel_object != NULL)
		display_sel_object(utils, coords);
	draw_rect(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0x45DD45);
}
