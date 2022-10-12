/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/12 16:04:08 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	image_processing(t_utils *utils, t_img *img, t_uint fill_col, int mode)
{
	utils->curr_img = img;
	utils->pxl[0].param = utils->curr_img;
	fill_img(utils, fill_col);
	img->draw_func(utils);
	if (mode == 1)
		mlx_put_image_to_window(utils->mlx, utils->win, img->ptr,
			img->dim.start.x, img->dim.start.y);
}

double	time_since_success(double ammount, int id)
{
	static struct timespec	time[8];
	struct timespec			curr_time;
	long int				elapsed;

	clock_gettime(CLOCK_MONOTONIC, &curr_time);
	elapsed = (curr_time.tv_sec - time[id].tv_sec) * 1000000
		+ (curr_time.tv_nsec - time[id].tv_nsec) / 1000;
	if (elapsed > (long int)(ammount * 1000000.0))
	{
		time[id] = curr_time;
	}
	return ((double)elapsed / 1000000.0);
}
/*
pthread_t	thread_id;
pthread_create(&thread_id, NULL, &test, (void *)utils);
pthread_join(thread_id, NULL);
*/

void	render_screen(t_utils *utils)
{
	double	fps;

	fps = 0.01;
	if (time_since_success(fps, 0) >= fps)
	{
		utils->density.y = 5;
		utils->density.x = 5;
		image_processing(utils, &utils->img[0], 0x000000, 0);
		put_images_to_window(utils);
	}
}
