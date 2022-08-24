/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/22 16:22:18 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	put_screen(t_utils *utils)
{
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img.ptr,
		utils->img.dim.x0, utils->img.dim.y0);
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img2.ptr,
		utils->img2.dim.x0, utils->img2.dim.y0);
	if (utils->visual_rays >= 1)
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img3.ptr,
			utils->img3.dim.x0, utils->img3.dim.y0);
	if (utils->sel_object != NULL)
	{
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img4.ptr,
			utils->img4.dim.x0, utils->img4.dim.y0);
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img5.ptr,
			utils->img5.dim.x0, utils->img5.dim.y0);
	}
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img6.ptr,
		utils->img6.dim.x0, utils->img6.dim.y0);
	if (utils->add_object_window == 1)
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img7.ptr,
			utils->img7.dim.x0, utils->img7.dim.y0);
}

static void	add_object_menu(t_utils *utils)
{
	(void)utils;
}

void	hold_left_button(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}

void	left_button_down(t_utils *utils, int x, int y)
{
	utils->add_object_window = 0;
	put_screen(utils);
	if (coords_in_img(&utils->img5, x, y) && utils->sel_object != NULL)
		delete_sel_object(utils, &utils->objects);
	else if (utils->add_object_window == 1)
		add_object_menu(utils);
	else if (coords_in_img(&utils->img6, x, y))
	{
		utils->add_object_window = 1;
		utils->img7.dim.x0 = utils->mouse.x;
		utils->img7.dim.y0 = utils->mouse.y;
		utils->img7.dim.x1 = utils->mouse.x + utils->img7.dim.width;
		utils->img7.dim.y1 = utils->mouse.y + utils->img7.dim.height;
		put_screen(utils);
	}
	else if (coords_in_img(&utils->img, x, y))
	{
		x -= utils->img.dim.x0;
		y -= utils->img.dim.y0;
		ray_plotting(utils, &utils->img, (t_2i){x, y});
		if (utils->sel_object == utils->closest_object)
		{
			utils->sel_object = NULL;
			image_processing(utils, &utils->img2, 0x000000);
			image_processing(utils, &utils->img6, 0x000000);
		}
		else
		{
			ft_putstr("TEST\n");
			utils->sel_object = utils->closest_object;
			image_processing(utils, &utils->img4, 0x000000);
			image_processing(utils, &utils->img5, 0x000000);
			utils->closest_object = NULL;
		}
	}
}

void	left_button_up(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}
