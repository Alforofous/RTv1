/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 08:25:53 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/07 11:45:07 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	fill_img(t_utils *utils, t_uint color)
{
	t_2i	coords;

	coords.y = 0;
	if ((0xFF000000 & color) == 0xFF000000)
		return ;
	while (coords.y < utils->curr_img->dim.size.y)
	{
		coords.x = 0;
		while (coords.x < utils->curr_img->dim.size.x)
		{
			put_pixel(coords, color, utils->curr_img);
			coords.x++;
		}
		coords.y++;
	}
}

void	put_pixel(t_2i coords, t_uint color, void *param)
{
	t_img	*img;
	char	*dst;

	img = param;
	if (coords.x >= 0 && coords.y >= 0
		&& coords.x < img->dim.size.x && coords.y < img->dim.size.y)
	{
		dst = img->addr + (coords.y * img->line_length
			+ coords.x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_dot(t_2i coords, t_uint color, void *param)
{
	t_img	*img;

	img = (t_img *)param;
	if (coords.x >= 0 && coords.y >= 0
		&& coords.x < img->dim.size.x && coords.y < img->dim.size.y)
		draw_circlef(&(t_pxl_func){&put_pixel, img}, coords, 2, color);
}
