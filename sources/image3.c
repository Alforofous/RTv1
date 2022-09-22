/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:43:52 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 15:53:08 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_object_property(t_utils *utils, t_2i coords)
{
	t_read_obj	obj;
	float		property;

	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.6);
	if (utils->sel_object->type == 0)
	{
		obj.light = (t_light *)utils->sel_object->content;
		coords = display_str(utils, coords, utils->font2, "Lumen ");
		property = obj.light->lumen;
	}
	else if (utils->sel_object->type == 1)
	{
		obj.sphere = (t_sphere *)utils->sel_object->content;
		coords = display_str(utils, coords, utils->font2, "Radius ");
		property = obj.sphere->radius;
	}
	else if (utils->sel_object->type == 3)
	{
		obj.cone = (t_cone *)utils->sel_object->content;
		coords = display_str(utils, coords, utils->font2, "Radius ");
		property = obj.cone->radius;
	}
	else if (utils->sel_object->type == 4)
	{
		obj.cylinder = (t_cylinder *)utils->sel_object->content;
		coords = display_str(utils, coords, utils->font2, "Radius ");
		property = obj.cylinder->radius;
	}
	else
		return ;
	utils->img[9].dim.x0 = coords.x + utils->img[3].dim.x0;
	utils->img[9].dim.y0 = coords.y + utils->img[3].dim.y0;
	utils->img[9].dim.x1 = utils->img[9].dim.x0 + utils->img[9].dim.width;
	utils->img[9].dim.y1 = utils->img[9].dim.y0 + utils->img[9].dim.height;
	coords.x += utils->img[9].dim.width;
	display_int(utils, coords, utils->font2, (int)property);
	coords = display_str(utils, coords, utils->font2, "     ");
	utils->img[10].dim.x0 = coords.x + utils->img[3].dim.x0;
	utils->img[10].dim.y0 = coords.y + utils->img[3].dim.y0;
	utils->img[10].dim.x1 = utils->img[10].dim.x0 + utils->img[10].dim.width;
	utils->img[10].dim.y1 = utils->img[10].dim.y0 + utils->img[10].dim.height;
}

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
		&(t_2i){coords.x, coords.y}, (coords.x + coords.y) / 10, utils->sel_object->color);
	display_sel_object_origin(utils, coords);
	display_object_property(utils, coords);
}

void	draw_image3(t_utils *utils)
{
	t_2i	coords;

	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	if (utils->sel_object != NULL)
		display_sel_object(utils, coords);
	draw_rect(&(t_pxl_func){&put_pixel, utils->curr_img},
		(t_2i){0, 0}, (t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0x45DD45);
}
