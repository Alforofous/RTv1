/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_slider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:18:19 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/06 16:41:14 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Initiate RGB slider pallete (main colors for palette, changable)*/
static void	init_rgb_slider_palette(t_uint	*color)
{
	color[0] = 0xFF0000;
	color[1] = 0xFFFF00;
	color[2] = 0x00FF00;
	color[3] = 0x00FFFF;
	color[4] = 0x0000FF;
	color[5] = 0xFF00FF;
	color[6] = 0xFF0000;
}

/*Mapping of xy into image size and getting horizontal & vertical percentage
 * for color transition*/
static t_2f	init_perc_values(t_img *img, t_2i *coords, int *color_i)
{
	t_2f	perc;

	perc.x = (float)(coords->x) / (float)(img->dim.size.x - 1);
	perc.x *= (float)*color_i;
	*color_i = (int)(perc.x - 0.001f);
	while (perc.x > 1.0f)
		perc.x -= 1.0f;
	perc.y = (float)coords->y / (float)(img->dim.size.y - 1);
	perc.y = (2 * perc.y) - 1;
	return (perc);
}

t_uint	rgb_slider(t_img *img, t_2i *coords)
{
	t_uint	color[7];
	t_uint	final_color;
	t_2ui	mixed;
	t_2f	perc;
	int		i;

	final_color = 0x000000;
	init_rgb_slider_palette(&color[0]);
	i = 6;
	perc = init_perc_values(img, coords, &i);
	if (i < 6)
	{
		if (perc.y < 0)
		{
			mixed.x = transition_colors(color[i], 0xFFFFFF, fabsf(perc.y));
			mixed.y = transition_colors(color[i + 1], 0xFFFFFF, fabsf(perc.y));
		}
		else
		{
			mixed.x = transition_colors(color[i], 0x000000, perc.y);
			mixed.y = transition_colors(color[i + 1], 0x000000, perc.y);
		}
		final_color = transition_colors(mixed.x, mixed.y, perc.x);
	}
	return (final_color);
}
