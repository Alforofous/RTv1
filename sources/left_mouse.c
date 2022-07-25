/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:24:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/25 15:38:04 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	hold_left_button(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}

void	left_button_down(t_utils *utils, int x, int y)
{
	ray_plotting(utils, &utils->img, (t_2i){x - utils->img.dim.x0, y - utils->img.dim.y0});
	utils->sel_object = utils->closest_object;
	utils += 0;
	x += 0;
	y += 0;
	image_processing(utils, &utils->img4, 0x000000);
}

void	left_button_up(t_utils *utils, int x, int y)
{
	utils += 0;
	x += 0;
	y += 0;
}
