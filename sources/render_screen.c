/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/18 15:12:25 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	image_processing(t_utils *utils, t_img *img, t_uint fill_color)
{
	utils->curr_img = img;
	fill_img(utils, fill_color);
	img->draw_func(utils);
	mlx_put_image_to_window(utils->mlx, utils->win, img->ptr, img->dim.x0,
		img->dim.y0);
}


void	render_screen(t_utils *utils)
{
	struct timespec	new_time;

	utils->density.y = 9;
	utils->density.x = 9;
	clock_gettime(CLOCK_MONOTONIC, &new_time);
	utils->elapsed_time = (new_time.tv_sec - utils->time.tv_sec)
		* 1000000 + (new_time.tv_nsec - utils->time.tv_nsec) / 1000;
	if (utils->elapsed_time >= 50000)
	{
		clock_gettime(CLOCK_MONOTONIC, &utils->time);
	}
	else
	{
		return ;
	}
	image_processing(utils, &utils->img, 0x000000);
	image_processing(utils, &utils->img2, 0x000000);
	if (utils->visual_rays >= 1)
		image_processing(utils, &utils->img3, 0x67000000);
	if (utils->sel_object != NULL)
	{
		image_processing(utils, &utils->img4, 0x000000);
		image_processing(utils, &utils->img5, 0x000000);
	}
}
