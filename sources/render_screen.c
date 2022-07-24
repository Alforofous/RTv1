/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:10:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/23 15:10:07 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	image_processing(t_utils *utils, t_img *img, t_uint fill_color)
{
	utils->curr_img = img;
	fill_img(utils, fill_color);
	img->draw_func(utils);
	mlx_put_image_to_window(utils->mlx, utils->win, img->ptr, img->dim.x0,
		img->dim.y0);
}


void	render_screen(t_utils *utils)
{
	clock_t	interv[2];
	int		xy[2];
	char	*str;
	struct timespec	new_time;

	clock_gettime(CLOCK_MONOTONIC, &new_time);
	utils->elapsed_time = (new_time.tv_sec - utils->time.tv_sec) * 1000000 + (new_time.tv_nsec - utils->time.tv_nsec) / 1000;
	//clock_gettime(CLOCK_MONOTONIC, &utils->time);
	if (utils->elapsed_time >= 200000)
	{
		clock_gettime(CLOCK_MONOTONIC, &utils->time);
	}
	else
	{
		return ;
	}
	xy[0] = utils->img.dim.width / 80;
	xy[1] = utils->img.dim.height / 50;
	interv[0] = clock();
	image_processing(utils, &utils->img, 0x000000);
	interv[1] = clock();
	str = ft_ftoa((float)(interv[1] - interv[0]) / CLOCKS_PER_SEC, 5);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for render time...", -1);
	mlx_string_put(utils->mlx, utils->win, utils->img.dim.x0 + xy[0],
		utils->img.dim.y0 + xy[1], 0x000000, str);
	mlx_string_put(utils->mlx, utils->win, utils->img.dim.x0 + xy[0],
		utils->img.dim.y0 + xy[1] + 1, 0xFFFFFF, str);
	free(str);
	image_processing(utils, &utils->img2, 0x000000);
	str = ft_ftoa(utils->proj.fov, 3);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for FOV...", -1);
	mlx_string_put(utils->mlx, utils->win, 10, 10, 0xFFFFFF, str);
	if (utils->visual_rays >= 1)
		image_processing(utils, &utils->img3, 0x67000000);
	free(str);
}
