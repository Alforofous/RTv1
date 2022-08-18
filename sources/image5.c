/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:25:31 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/18 15:41:19 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_image5(t_utils *utils)
{
	t_2i	coords;

	coords.x = (int)(utils->curr_img->dim.width * 0.0);
	coords.y = (int)(utils->curr_img->dim.height * 0.0);
	draw_rect(&(t_pxl_func){&ft_pixel_put, utils->curr_img},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 1,
		utils->curr_img->dim.height - 1}, 0x5289FC);
}
