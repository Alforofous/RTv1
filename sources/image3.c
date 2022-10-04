/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:43:52 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 16:45:06 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	origin(t_pxl *pxl, t_2i coords, t_object *sel_object)
{
	int		font_height;
	t_2i	offset;
	t_2i	color;

	color.x = 0xFFFFFF;
	color.y = (int)sel_object->color;
	font_height = (int)pxl->font->bound_box[1];
	display_str(pxl, coords, "Object origin: ", color);
	coords.y += (int)font_height;
	offset = display_str(pxl, coords, "X: ", color);
	display_float(pxl, offset, (t_2f){sel_object->origin.x, 1.0f}, color);
	coords.y += (int)font_height;
	offset = display_str(pxl, coords, "Y: ", color);
	display_float(pxl, offset, (t_2f){sel_object->origin.y, 1.0f}, color);
	coords.y += (int)font_height;
	offset = display_str(pxl, coords, "Z: ", color);
	display_float(pxl, offset, (t_2f){sel_object->origin.z, 1.0f}, color);
}

static void	type(t_pxl *pxl, t_2i coords, t_object *sel_object)
{
	t_2i	color;

	color.x = 0xFFFFFF;
	color.y = (int)sel_object->color;
	coords = display_str(pxl, coords, "Object:", color);
	if (sel_object->type == 0)
		display_str(pxl, coords, "Light", color);
	else if (sel_object->type == 1)
		display_str(pxl, coords, "Sphere", color);
	else if (sel_object->type == 2)
		display_str(pxl, coords, "Plane", color);
	else if (sel_object->type == 3)
		display_str(pxl, coords, "Cone", color);
	else if (sel_object->type == 4)
		display_str(pxl, coords, "Cylinder", color);
}

void	draw_image3(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_2i	coords;

	utils = param;
	img = &utils->img[3];
	if (utils->sel_object == NULL)
		return ;
	coords = (t_2i){img->dim.size.x * 0 / 100, img->dim.size.y * 0 / 100};
	type(&utils->pxl[0], coords, utils->sel_object);
	coords = (t_2i){img->dim.size.x * 50 / 100, img->dim.size.y * 20 / 100};
	draw_circlef(&(t_pxl_func){&put_pixel, img}, coords,
		(coords.x + coords.y) / 10, utils->sel_object->color);
	coords = (t_2i){img->dim.size.x * 0 / 100, img->dim.size.y * 30 / 100};
	origin(&utils->pxl[0], coords, utils->sel_object);
	coords = (t_2i){img->dim.size.x * 0 / 100, img->dim.size.y * 55 / 100};
	properties(utils, &utils->pxl[0], coords, utils->sel_object);
	coords = (t_2i){img->dim.size.x - 1, img->dim.size.y - 1};
	draw_rect(&(t_pxl_func){&put_dot, img}, (t_2i){0, 0}, coords,
		utils->sel_object->color);
}
