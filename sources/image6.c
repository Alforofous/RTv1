/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:44:25 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 13:58:58 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_add_object_options(t_utils *utils, t_2i coords)
{
	int	new_line;

	new_line = (int)utils->img[6].dim.height / 5;
	display_str(utils, coords, utils->font2, "Light");
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
	display_str(utils, coords, utils->font2, "Sphere");
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
	display_str(utils, coords, utils->font2, "Plane");
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
	display_str(utils, coords, utils->font2, "Cone");
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
	display_str(utils, coords, utils->font2, "Cylinder");
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
}

void	draw_image6(t_utils *utils)
{
	t_2i	coords;

	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	display_add_object_options(utils, coords);
	draw_rect(&(t_pxl_func){&put_dot, utils},
		(t_2i){0, 0}, (t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0xFFFFFF);
}
