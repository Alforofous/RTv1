/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:47:48 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 16:53:04 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static float	*name(t_pxl *pxl, t_2i *coords, t_object *object, char *name)
{
	t_2i		color;
	float		*property;

	color = (t_2i){0x000000, 0xFFFFFF};
	if (ft_strequ(name, "Lumen: ") == 1)
		property = &object->lumen;
	else if (ft_strequ(name, "Radius: ") == 1)
		property = &object->radius;
	else if (ft_strequ(name, "Axis length: ") == 1)
		property = &object->axis_length;
	else
		return NULL;
	*coords = display_str(pxl, *coords, name, color);
	return (property);
}

static void	property0(t_utils *utils, t_pxl *pxl, t_2i coords, t_object *object)
{
	t_2i	color;

	color = (t_2i){0x000000, 0xFFFFFF};
	utils->property[0] = NULL;
	if (object->type == 0)
		utils->property[0] = name(pxl, &coords, object, "Lumen");
	else if (object->type != 2)
		utils->property[0] = name(pxl, &coords, object, "Radius");
	else
		return ;
	utils->button[3] = get_button_position(coords);
	draw_decrement(pxl->param, utils->button[3]);
	coords.x += utils->button[3].size.x;
	display_int(pxl, coords, (int)*(utils->property[0]), color);
	coords = display_str(pxl, coords, "         ", (t_2i){0x000000, 0x000000});
	utils->button[4] = get_button_position(coords);
	draw_increment(pxl->param, utils->button[4]);
}

static void	property1(t_utils *utils, t_pxl *pxl, t_2i coords, t_object *object)
{
	t_2i	color;

	color = (t_2i){0x000000, 0xFFFFFF};
	utils->property[1] = NULL;
	if (object->type == 3 || object->type == 4)
		utils->property[1] = name(pxl, &coords, object, "Axis length");
	else
		return ;
	utils->button[5] = get_button_position(coords);
	draw_decrement(pxl->param, utils->button[5]);
	coords.x += utils->button[4].size.x;
	display_int(pxl, coords, (int)*(utils->property[1]), color);
	coords = display_str(pxl, coords, "         ", (t_2i){0x000000, 0x000000});
	utils->button[6] = get_button_position(coords);
	draw_increment(pxl->param, utils->button[6]);
}

void	properties(t_utils *utils, t_pxl *pxl, t_2i coords, t_object *object)
{
	int	font_height;

	font_height = (int)pxl->font->bound_box[1];
	property0(utils, pxl, coords, object);
	coords.y += (int)font_height;
	property1(utils, pxl, coords, object);
}
