/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:54:10 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 16:54:12 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	name_and_newline(t_pxl *pxl, t_dim dim, char *name, t_2i ylen)
{
	t_2i		color;

	color = (t_2i){0x000000, 0xCCFFFF};
	display_str(pxl, dim.start, name, color);
	dim.start = (t_2i){dim.start.x, ylen.x * ylen.y};
	dim.end = (t_2i){dim.end.x, ylen.x * ylen.y};
	draw_line(&(t_pxl_func){&put_dot, pxl->param},
		(t_line){dim.start, dim.end}, 0xFFFFFF, 0xFFFFFF);
	return (ylen.y + 1);
}

static void	display_add_object_options(t_pxl *pxl, t_dim dim)
{
	t_2i	ylen;

	ylen = (t_2i){dim.size.y / 5, 1};
	ylen.y = name_and_newline(pxl, dim, "Light", ylen);
	ylen.y = name_and_newline(pxl, dim, "Sphere", ylen);
	ylen.y = name_and_newline(pxl, dim, "Plane", ylen);
	ylen.y = name_and_newline(pxl, dim, "Cone", ylen);
	ylen.y = name_and_newline(pxl, dim, "Cylinder", ylen);
}

void	draw_image4(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_2i	coords;

	utils = param;
	img = &utils->img[4];
	display_add_object_options(&utils->pxl[0], img->dim);
	coords = (t_2i){img->dim.size.x - 2, img->dim.size.y - 2};
	draw_rect(&(t_pxl_func){&put_dot, img}, (t_2i){0, 0}, coords, 0xFFFFFF);
}
