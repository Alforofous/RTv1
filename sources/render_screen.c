/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 14:28:25 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_screen(t_utils *utils)
{
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[0].ptr,
		utils->img[0].dim.x0, utils->img[0].dim.y0);
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[1].ptr,
		utils->img[1].dim.x0, utils->img[1].dim.y0);
	if (utils->visual_rays >= 1)
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[2].ptr,
			utils->img[2].dim.x0, utils->img[2].dim.y0);
	if (utils->sel_object != NULL)
	{
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[3].ptr,
			utils->img[3].dim.x0, utils->img[3].dim.y0);
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[4].ptr,
			utils->img[4].dim.x0, utils->img[4].dim.y0);
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[7].ptr,
			utils->img[7].dim.x0, utils->img[7].dim.y0);
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[9].ptr,
			utils->img[9].dim.x0, utils->img[9].dim.y0);
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[10].ptr,
			utils->img[10].dim.x0, utils->img[10].dim.y0);
	}
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[5].ptr,
		utils->img[5].dim.x0, utils->img[5].dim.y0);
	if (utils->add_object_menu == 1)
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[6].ptr,
			utils->img[6].dim.x0, utils->img[6].dim.y0);
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[8].ptr,
		utils->img[8].dim.x0, utils->img[8].dim.y0);
}

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
	image_processing(utils, &utils->img[0], 0x000000);
	image_processing(utils, &utils->img[1], 0x000000);
	image_processing(utils, &utils->img[5], 0x000000);
	image_processing(utils, &utils->img[8], 0x000000);
	if (utils->visual_rays >= 1)
		image_processing(utils, &utils->img[2], 0x67000000);
	if (utils->sel_object != NULL)
	{
		image_processing(utils, &utils->img[3], 0x000000);
		image_processing(utils, &utils->img[4], 0x000000);
		image_processing(utils, &utils->img[7], 0x000000);
	}
	put_screen(utils);
}
