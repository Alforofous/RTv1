/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hold_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:45:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 09:53:15 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rgb_slider_selected(t_utils *utils, t_img *img, t_object *obj)
{
	t_2i	coords;

	coords = (t_2i){utils->mouse.pos.x, utils->mouse.pos.y};
	coords.x -= img[5].dim.start.x;
	coords.y -= img[5].dim.start.y;
	coords.x = ft_max(coords.x, 0);
	coords.y = ft_max(coords.y, 0);
	coords.x = ft_min(coords.x, img[5].dim.size.x - 1);
	coords.y = ft_min(coords.y, img[5].dim.size.y - 1);
	obj->rgb = rgb_slider(&img[5], &coords);
	obj->color = shade_picker(&img[6], &obj->shade_coords, obj->rgb);
	image_processing(utils, &img[6], 0x000000, 0);
}

static void	shade_picker_selected(t_utils *utils, t_img *img, t_object *obj)
{
	obj->shade_coords = (t_2i){utils->mouse.pos.x, utils->mouse.pos.y};
	obj->shade_coords.x -= img[6].dim.start.x;
	obj->shade_coords.y -= img[6].dim.start.y;
	obj->shade_coords.x = ft_max(obj->shade_coords.x, 0);
	obj->shade_coords.y = ft_max(obj->shade_coords.y, 0);
	obj->shade_coords.x = ft_min(obj->shade_coords.x, img[6].dim.size.x - 1);
	obj->shade_coords.y = ft_min(obj->shade_coords.y, img[6].dim.size.y - 1);
	obj->color = shade_picker(&img[6], &obj->shade_coords, obj->rgb);
	image_processing(utils, &img[6], 0x000000, 0);
}

void	mouse_hold_elem(t_utils *utils, int elem)
{
	if (elem == 1 && *(utils->property[0]) > utils->multiplier)
		*(utils->property[0]) -= 1.0f * utils->multiplier;
	else if (elem == 2)
		*(utils->property[0]) += 1.0f * utils->multiplier;
	else if (elem == 3)
		*(utils->property[1]) -= 1.0f * utils->multiplier;
	else if (elem == 4)
		*(utils->property[1]) += 1.0f * utils->multiplier;
	else if (elem == 5)
		rgb_slider_selected(utils, utils->img, utils->sel_object);
	else if (elem == 6)
		shade_picker_selected(utils, utils->img, utils->sel_object);
	else
		return ;
	image_processing(utils, &utils->img[3], 0x000000, 0);
	render_screen(utils);
}
