/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:43:52 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/29 17:02:11 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	prop0_value(t_utils *utils, t_2i coords, float property)
{
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
	utils->img[9].dim.x0 = coords.x + utils->img[3].dim.x0;
	utils->img[9].dim.y0 = coords.y + utils->img[3].dim.y0;
	utils->img[9].dim.x1 = utils->img[9].dim.x0 + utils->img[9].dim.width;
	utils->img[9].dim.y1 = utils->img[9].dim.y0 + utils->img[9].dim.height;
	coords.x += utils->img[9].dim.width;
	display_int(utils, coords, (int)property, color);
	coords = display_str(&utils->pxl[0], coords, "     ", color);
	utils->img[10].dim.x0 = coords.x + utils->img[3].dim.x0;
	utils->img[10].dim.y0 = coords.y + utils->img[3].dim.y0;
	utils->img[10].dim.x1 = utils->img[10].dim.x0 + utils->img[10].dim.width;
	utils->img[10].dim.y1 = utils->img[10].dim.y0 + utils->img[10].dim.height;
}

static void	prop1_value(t_utils *utils, t_2i coords, float property)
{
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
	utils->img[11].dim.x0 = coords.x + utils->img[3].dim.x0;
	utils->img[11].dim.y0 = coords.y + utils->img[3].dim.y0;
	utils->img[11].dim.x1 = utils->img[11].dim.x0 + utils->img[11].dim.width;
	utils->img[11].dim.y1 = utils->img[11].dim.y0 + utils->img[11].dim.height;
	coords.x += utils->img[11].dim.width;
	display_int(utils, coords, (int)property, color);
	coords = display_str(&utils->pxl[0], coords, "     ", color);
	utils->img[12].dim.x0 = coords.x + utils->img[3].dim.x0;
	utils->img[12].dim.y0 = coords.y + utils->img[3].dim.y0;
	utils->img[12].dim.x1 = utils->img[12].dim.x0 + utils->img[12].dim.width;
	utils->img[12].dim.y1 = utils->img[12].dim.y0 + utils->img[12].dim.height;
}

static void	display_object_property(t_utils *utils, t_2i coords)
{
	char		*prop_name[5];
	int			i;
	t_2i		color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
	prop_name[0] = "Lumen ";
	prop_name[1] = "Radius ";
	prop_name[3] = "Radius ";
	prop_name[4] = "Radius ";
	i = utils->sel_object->type;
	utils->property0 = NULL;
	utils->property1 = NULL;
	if (i == 0)
		utils->property0 = &utils->sel_object->lumen;
	else if (i == 1 || i == 3 || i == 4)
		utils->property0 = &utils->sel_object->radius;
	else
		return ;
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.6);
	display_str(&utils->pxl[0], coords, prop_name[i], color);
	coords = display_str(&utils->pxl[0], coords, "       ", color);
	prop0_value(utils, coords, *(utils->property0));
	if (i == 3 || i == 4)
		utils->property1 = &utils->sel_object->axis_length;
	else
		return ;
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.55);
	prop_name[3] = "Axis ";
	prop_name[4] = "Axis ";
	display_str(&utils->pxl[0], coords, prop_name[i], color);
	coords = display_str(&utils->pxl[0], coords, "       ", color);
	prop1_value(utils, coords, *(utils->property1));
}

static void	display_sel_object_origin(t_utils *utils, t_2i coords)
{
	int		font_height;
	t_2i	offset;
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
	font_height = (int)utils->font2->bound_box[1];
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.3);
	offset = display_str(&utils->pxl[0], coords, "X: ", color);
	display_float(utils, offset, (t_2f){utils->sel_object->origin.x, 1.0f}, color);
	coords.y += (int)font_height;
	offset = display_str(&utils->pxl[0], coords, "Y: ", color);
	display_float(utils, offset, (t_2f){utils->sel_object->origin.y, 1.0f}, color);
	coords.y += (int)font_height;
	offset = display_str(&utils->pxl[0], coords, "Z: ", color);
	display_float(utils, offset, (t_2f){utils->sel_object->origin.z, 1.0f}, color);
}

static void	display_sel_object(t_utils *utils, t_2i coords)
{
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
	coords = display_str(&utils->pxl[0], coords, "Object:", color);
	if (utils->sel_object->type == 0)
		display_str(&utils->pxl[0], coords, "Light", color);
	else if (utils->sel_object->type == 1)
		display_str(&utils->pxl[0], coords, "Sphere", color);
	else if (utils->sel_object->type == 2)
		display_str(&utils->pxl[0], coords, "Plane", color);
	else if (utils->sel_object->type == 3)
		display_str(&utils->pxl[0], coords, "Cone", color);
	else if (utils->sel_object->type == 4)
		display_str(&utils->pxl[0], coords, "Cylinder", color);
	coords.x = (int)(utils->curr_img->dim.width * 0.5);
	coords.y = (int)(utils->curr_img->dim.height * 0.2);
	draw_circlef(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){coords.x, coords.y}, (coords.x + coords.y) / 10, utils->sel_object->color);
	display_sel_object_origin(utils, coords);
	display_object_property(utils, coords);
}

void	draw_image3(void *param)
{
	t_2i	coords;
	t_utils	*utils;

	utils = param;
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	if (utils->sel_object != NULL)
		display_sel_object(utils, coords);
	draw_rect(&(t_pxl_func){&put_pixel, utils->curr_img},
		(t_2i){0, 0}, (t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0x45DD45);
}
