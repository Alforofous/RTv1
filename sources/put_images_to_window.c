/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_images_to_screen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:28:32 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/07 11:13:43 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	put_main_images(t_utils *utils)
{
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[0].ptr,
		utils->img[0].dim.start.x, utils->img[0].dim.start.y);
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[1].ptr,
		utils->img[1].dim.start.x, utils->img[1].dim.start.y);
}

static void	put_selected_object_images(t_utils *utils)
{
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[3].ptr,
		utils->img[3].dim.start.x, utils->img[3].dim.start.y);
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[7].ptr,
		utils->img[7].dim.start.x, utils->img[7].dim.start.y);
	if (utils->property[0] != NULL)
	{
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[10].ptr,
			utils->img[10].dim.start.x, utils->img[10].dim.start.y);
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[11].ptr,
			utils->img[11].dim.start.x, utils->img[11].dim.start.y);
	}
	if (utils->property[1] != NULL)
	{
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[12].ptr,
			utils->img[12].dim.start.x, utils->img[12].dim.start.y);
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[13].ptr,
			utils->img[13].dim.start.x, utils->img[13].dim.start.y);
	}
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[5].ptr,
		utils->img[5].dim.start.x, utils->img[5].dim.start.y);
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[6].ptr,
		utils->img[6].dim.start.x, utils->img[6].dim.start.y);
}

static void	put_misc_images(t_utils *utils)
{
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[8].ptr,
		utils->img[8].dim.start.x, utils->img[8].dim.start.y);
	mlx_put_image_to_window(utils->mlx, utils->win, utils->img[9].ptr,
		utils->img[9].dim.start.x, utils->img[9].dim.start.y);
	if (utils->add_object_menu == 1)
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[4].ptr,
			utils->img[4].dim.start.x, utils->img[4].dim.start.y);
	if (utils->visual_rays >= 1)
		mlx_put_image_to_window(utils->mlx, utils->win, utils->img[2].ptr,
			utils->img[2].dim.start.x, utils->img[2].dim.start.y);
}

void	put_images_to_window(t_utils *utils)
{
	put_main_images(utils);
	if (utils->sel_object != NULL)
		put_selected_object_images(utils);
	put_misc_images(utils);
}
