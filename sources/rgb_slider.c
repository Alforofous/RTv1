/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_slider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:18:19 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/16 09:50:19 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_rgb_slider(t_img *img)
{
	t_2i	coords;
	t_uint	color[7];
	int		i;
	float	step[2];
	float	percent;
	int		switch_len;

	coords.y = 0;
	step[0] = 1.0f / (float)img->dim.width * 6.0f;
	color[0] = 0xFF0000;
	color[1] = 0xFFFF00;
	color[2] = 0x00FF00;
	color[3] = 0x00FFFF;
	color[4] = 0x0000FF;
	color[5] = 0xFF00FF;
	color[6] = 0xFF0000;
	while (coords.y <= img->dim.height)
	{
		percent = 0;
		coords.x = 0;
		i = 0;
		switch_len = img->dim.width / 6;
		while (coords.x <= img->dim.width)
		{
			if (percent >= 1)
				percent = 0;
			if (switch_len < 0)
			{
				switch_len = img->dim.width / 6;
				i++;
			}
			if (i < 6)
				put_pixel(coords.x, coords.y, transition_colors(color[i], color[i + 1], percent), img);
			coords.x += 1;
			switch_len -= 1;
			percent += step[0];
		}
		coords.y += 1;
	}
}
