/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:41:05 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 15:05:01 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	draw_aim_point(t_img *img)
{
	t_2i	coords;

	coords = (t_2i){img->dim.size.x / 2, img->dim.size.y / 2};
	draw_circle(&(t_pxl_func){&put_pixel, img}, coords, 3, 0x004557);
	draw_circle(&(t_pxl_func){&put_pixel, img}, coords, 2, 0xFFFFFF);
}

static void	draw_scene(t_utils *utils, t_object **clo_obj, t_img *img)
{
	t_2i	coords;
	t_uint	color;
	t_ray	ray;

	coords.y = 0;
	while (coords.y <= img->dim.size.y)
	{
		if (coords.y % 6 == utils->density.y)
		{
			coords.x = 0;
			while (coords.x <= img->dim.size.x)
			{
				if (coords.x % 6 == utils->density.x)
				{
					ray = get_ray(coords, img, &utils->cam, &utils->proj);
					color = ray_trace(utils, clo_obj, utils->scene, ray);
					put_pixel(coords, color, img);
				}
				coords.x += 1;
			}
		}
		coords.y += 1;
	}
}

void	draw_image0(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_2i	coords;
	t_2i	color;
	float	plot_time;

	utils = param;
	img = &utils->img[0];
	coords = (t_2i){0, 0};
	color = (t_2i){0x000000, 0xFFFFFF};
	get_camera_directions(utils, &utils->cam);
	draw_scene(utils, &utils->closest_object, img);
	draw_aim_point(img);
	if (utils->density.x == 0 && utils->density.y == 0)
	{	
		plot_time = (float)time_since_success(0.00001, 0);
		coords = display_str(&utils->pxl[0], coords, "Plot time: ", color);
		display_float(&utils->pxl[0], coords, (t_2f){plot_time, 5.0f}, color);
	}
	coords = (t_2i){img->dim.size.x - 1, img->dim.size.y - 1};
	draw_rect(&(t_pxl_func){&put_pixel, img}, (t_2i){0, 0}, coords, 0xFFFFFF);
}
