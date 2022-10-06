/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:41:44 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/06 13:38:52 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rgb_iter(t_img *img, t_uint (*f)(t_img *, t_2i *))
{
	t_2i	coords;

	coords.y = 0;
	while (coords.y <= img->dim.size.y)
	{
		coords.x = 0;
		while (coords.x <= img->dim.size.x)
		{
			put_pixel(coords.x, coords.y, (*f)(img, &coords), img);
			coords.x += 1;
		}
		coords.y += 1;
	}
}

void	draw_image5(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_2i	coords;

	utils = param;
	img = &utils->img[5];
	rgb_iter(img, &rgb_slider);
	coords = (t_2i){img->dim.size.x - 2, img->dim.size.y - 2};
	draw_rect(&(t_pxl_func){&put_dot, img}, (t_2i){0, 0}, coords, 0xFFFFFF);
}
