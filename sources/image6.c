/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:44:25 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/27 17:15:22 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	display_add_object_options(t_utils *utils, t_2i coords)
{
	int	new_line;
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xCCFFFF;
	new_line = (int)utils->img[6].dim.height / 5;
	display_str(&utils->pxl[0], coords, "Light", color);
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
	display_str(&utils->pxl[0], coords, "Sphere", color);
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
	display_str(&utils->pxl[0], coords, "Plane", color);
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
	display_str(&utils->pxl[0], coords, "Cone", color);
	coords.y += (int)new_line;
	draw_line(&(t_pxl_func){&put_dot, utils},
		&(t_line){coords.x, coords.y, utils->curr_img->dim.x1, coords.y},
		0xFFFFFF, 0xFFFFFF);
	display_str(&utils->pxl[0], coords, "Cylinder", color);
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
