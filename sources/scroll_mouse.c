/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/13 12:10:55 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scroll_wheel(t_utils *u, int x, int y)
{
	u += 0;
	x += 0;
	y += 0;
}

void	scroll_wheel_up(t_utils *u, int x, int y)
{
	if (u->mouse.zoom > 3)
		u->mouse.zoom = (int)((float)u->mouse.zoom / 1.6f);
	x += 0;
	y += 0;
}

void	scroll_wheel_down(t_utils *u, int x, int y)
{
	u->mouse.zoom = (int)((float)u->mouse.zoom * 1.6f);
	x += 0;
	y += 0;
}
