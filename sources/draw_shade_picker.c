/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shade_picker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:52:47 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/07 11:45:27 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Create shade picker with given color inside of an image.*/
t_uint	shade_picker(t_img *img, t_2i *coords, t_uint color)
{
	t_2f	perc;

	perc.x = (float)(coords->x) / (float)(img->dim.size.x - 1);
	perc.y = (float)(coords->y) / (float)(img->dim.size.y - 1);
	color = transition_colors(0xFFFFFF, color, perc.x);
	color = transition_colors(color, 0x000000, perc.y);
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
	img = &utils->img[6];
	if (utils->sel_object != NULL)
		shade_picker_iter(img, utils->sel_object->color);
	coords = (t_2i){img->dim.size.x - 2, img->dim.size.y - 2};
	draw_rect(&(t_pxl_func){&put_dot, img}, (t_2i){0, 0}, coords, 0xFFFFFF);
}
