/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:43:52 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/27 14:18:19 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	prop0_value(t_utils *utils, t_2i coords, float property)
{
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

static void	prop1_value(t_utils *utils, t_2i coords, float property)
{
	utils->img[11].dim.x0 = coords.x + utils->img[3].dim.x0;
	utils->img[11].dim.y0 = coords.y + utils->img[3].dim.y0;
	utils->img[11].dim.x1 = utils->img[11].dim.x0 + utils->img[11].dim.width;
	utils->img[11].dim.y1 = utils->img[11].dim.y0 + utils->img[11].dim.height;
	coords.x += utils->img[11].dim.width;
	display_int(utils, coords, utils->font2, (int)property);
	coords = display_str(utils, coords, utils->font2, "     ");
	utils->img[12].dim.x0 = coords.x + utils->img[3].dim.x0;
	utils->img[12].dim.y0 = coords.y + utils->img[3].dim.y0;
	utils->img[12].dim.x1 = utils->img[12].dim.x0 + utils->img[12].dim.width;
	utils->img[12].dim.y1 = utils->img[12].dim.y0 + utils->img[12].dim.height;
}

static void	*get_light_prop(t_object *object, int prop_i)
{
	t_light	*light;

	light = (t_light *)object->content;
	if (prop_i == 0)
		return (&light->lumen);
	return (NULL);
}

static void	*get_sphere_prop(t_object *object, int prop_i)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)object->content;
	if (prop_i == 0)
		return (&sphere->radius);
	return (NULL);
}

static void	*get_cone_prop(t_object *object, int prop_i)
{
	t_cone	*cone;

	cone = (t_cone *)object->content;
	if (prop_i == 0)
		return (&cone->radius);
	else if (prop_i == 1)
		return (&cone->axis_length);
	return (NULL);
}

static void	*get_cylinder_prop(t_object *object, int prop_i)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)object->content;
	if (prop_i == 0)
		return (&cylinder->radius);
	else if (prop_i == 1)
		return (&cylinder->axis_length);
	return (NULL);
}

static void	display_object_property(t_utils *utils, t_2i coords)
{
	char		*prop_name[5];
	void		*(*f[5])(t_object *, int prop_i);
	int			i;

	f[0] = &get_light_prop;
	f[1] = &get_sphere_prop;
	f[3] = &get_cone_prop;
	f[4] = &get_cylinder_prop;
	prop_name[0] = "Lumen ";
	prop_name[1] = "Radius ";
	prop_name[3] = "Radius ";
	prop_name[4] = "Radius ";
	i = utils->sel_object->type;
	utils->property0 = NULL;
	utils->property1 = NULL;
	if (i == 0 || i == 1 || i == 3 || i == 4)
		utils->property0 = (float *)(*f[i])(utils->sel_object, 0);
	else
		return ;
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.6);
	display_str(utils, coords, utils->font2, prop_name[i]);
	coords = display_str(utils, coords, utils->font2, "       ");
	prop0_value(utils, coords, *(utils->property0));
	if (i == 3 || i == 4)
		utils->property1 = (float *)(*f[i])(utils->sel_object, 1);
	else
		return ;
	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.55);
	prop_name[3] = "Axis ";
	prop_name[4] = "Axis ";
	display_str(utils, coords, utils->font2, prop_name[i]);
	coords = display_str(utils, coords, utils->font2, "       ");
	prop1_value(utils, coords, *(utils->property1));
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
