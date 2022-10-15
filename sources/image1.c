/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:44:56 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 11:09:57 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	object_cnt(t_pxl *pxl, t_2i coords, int count)
{
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xCCCCCC;
	coords = display_str(pxl, coords, "Object count: ", color);
	display_int(pxl, coords, count, color);
}

static int	camera_origin(t_pxl *pxl, t_2i coords, t_cam *cam)
{
	int		font_height;
	t_2i	offset;
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xFFFFFF;
	font_height = (int)pxl->font->bound_box[1];
	display_str(pxl, coords, "Camera origin: ", (t_2i){0x000000, 0x955421});
	coords.y += (int)font_height;
	offset = display_str(pxl, coords, "X: ", color);
	display_double(pxl, offset, (t_2d){cam->origin.x, 1.0f}, color);
	coords.y += (int)font_height;
	offset = display_str(pxl, coords, "Y: ", color);
	display_double(pxl, offset, (t_2d){cam->origin.y, 1.0f}, color);
	coords.y += (int)font_height;
	offset = display_str(pxl, coords, "Z: ", color);
	display_double(pxl, offset, (t_2d){cam->origin.z, 1.0f}, color);
	return (coords.y);
}

static void	fov(t_pxl *pxl, t_2i coords, int fov, double multiplier)
{
	t_2i	color;

	color.x = 0x000000;
	color.y = 0xCCCCCC;
	coords = display_str(pxl, coords, "FOV: ", color);
	coords = display_int(pxl, coords, fov, color);
	coords = display_str(pxl, coords, "  x", color);
	display_double(pxl, coords, (t_2d){multiplier, 1.0f}, color);
}

void	draw_image1(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_2i	coords;
	int		font_height;

	utils = param;
	img = &utils->img[1];
	font_height = (int)utils->pxl->font->bound_box[1];
	coords = (t_2i){img->dim.size.x * 0 / 100, img->dim.size.y * 0 / 100};
	fov(&utils->pxl[0], coords, (int)utils->proj.fov, utils->multiplier);
	coords.y += font_height;
	coords.y = camera_origin(&utils->pxl[0], coords, &utils->cam);
	coords.y += font_height;
	object_cnt(&utils->pxl[0], coords, (int)ft_lstsize(utils->scene));
	coords = (t_2i){img->dim.size.x - 1, img->dim.size.y - 1};
	draw_rect(&(t_pxl_func){&put_pixel, img}, (t_2i){0, 0}, coords, 0xFFFFFF);
}
