/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_slider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:18:19 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/06 13:37:39 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_rgb_slider_palette(t_uint	*color)
{
	color[0] = 0xFF0000;
	color[1] = 0xFFFF00;
	color[2] = 0x00FF00;
	color[3] = 0x00FFFF;
	color[4] = 0x0000FF;
	color[5] = 0xFF00FF;
	color[6] = 0xFF0000;
	color[7] = 0x676767;
	color[8] = 0xFFFFFF;
}

t_uint	rgb_slider(t_img *img, t_2i *coords)
{
	t_uint	color[9];
	t_2ui	mixed;
	int		i;
	float	perc[2];

	perc[0] = (float)(coords->x) / (float)(img->dim.size.x - 1) * 7.0f;
	i = (int)(perc[0] - 0.001f);
	while (perc[0] > 1.0f)
		perc[0] -= 1.0f;
	perc[1] = (float)coords->y / (float)img->dim.size.y;
	perc[1] = (2 * perc[1]) - 1;
	init_rgb_slider_palette(&color[0]);
	if (i < 7)
	{
		if (perc[1] < 0)
		{
			mixed.x = transition_colors(color[i], 0xFFFFFF, fabsf(perc[1]));
			mixed.y = transition_colors(color[i + 1], 0xFFFFFF, fabsf(perc[1]));
		}
		else
		{
			mixed.x = transition_colors(color[i], 0x000000, perc[1]);
			mixed.y = transition_colors(color[i + 1], 0x000000, perc[1]);
		}
		color[8] = transition_colors(mixed.x, mixed.y, perc[0]);
	}
	return (color[8]);
}
