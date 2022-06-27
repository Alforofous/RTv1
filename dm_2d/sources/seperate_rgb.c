/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:00:46 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/27 12:32:23 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	seperate_rgb(t_u_int color, int *red, int *green, int *blue)
{
	*red = (color & 0xFF0000) >> 16;
	*green = (color & 0x00FF00) >> 8;
	*blue = (color & 0x0000FF);
}
