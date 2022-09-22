/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_slider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:18:19 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 11:58:00 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_uint	rgb_slider(t_img *img, t_2i *coords)
{
	t_uint	color[10];
	int		i;
	float	perc[2];

	perc[0] = (float)(coords->x) / (float)(img->dim.width - 1) * 6.0f;
	i = (int)(perc[0] - 0.001f);
	while (perc[0] > 1.0f)
		perc[0] -= 1.0f;
	perc[1] = (float)coords->y / (float)img->dim.height;
	perc[1] = (2 * perc[1]) - 1;
	color[0] = 0xFF0000;
	color[1] = 0xFFFF00;
	color[2] = 0x00FF00;
	color[3] = 0x00FFFF;
	color[4] = 0x0000FF;
	color[5] = 0xFF00FF;
	color[6] = 0xFF0000;
	color[9] = 0xFFFFFF;
	if (i < 6)
	{
		if (perc[1] < 0)
		{
			color[7] = transition_colors(color[i], 0xFFFFFF, fabsf(perc[1]));
			color[8] = transition_colors(color[i + 1], 0xFFFFFF, fabsf(perc[1]));
		}
		else
		{
			color[7] = transition_colors(color[i], 0x000000, perc[1]);
			color[8] = transition_colors(color[i + 1], 0x000000, perc[1]);
		}
		color[9] = transition_colors(color[7], color[8], perc[0]);
		put_pixel(coords->x, coords->y, color[9], img);
	}
	return (color[9]);
}
