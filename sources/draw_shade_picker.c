/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shade_picker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:52:47 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:27:53 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	draw_selector(t_img *img, t_2i coords)
{
	draw_circle(&(t_pxl_func){&put_pixel, img}, coords, 4, 0x005223);
	draw_circle(&(t_pxl_func){&put_pixel, img}, coords, 5, 0xFFFFFF);
}

/*Create shade picker with given color inside of an image.*/
t_uint	shade_picker(t_img *img, t_2i *coords, t_uint color)
{
	t_2d	perc;

	perc.x = (double)(coords->x) / (double)(img->dim.size.x - 1);
	perc.y = (double)(coords->y) / (double)(img->dim.size.y - 1);
	color = transition_colors(color, 0xFFFFFF, (float)perc.x);
	color = transition_colors(color, 0x000000, (float)perc.y);
	return (color);
}

/*Iterrate through the pixels of the image and call shade_picker function.*/
static void	shade_picker_iter(t_img *img, t_uint color)
{
	t_2i	coords;

	coords.y = 0;
	while (coords.y <= img->dim.size.y)
	{
		coords.x = 0;
		while (coords.x <= img->dim.size.x)
		{
			put_pixel(coords, shade_picker(img, &coords, color), img);
			coords.x += 1;
		}
		coords.y += 1;
	}
}

void	draw_shade_picker(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_2i	coords;

	utils = param;
	if (utils->sel_object == NULL)
		return ;
	img = &utils->img[6];
	shade_picker_iter(img, utils->sel_object->rgb);
	coords = (t_2i){img->dim.size.x - 2, img->dim.size.y - 2};
	draw_rect(&(t_pxl_func){&put_dot, img}, (t_2i){0, 0}, coords, 0xFFFFFF);
	draw_selector(img, utils->sel_object->shade_coords);
}
