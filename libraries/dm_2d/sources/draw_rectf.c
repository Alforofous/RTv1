/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:58 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 15:19:17 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_rectf(t_pxl_func *pxl, t_2i coords, t_2i dimen, t_uint color)
{
	int		dest;
	t_line	line;

	dest = coords.y + dimen.y;
	while (coords.y <= dest)
	{
		line = (t_line){coords, (t_2i){coords.x + dimen.x, coords.y}};
		draw_line(pxl, line, color, color);
		coords.y += 1;
	}
}
