/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:04:23 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 10:33:12 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

int	mix_colors(int color, int color2, float percent)
{
	t_cols	chn[2];

	if (percent == 0)
		return (color);
	seperate_rgb(color, &chn[0].r, &chn[0].g, &chn[0].b);
	seperate_rgb(color2, &chn[1].r, &chn[1].g, &chn[1].b);
	if (chn[0].r <= chn[1].r)
		chn[0].r = (int)((float)abs(chn[0].r - chn[1].r) * percent) + chn[0].r;
	else
		chn[0].r = (int)(abs(chn[0].r - chn[1].r) * (1.0 - percent)) + chn[1].r;
	if (chn[0].g <= chn[1].g)
		chn[0].g = (int)((float)abs(chn[0].g - chn[1].g) * percent) + chn[0].g;
	else
		chn[0].g = (int)(abs(chn[0].g - chn[1].g) * (1.0 - percent)) + chn[1].g;
	if (chn[0].b <= chn[1].b)
		chn[0].b = (int)((float)abs(chn[0].b - chn[1].b) * percent) + chn[0].b;
	else
		chn[0].b = (int)(abs(chn[0].b - chn[1].b) * (1.0 - percent)) + chn[1].b;
	color = combine_rgb(chn[0].r, chn[0].g, chn[0].b);
	return (color);
}
