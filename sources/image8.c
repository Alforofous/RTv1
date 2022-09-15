/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:55:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/15 16:56:06 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_image8(t_utils *utils)
{
	draw_rgb_slider(utils->curr_img);
	draw_rect(&(t_pxl_func){&put_dot, utils},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0xFFFFFF);
}
