/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:44:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 12:44:50 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rgb_iter(t_img *img, t_uint (*f)(t_img *, t_2i *))
{
	t_2i	coords;

	coords.y = 0;
	while (coords.y <= img->dim.height)
	{
		coords.x = 0;
		while (coords.x <= img->dim.width)
		{
			f(img, &coords);
			coords.x += 1;
		}
		coords.y += 1;
	}
}

void	draw_image7(t_utils *utils)
{
	rgb_iter(utils->curr_img, &rgb_slider);
	draw_rect(&(t_pxl_func){&put_dot, utils},
		&(t_2i){0, 0}, &(t_2i){utils->curr_img->dim.width - 2,
		utils->curr_img->dim.height - 2}, 0xFFFFFF);
}
