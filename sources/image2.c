/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:44:56 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/20 10:45:30 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_image2(t_utils *utils)
{
	int	pos[2];

	pos[0] = utils->curr_img->dim.width / 10;
	pos[1] = utils->curr_img->dim.height / 40;
	if (utils->sel_object != NULL)
	{
		draw_rectf(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
			&(t_2i){pos[0], pos[1]}, &(t_2i){pos[0] * 9, pos[1] * 9}, utils->sel_object->color);
	}
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0xFFDD45);
}
