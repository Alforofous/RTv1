/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rgb_slider.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:48:53 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/07 11:31:00 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Initiate RGB slider pallete (main colors for palette, changable).*/
static void	init_rgb_slider_palette(t_uint	*color)
{
	color[0] = 0xFF0000;
	color[1] = 0xFFFF00;
	color[2] = 0x00FF00;
	color[3] = 0x00FFFF;
	color[4] = 0x0000FF;
	color[5] = 0xFF00FF;
	color[6] = 0xFF0000;
}

/*Mapping of xy into image size and getting horizontal & vertical percentage
 * for color transition.*/
static float	init_perc_values(t_img *img, t_2i *coords, int *color_i)
{
	float	perc;

	perc = (float)(coords->x) / (float)(img->dim.size.x - 1);
	perc *= (float)*color_i;
	*color_i = (int)(perc - 0.001f);
	while (perc > 1.0f)
		perc -= 1.0f;
	return (perc);
}

/*Create rgb slider with given colors inside of an image.*/
t_uint	rgb_slider(t_img *img, t_2i *coords)
{
	t_uint	color[7];
	t_uint	final_color;
	float	perc;
	int		i;

	final_color = 0x000000;
	init_rgb_slider_palette(&color[0]);
	i = 6;
	perc = init_perc_values(img, coords, &i);
	if (i < 6)
	{
		final_color = transition_colors(color[i], color[i + 1], perc);
	}
	return (final_color);
}

/*Iterrate through the pixels of the image and call rgb_slider function.*/
static void	rgb_iter(t_img *img)
{
	t_2i	coords;

	coords.y = 0;
	while (coords.y <= img->dim.size.y)
	{
		coords.x = 0;
		while (coords.x <= img->dim.size.x)
		{
			put_pixel(coords, rgb_slider(img, &coords), img);
			coords.x += 1;
		}
		coords.y += 1;
	}
}

void	draw_rgb_slider(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_2i	coords;

	utils = param;
	img = &utils->img[5];
	rgb_iter(img);
	coords = (t_2i){img->dim.size.x - 2, img->dim.size.y - 2};
	draw_rect(&(t_pxl_func){&put_dot, img}, (t_2i){0, 0}, coords, 0xFFFFFF);
}
