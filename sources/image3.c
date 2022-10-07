/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:43:52 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/07 14:03:05 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	origin(t_pxl *pxl, t_2i coords, t_object *sel_object)
{
	int		font_height;
	t_2i	offset;
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
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
	return (coords.y);
}

static t_2i	type(t_pxl *pxl, t_2i coords, t_object *sel_object)
{
	t_2i	color;

	color.x = (int)~sel_object->color & 0x00FFFFFF;
	color.y = (int)sel_object->color;
	coords = display_str(pxl, coords, "Object:", color);
	if (sel_object->type == 0)
		coords = display_str(pxl, coords, "Light  ", color);
	else if (sel_object->type == 1)
		coords = display_str(pxl, coords, "Sphere  ", color);
	else if (sel_object->type == 2)
		coords = display_str(pxl, coords, "Plane  ", color);
	else if (sel_object->type == 3)
		coords = display_str(pxl, coords, "Cone  ", color);
	else if (sel_object->type == 4)
		coords = display_str(pxl, coords, "Cylinder  ", color);
	return (coords);
}

void	draw_image3(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_2i	coords;
	int		font_height;

	utils = param;
	img = &utils->img[3];
	if (utils->sel_object == NULL)
		return ;
	font_height = (int)utils->font->bound_box[1];
	coords = (t_2i){img->dim.size.x * 0 / 100, img->dim.size.y * 0 / 100};
	type(&utils->pxl[0], coords, utils->sel_object);
	coords.y += font_height;
	coords = (t_2i){img->dim.size.x * 0 / 100, img->dim.size.y * 30 / 100};
	coords.y = origin(&utils->pxl[0], coords, utils->sel_object) + font_height;
	properties(utils, &utils->pxl[0], coords, utils->sel_object);
	coords = (t_2i){img->dim.size.x * 50 / 100, img->dim.size.y * 20 / 100};
	draw_circlef(&(t_pxl_func){&put_pixel, img}, coords,
		(coords.x + coords.y) / 10, utils->sel_object->color);
	coords = (t_2i){img->dim.size.x - 1, img->dim.size.y - 1};
	draw_rect(&(t_pxl_func){&put_pixel, img}, (t_2i){0, 0}, coords, 0xFFFFFF);
}
