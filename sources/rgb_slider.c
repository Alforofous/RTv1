/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_slider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:18:19 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/15 17:23:09 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	swap_color(t_uint *color1, t_uint *color2)
{
	t_uint	temp;

	temp = *color1;
	*color1 = *color2;
	*color2 = temp;
}

void	draw_rgb_slider(t_img *img)
{
	t_2i	coords;
	t_uint	color[3];
	float	slider;
	float	step[2];
	float	percent;

	coords.y = 0;
	step[0] = 1.0f / img->dim.width * 6.0f;
	while (coords.y <= img->dim.height)
	{
		percent = 0;
		coords.x = 0;
		while (coords.x <= img->dim.width)
		{
			if (percent >= 1)
			{
				percent = 1;
				step[0] *= -1;
			}
			else if (percent <= 0)
			{
				percent = 0;
				step[0] *= -1;
			}
			slider = (float)coords.x / img->dim.width;
			if (slider <= 1.0 / 3)
			{
				color[0] = 0xFF0000;
				color[1] = 0x00FF00;
			}
			else if (slider <= 1.0 / 3 * 2)
			{
				color[0] = 0x00FF00;
				color[1] = 0x0000FF;
			}
			else
			{
				color[0] = 0x0000FF;
				color[1] = 0xFF0000;
			}
			if (step[0] <= 0.0f)
				swap_color(&color[0], &color[1]);
			color[1] = color[0] | color[1];
			put_pixel(coords.x, coords.y, transition_colors(color[0], color[1], percent), img);
			coords.x += 1;
			percent += step[0];
		}
		coords.y += 1;
	}
}
