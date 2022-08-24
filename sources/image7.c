/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:45:10 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/22 13:51:52 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_add_object_options(t_utils *utils, t_2i coords)
{
	int		font_height;

	font_height = (int)utils->font2->bound_box[1];
	display_str(utils, coords, utils->font2, "Add Object:");
	coords.y += (int)font_height;
	display_str(utils, coords, utils->font2, "Sphere");
	coords.y += (int)font_height;
	display_str(utils, coords, utils->font2, "Plane");
	coords.y += (int)font_height;
	display_str(utils, coords, utils->font2, "Cone");
	coords.y += (int)font_height;
	display_str(utils, coords, utils->font2, "Cylinder");
}

void	draw_image7(t_utils *utils)
{
	t_2i	coords;

	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	display_add_object_options(utils, coords);
	draw_rect(&(t_pxl_func){&put_dot, utils},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0x6988FD);
}
