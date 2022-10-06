/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:47:48 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/06 15:09:51 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_dim	button_pos(t_2i pos, t_2i offset, t_2i size)
{
	t_dim	button;

	button.start = (t_2i){pos.x + offset.x, pos.y + offset.y};
	button.end = (t_2i){button.start.x + size.x, button.start.y + size.y};
	button.size = size;
	return (button);
}

static float	*name(t_pxl *pxl, t_2i coords, t_object *object, char *name)
{
	t_2i		color;
	float		*property;

	color = (t_2i){0x000000, 0xFFFFFF};
	if (ft_strequ(name, "Lumen: ") == 1)
		property = &object->lumen;
	else if (ft_strequ(name, "Radius: ") == 1)
		property = &object->radius;
	else if (ft_strequ(name, "Axis: ") == 1)
		property = &object->axis_length;
	else
		return NULL;
	coords = display_str(pxl, coords, name, color);
	return (property);
}

static void	property0(t_utils *utils, t_pxl *pxl, t_2i coords, t_object *object)
{
	t_2i	color;
	t_2i	btn;

	btn = utils->button.size;
	color = (t_2i){0x000000, 0xFFFFFF};
	utils->property[0] = NULL;
	if (object->type == 0)
		utils->property[0] = name(pxl, coords, object, "Lumen: ");
	else if (object->type != 2)
		utils->property[0] = name(pxl, coords, object, "Radius: ");
	else
		return ;
	if (utils->property[0] == NULL)
		return ;
	coords = display_str(pxl, coords, "        ", (t_2i){0x000000, 0x000000});
	utils->img[9].dim = button_pos(coords, utils->img[3].dim.start, btn);
	coords.x += btn.x;
	display_int(pxl, coords, (int)*(utils->property[0]), color);
	coords = display_str(pxl, coords, "      ", (t_2i){0x000000, 0x000000});
	utils->img[10].dim = button_pos(coords, utils->img[3].dim.start, btn);
}

static void	property1(t_utils *utils, t_pxl *pxl, t_2i coords, t_object *object)
{
	t_2i	color;
	t_2i	btn;

	btn = utils->button.size;
	color = (t_2i){0x000000, 0xFFFFFF};
	utils->property[1] = NULL;
	if (object->type == 3 || object->type == 4)
		utils->property[1] = name(pxl, coords, object, "Axis: ");
	else
		return ;
	if (utils->property[1] == NULL)
		return ;
	coords = display_str(pxl, coords, "        ", (t_2i){0x000000, 0x000000});
	utils->img[11].dim = button_pos(coords, utils->img[3].dim.start, btn);
	coords.x += btn.x;
	display_int(pxl, coords, (int)*(utils->property[1]), color);
	coords = display_str(pxl, coords, "      ", (t_2i){0x000000, 0x000000});
	utils->img[12].dim = button_pos(coords, utils->img[3].dim.start, btn);
}

void	properties(t_utils *utils, t_pxl *pxl, t_2i coords, t_object *object)
{
	int	font_height;

	font_height = (int)pxl->font->bound_box[1];
	property0(utils, pxl, coords, object);
	coords.y += (int)font_height;
	property1(utils, pxl, coords, object);
}
