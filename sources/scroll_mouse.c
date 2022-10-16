/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/16 12:51:38 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scroll_wheel(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}

void	scroll_wheel_up(t_utils *utils, int x, int y)
{
	if (utils->multiplier < 64.0f)
		utils->multiplier *= 2.0f;
	image_processing(utils, &utils->img[1], 0x000000, 0);
	put_images_to_window(utils);
	(void)x;
	(void)y;
}

void	scroll_wheel_down(t_utils *utils, int x, int y)
{
	if (utils->multiplier > 0.125f)
		utils->multiplier /= 2.0f;
	image_processing(utils, &utils->img[1], 0x000000, 0);
	put_images_to_window(utils);
	(void)x;
	(void)y;
}
