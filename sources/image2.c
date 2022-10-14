/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:43:34 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/14 15:05:20 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	draw_ray_arrows(t_img *img, t_3f ray, t_uint color, int mode)
{
	t_3f	p[2];
	t_2i	coords;
	t_proj	proj;
	t_line	line;

	proj = init_proj(60, &img->dim.size, &(t_2f){0.1f, 1000.0f});
	ray.x *= -10;
	ray.y *= 10;
	ray.z *= 10;
	p[0] = get_points(img, &ray, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	p[1] = get_points(img, &(t_3f){0, 0, 0}, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	if (mode == 1)
	{
		coords = (t_2i){(int)p[0].x, (int)p[0].y};
		draw_circle(&(t_pxl_func){&put_pixel, img}, coords, 3, color);
		draw_circle(&(t_pxl_func){&put_pixel, img}, coords, 2, 0xFFFFFF);
		draw_circle(&(t_pxl_func){&put_pixel, img}, coords, 3, 0xFFFFFF);
	}
	if (mode == 2)
	{
		line.start = (t_2i){(int)p[0].x, (int)p[0].y};
		line.end = (t_2i){(int)p[1].x, (int)p[1].y};
		draw_line(&(t_pxl_func){&put_pixel, img}, line, color, 0xFFFFFF);
	}
}

void	draw_image2(void *param)
{
	t_utils	*utils;
	t_img	*img;
	t_ray	ray;
	t_2i	coords;

	utils = param;
	img = &utils->img[2];
	coords.y = 0;
	get_camera_directions(utils, &utils->cam);
	while (coords.y < img->dim.size.y)
	{
		coords.x = 0;
		while (coords.x < img->dim.size.x)
		{
			ray = get_ray(coords, img, &utils->cam, &utils->proj);
			draw_ray_arrows(img, ray.dir, 0x004466, utils->visual_rays);
			coords.x += 20;
		}
		coords.y += 20;
	}
	coords = (t_2i){img->dim.size.x - 1, img->dim.size.y - 1};
	draw_rect(&(t_pxl_func){&put_pixel, img}, (t_2i){0, 0}, coords, 0x00FFDD);
}
