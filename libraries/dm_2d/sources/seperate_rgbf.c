/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_rgbf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:37:30 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:24:56 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	seperate_rgbf(t_uint color, float *red, float *green, float *blue)
{
	*red = (float)((color & 0xFF0000) >> 16);
	*green = (float)((color & 0x00FF00) >> 8);
	*blue = (float)((color & 0x0000FF));
	*red /= 255.0f;
	*green /= 255.0f;
	*blue /= 255.0f;
}
