/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:37:45 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/05 12:24:35 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	draw_ray_arrows(t_utils *utils, t_3f ray, t_uint color, t_img *img)
{
	t_3f	p[2];
	t_proj	proj;

	proj = init_proj(60, &(t_2i){img->dim.width, img->dim.height}, &(t_2f){0.1f, 1000.0f});
	ray.x *= -10;
	ray.y *= -10;
	ray.z *= 10;
	p[0] = get_points(utils, &ray, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	p[1] = get_points(utils, &(t_3f){0, 0, 0}, &(t_3f){0.0f, 0.0f, 0.0f}, &proj);
	if (utils->visual_rays == 1)
	{
		draw_circle(&(t_pxl_func){&put_pixel, img}, &(t_2i){(int)p[0].x, (int)p[0].y}, 3, color);
		draw_circle(&(t_pxl_func){&put_pixel, img}, &(t_2i){(int)p[0].x, (int)p[0].y}, 2, 0xFFFFFF);
		draw_circle(&(t_pxl_func){&put_pixel, img}, &(t_2i){(int)p[1].x, (int)p[1].y}, 3, 0xFFFFFF);
	}
	if (utils->visual_rays == 2)
	{
		if (p[1].z < p[0].z)
			draw_line(&(t_pxl_func){&put_pixel, utils->curr_img},
				&(t_line){(int)p[1].x, (int)p[1].y, (int)p[0].x, (int)p[0].y},
				color, 0xFFFFFF);
		else
			draw_line(&(t_pxl_func){&put_pixel, utils->curr_img},
				&(t_line){(int)p[0].x, (int)p[0].y, (int)p[1].x, (int)p[1].y},
				color, 0xFFFFFF);
	}
}

void	draw_image3(t_utils *utils)
{
	int		xy[2];
	t_2f	scrn;
	t_3f	ray;
	t_img	*img;

	img = &utils->img3;
	xy[0] = 0;
	get_camera_directions(utils, &utils->cam);
	while (xy[0] < img->dim.width)
	{
		xy[1] = 0;
		while (xy[1] < img->dim.height)
		{
			scrn.x = (float)(2 * xy[0]) / (float)img->dim.width - 1.0f;
			scrn.y = (float)(-2 * xy[1]) / (float)img->dim.height + 1.0f;
			ray = get_ray(scrn, &utils->cam, &utils->proj);
			draw_ray_arrows(utils, ray, 0x004466, img);
			if (xy[0] + img->dim.x0 == utils->mouse.x
				&& xy[1] + img->dim.y0 == utils->mouse.y)
			draw_ray_arrows(utils, ray, 0xFF0000, img);
			xy[1] += 20;
		}
		xy[0] += 20;
	}
	draw_rect(&(t_pxl_func){&put_pixel, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0x00FFDD);
}
